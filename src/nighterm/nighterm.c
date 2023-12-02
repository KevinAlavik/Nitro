#include "nighterm.h"
#include "display/vga.h"
struct Terminal term;
char textBuffer[4096*4];
uint8_t fg_r = 255;
uint8_t fg_g = 255;
uint8_t fg_b = 255;

uint8_t bg_r = 0;
uint8_t bg_g = 0;
uint8_t bg_b = 0;

// TODO: Move memset into its own stdlib
void* memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

int init_nighterm(struct limine_file* font) {
    char *psf2buf = font->address;
    psf2Hdr hdr = *(psf2Hdr *)font->address;
    psf2buf += hdr.headerSize;

    if (hdr.magic[0] != 0x72 || hdr.magic[1] != 0xb5 || hdr.magic[2] != 0x4a ||
        hdr.magic[3] != 0x86)
        return 0;

    size_t buffer_size = (size_t)(getScreenWidth() / hdr.width) * (getScreenHeight() / hdr.height);
    term.fonthdr = hdr;
    term.fontData = psf2buf;
    term.cols = (getScreenHeight() / hdr.height);
    term.rows = (getScreenWidth() / hdr.width);
    term.curX = 0;
    term.curY = 0;
    nighterm_clear();
    return 1;
}

void nighterm_set_char_fg(uint8_t r, uint8_t b, uint8_t g) {
    fg_r = r;
    fg_g = g;
    fg_b = b;
}
void nighterm_set_char_bg(uint8_t r, uint8_t b, uint8_t g) {
    bg_r = r;
    bg_g = g;
    bg_b = b;
}

void nighterm_render_char(int row, int col,char ch){
    int rounding = ((term.fonthdr.width % 8) != 0) ^ (term.fonthdr.width == 9);
    uint8_t *glyph = term.fontData + ch * term.fonthdr.charSize;

    for (size_t y = 0; y < term.fonthdr.height; y++) {
        for (size_t x = 0; x < term.fonthdr.width; x++) {
            if ((glyph[y * ((term.fonthdr.width / 8) + rounding) + x / 8] >> (7 - x % 8)) & 1) {
                draw_pixel(col*term.fonthdr.width + x, row*term.fonthdr.height+ y, fg_r, fg_g, fg_b);
            } else {
                draw_pixel(col*term.fonthdr.width + x, row*term.fonthdr.height+ y, bg_r, bg_g, bg_b);
            }
        }
    }
}

void nighterm_refresh() {
    //Note: do not overuse this function since refreshing one character at a time is much mre efficient
    int row, col;
    for (row = 0; row < term.rows; row++) {
        for (col = 0; col < term.cols; col++) {
            char ch = textBuffer[row * term.cols + col];
            nighterm_render_char(col, row, ch);
        }
    }
}

void nighterm_clear() {
    size_t buffer_size = (size_t)term.rows * term.cols;
    memset(textBuffer, ' ', buffer_size);
    nighterm_refresh();
}

void nighterm_write(char ch) {
    size_t buffer_size = (size_t)term.rows * term.cols;
    switch (ch)
    {
    case '\n':
        term.curX = 0;
        term.curY++;
        break;
    case '\t':
        term.curX += INDENT_AMOUNT;
        break;
    case '\b':
        term.curX -= 1;
        break;
    case 0:
        break;// ignore termination
    default:
        int bufferIndex = term.curY * term.cols + term.curX;
        textBuffer[bufferIndex] = ch;
        term.curX++;
        nighterm_render_char(term.curY,term.curX - 1,ch);
        break;
    }

}
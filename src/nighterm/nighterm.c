#include "nighterm.h"
#include "display/vga.h"

struct Terminal term;
char textBuffer[4096*4];
uint8_t r = 255;
uint8_t g = 255;
uint8_t b = 255;

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
    memset(textBuffer, ' ', buffer_size);
    return 1;
}

void nighterm_set_char_fg(uint8_t r, uint8_t b, uint8_t g) {
    r = r;
    g = g;
    b = b;
}

void nighterm_render_char(int row, int col,char ch){
    int rounding = ((term.fonthdr.width % 8) != 0) ^ (term.fonthdr.width == 9);
    uint8_t *glyph = term.fontData + ch * term.fonthdr.charSize;

    for (size_t y = 0; y < term.fonthdr.height; y++) {
        for (size_t x = 0; x < term.fonthdr.width; x++) {
            if ((glyph[y * ((term.fonthdr.width / 8) + rounding) + x / 8] >> (7 - x % 8)) & 1) {
                draw_pixel(col+x, row+y, r, g, b);
            } else {
                //TODO: plot a secondary/background color pixel at the correct location
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
            nighterm_render_char(row,col,ch);
        }
        printf("\n");
    }
}

void clear_text_buffer() {
    size_t buffer_size = (size_t)term.rows * term.cols;
    memset(textBuffer, ' ', buffer_size);
}

void nighterm_print(const char* text) {
    nighterm_set_char_fg(255, 255, 255);
    size_t buffer_size = (size_t)term.rows * term.cols;
    int bufferIndex = 0;

    while (textBuffer[bufferIndex] != '\0' && bufferIndex < buffer_size) {
        bufferIndex++;
    }

    for (int i = 0; text[i] != '\0' && bufferIndex < buffer_size - 1; ++i) {
        textBuffer[bufferIndex++] = text[i];
    }

    textBuffer[bufferIndex] = '\0';
}
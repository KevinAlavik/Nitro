#include "nighterm.h"
#include "display/vga.h"

struct Terminal term;
char textBuffer[4096*4];

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
    nighterm_refresh(); // refresh to clear
    return 1;
}
void nighterm_render_char(int row, int col,char ch){
    int rounding = ((term.fonthdr.width % 8) != 0) ^ (term.fonthdr.width == 9);
    uint8_t *glyph = term.fontData + ch * term.fonthdr.charSize;

    for (size_t y = 0; y < term.fonthdr.height; y++) {
        for (size_t x = 0; x < term.fonthdr.width; x++) {
            if ((glyph[y * ((term.fonthdr.width / 8) + rounding) + x / 8] >> (7 - x % 8)) & 1) {
                //TODO: plot a primary color pixel at the correct location
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

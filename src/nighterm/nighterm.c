#include "nighterm.h"
#include "display/vga.h"

// TODO: Make it work lol
// TODO: Move memset into its own stdlib
// void* memset(void *ptr, int value, size_t num) {
//     unsigned char *p = ptr;
//     while (num--) {
//         *p++ = (unsigned char)value;
//     }
//     return ptr;
// }

// struct Terminal* init_nighterm(struct limine_file* font) {
//     struct Terminal* term = (struct Terminal*)malloc(sizeof(struct Terminal));
//     char *psf2buf = font->address;
//     psf2Hdr hdr = *(psf2Hdr *)font->address;
//     psf2buf += hdr.headerSize;

//     if (hdr.magic[0] != 0x72 || hdr.magic[1] != 0xb5 || hdr.magic[2] != 0x4a ||
//         hdr.magic[3] != 0x86)
//         return (void *)0;

//     if (term != NULL) {
//         size_t buffer_size = (size_t)(getScreenWidth() / hdr.width) * (getScreenHeight() / hdr.height);
//         term->fonthdr = hdr;
//         term->fontData = psf2buf;
//         term->textBuffer = malloc(buffer_size);
//         term->cols = (getScreenHeight() / hdr.height);
//         term->rows = (getScreenWidth() / hdr.width);
//         term->curX = 0;
//         term->curY = 0;
//         memset(term->textBuffer, ' ', buffer_size);
//         nighterm_refresh(term); // refresh to clear
//     }
//     return term;
// }
// void nighterm_render_char(struct Terminal *term,int row, int col,char ch){
//     int rounding = ((term->fonthdr.width % 8) != 0) ^ (term->fonthdr.width == 9);
//     uint8_t *glyph = term->fontData + ch * term->fonthdr.charSize;

//     for (size_t y = 0; y < term->fonthdr.height; y++) {
//         for (size_t x = 0; x < term->fonthdr.width; x++) {
//             if ((glyph[y * ((term->fonthdr.width / 8) + rounding) + x / 8] >> (7 - x % 8)) & 1) {
//                 //TODO: plot a primary color pixel at the correct location
//             } else {
//                 //TODO: plot a secondary/background color pixel at the correct location
//             }
//         }
//     }
// }

// void nighterm_refresh(struct Terminal *term) {
//     //Note: do not overuse this function since refreshing one character at a time is much mre efficient
//     int row, col;
//     for (row = 0; row < term->rows; row++) {
//         for (col = 0; col < term->cols; col++) {
//             char ch = term->textBuffer[row * term->cols + col];
//             nighterm_render_char(term,row,col,ch);
//         }
//         printf("\n");
//     }
// }

// void clear_text_buffer(struct Terminal *term) {
//     size_t buffer_size = (size_t)term->rows * term->cols;
//     memset(term->textBuffer, ' ', buffer_size);
// }

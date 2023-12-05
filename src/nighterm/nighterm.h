#ifndef NIGHTERM_H_
#define NIGHTERM_H_
#include <limine.h>

#define INDENT_AMOUNT 4

#define PSF2_MAGIC0 0x72
#define PSF2_MAGIC1 0xb5
#define PSF2_MAGIC2 0x4a
#define PSF2_MAGIC3 0x86

#define PSF2_MODE 1

typedef struct {
    uint8_t magic[4];
    uint32_t version;
    uint32_t headerSize;
    uint32_t flags;
    uint32_t length;
    uint32_t charSize;
    uint32_t height, width;
} __attribute__((packed)) psf2Hdr;

struct Terminal {
    psf2Hdr fonthdr;
    void* fontData;
    int curX;
    int curY;
    int rows;
    int cols;    
    char* buffer;
};
extern struct Terminal term;

int init_nighterm(struct limine_file* font);
void nighterm_refresh();
void nighterm_clear();
void nighterm_set_char_fg(uint8_t r, uint8_t b, uint8_t g);
void nighterm_set_char_bg(uint8_t r, uint8_t b, uint8_t g);
void nighterm_write(char ch);
void nighterm_move_cursor(int row, int col);

#endif // NIGHTERM_H_

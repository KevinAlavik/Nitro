#ifndef NIGHTERM_H_
#define NIGHTERM_H_
#include <limine.h>

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
};
extern struct Terminal term;
extern uint8_t r;
extern uint8_t g;
extern uint8_t b;

int init_nighterm(struct limine_file* font);
void nighterm_refresh();
void clear_text_buffer();
void nighterm_set_char_fg(uint8_t r, uint8_t b, uint8_t g);
void nighterm_print(const char* text);

#endif // NIGHTERM_H_
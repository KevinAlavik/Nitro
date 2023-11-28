// TODO: Make this more structured
#include "vga.h"

#include "cpu/cpu.h"
#include "fonts.h"

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0};

struct limine_framebuffer *framebuffer;
volatile uint32_t *fb_ptr;

uint16_t display_red = 0;
uint16_t display_green = 0;
uint16_t display_blue = 0;

void init_display() {
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    {
        hcf();
    }

    framebuffer = framebuffer_request.response->framebuffers[0];
    fb_ptr = framebuffer->address;
}

void display_write_data(uint32_t address, uint8_t red, uint8_t green, uint8_t blue) {
    fb_ptr[address] = rgb(red, green, blue);
}

unsigned int rgb(uint8_t red, uint8_t green, uint8_t blue) {
    return (0xFF << 24) | (red << 16) | (green << 8) | blue;
}

void draw_pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t b, uint8_t g) {
    fb_ptr[x * 4 + y * framebuffer->pitch] = rgb(r, g, b);
}

void set_background_color(uint16_t red, uint16_t green, uint16_t blue) {
    display_red = red;
    display_green = green;
    display_blue = blue;

    for (size_t x = 0; x < framebuffer->width; x++) {
        for(size_t y = 0; y < framebuffer->height; y++) {
            draw_pixel(x, y, display_red, display_green, display_blue);
        }
    }
}

void draw_letter(int letterIndex, int x, int y, int r, int g, int b)
{
    for (size_t yi = 0; yi < LETTER_HEIGHT; yi++)
    {
        for (size_t xi = 0; xi < LETTER_WIDTH; xi++)
        {
            uint8_t bit = current_font[letterIndex][yi] & (0x80 >> xi);
            if (bit != 0)
            {
                draw_pixel(x + xi, y + yi, r, b, g);
            }
        }
    }
}

// TODO: Move these into a somewhat stdlib

size_t current_line = 0;
size_t current_column = 0;

void newline() {
    current_line++;
    current_column = 0;
}

void clear() {
    current_line = 0;
    current_column = 0;
    set_background_color(display_red, display_green, display_blue);
}

void printf(const char* text) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char letter = text[i];

        if (letter == '\n') {
            newline();
            continue;
        }

        if (letter == '\t') {
            current_column += INDENT_AMOUNT;
            continue;
        }

        int x_position = TEXT_PADDING + (current_column * (LETTER_WIDTH + TEXT_PADDING));
        int y_position = TEXT_PADDING + (current_line * (LETTER_HEIGHT + TEXT_PADDING));
        int r = 255, g = 255, b = 255;

        int letterIndex = (int)letter;
        draw_letter(letterIndex, x_position, y_position, r, g, b);

        current_column++;
    }
}

void printfc(const char* text, int r, int g, int b) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char letter = text[i];

        if (letter == '\n') {
            newline();
            continue;
        }

        if (letter == '\t') {
            current_column += INDENT_AMOUNT;
            continue;
        }

        int x_position = TEXT_PADDING + (current_column * (LETTER_WIDTH + TEXT_PADDING));
        int y_position = TEXT_PADDING + (current_line * (LETTER_HEIGHT + TEXT_PADDING));

        int letterIndex = (int)letter;
        draw_letter(letterIndex, x_position, y_position, r, g, b);

        current_column++;
    }
}

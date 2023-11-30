#include "stdio.h"

size_t current_line = 0;
size_t current_column = 0;

void newline() {
    current_line++;
    current_column = 0;
}

void move_cursor(int row, int col) {
    current_line = row;    
    current_column = col;
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
        draw_letter(letterIndex, x_position, y_position, r, g, b, 1);

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
        draw_letter(letterIndex, x_position, y_position, r, g, b, 1);

        current_column++;
    }
}

void printfcs(const char* text, int r, int g, int b, int size) {
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
        draw_letter(letterIndex, x_position, y_position, r, g, b, 1);

        current_column++;
    }
}

void printfs(const char* text, int size) {
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
        draw_letter(letterIndex, x_position, y_position, r, g, b, 1);

        current_column++;
    }
}

void print_char(char letter, int x, int y, int r, int g, int b, int fontSize) {
    if (letter == '\n') {
        newline();
        return;
    }

    if (letter == '\t') {
        current_column += INDENT_AMOUNT;
        return;
    }

    int x_position = x + (current_column * (LETTER_WIDTH + TEXT_PADDING));
    int y_position = y + (current_line * (LETTER_HEIGHT + TEXT_PADDING));

    draw_letter((int)letter, x_position, y_position, r, g, b, fontSize);
    current_column++;
}
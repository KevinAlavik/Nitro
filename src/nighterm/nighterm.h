#ifndef NIGHTERM_H_
#define NIGHTERM_H_

struct Terminal {
    int rows;
    int cols;
    char** textBuffer;
};

struct Terminal* init_nighterm(int rows, int cols);
void destroy_nighterm(struct Terminal* term);

#endif // NIGHTERM_H_

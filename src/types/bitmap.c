#include "bitmap.h"

bool bitmap_set(struct Bitmap bm, size_t index, bool setto) {
    if (index > bm.size * 8)
        return false;
    register size_t byteIndex = index / 8;
    register uint8_t bitIndex = index % 8;

    register uint8_t bitMask = (1 << (bitIndex));

    register uint8_t temp =
        bm.buffer[byteIndex] ^ (bm.buffer[byteIndex] & bitMask);

    bm.buffer[byteIndex] = temp | (setto << (bitIndex));
    return true;
}

bool bitmap_get(struct Bitmap bm, size_t index) {
    register size_t byteIndex = index / 8;
    register uint8_t bitIndex = index % 8;

    register uint8_t bitIndexer = 1 << bitIndex;
    return bm.buffer[byteIndex] & bitIndexer;
}
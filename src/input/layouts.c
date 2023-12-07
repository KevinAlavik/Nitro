#include "layouts.h"

// Swedish (SE-SV) layout
struct KeyState sv_layout[0xFF + 1] = {
    [0x01] = { "", "", "" },
    [0x02] = { "\x31", "!", "1" },
    [0x03] = { "\x32", "\"", "2" },
    [0x04] = { "\x33", "#", "3" },
    [0x05] = { "\x34", "$", "4" },
    [0x06] = { "\x35", "%", "5" },
    [0x07] = { "\x36", "&", "6" },
    [0x08] = { "\x37", "/", "7" },
    [0x09] = { "\x38", "(", "8" },
    [0x0A] = { "\x39", ")", "9" },
    [0x0B] = { "\x30", "=", "0" },
    [0x0C] = { "+", "?", "+" },
    [0x0D] = { "´", "`", "´" },
    [0x0E] = { "\b \b", "\b \b", "\b \b" }, // Backspace
    [0x0F] = { "\t", "\t", "\t" }, // Tab
    [0x10] = { "q", "Q", "Q" },
    [0x11] = { "w", "W", "W" },
    [0x12] = { "e", "E", "E" },
    [0x13] = { "r", "R", "R" },
    [0x14] = { "t", "T", "T" },
    [0x15] = { "y", "Y", "Y" },
    [0x16] = { "u", "U", "U" },
    [0x17] = { "i", "I", "I" },
    [0x18] = { "o", "O", "O" },
    [0x19] = { "p", "P", "P" },
    [0x1A] = { "å", "Å", "Å" },
    [0x1B] = { "¨", "^", "¨" },
    [0x1C] = { "\n", "\n", "\n" }, // Enter
    [0x1D] = { "", "", "" }, // Left control
    [0x1E] = { "a", "A", "A" },
    [0x1F] = { "s", "S", "S" },
    [0x20] = { "d", "D", "D" },
    [0x21] = { "f", "F", "F" },
    [0x22] = { "g", "G", "G" },
    [0x23] = { "h", "H", "H" },
    [0x24] = { "j", "J", "J" },
    [0x25] = { "k", "K", "K" },
    [0x26] = { "l", "L", "L" },
    [0x27] = { "ö", "Ö", "Ö" },
    [0x28] = { "ä", "Ä", "Ä" },
    [0x29] = { "´", "`", "´" },
    [0x2A] = { "", "", "" }, // Left shift
    [0x2B] = { "<", ">", "<" },
    [0x2C] = { "z", "Z", "Z" },
    [0x2D] = { "x", "X", "X" },
    [0x2E] = { "c", "C", "C" },
    [0x2F] = { "v", "V", "V" },
    [0x30] = { "b", "B", "B" },
    [0x31] = { "n", "N", "N" },
    [0x32] = { "m", "M", "M" },
    [0x33] = { ",", ";", "," },
    [0x34] = { ".", ":", "." },
    [0x35] = { "-", "_", "-" },
    [0x36] = { "", "", "" }, // Right shift
    [0x37] = { "*", "*", "*" },
    [0x38] = { "", "", "" }, // Left alt
    [0x39] = { " ", " ", " " },
    [0x3A] = { "", "", "" }, // Caps lock
    [0x3B ... 0xFF] = { "", "", "" }
};

// US English (US) layout
struct KeyState us_layout[0xFF + 1] = {
    [0x01] = { "", "", "" },
    [0x02] = { "\x31", "!", "1" },
    [0x03] = { "\x32", "@", "2" },
    [0x04] = { "\x33", "#", "3" },
    [0x05] = { "\x34", "$", "4" },
    [0x06] = { "\x35", "%", "5" },
    [0x07] = { "\x36", "^", "6" },
    [0x08] = { "\x37", "&", "7" },
    [0x09] = { "\x38", "*", "8" },
    [0x0A] = { "\x39", "(", "9" },
    [0x0B] = { "\x30", ")", "0" },
    [0x0C] = { "-", "_", "-" },
    [0x0D] = { "=", "+", "=" },
    [0x0E] = { "\b \b", "\b \b", "\b \b" }, // Backspace
    [0x0F] = { "\t", "\t", "\t" }, // Tab
    [0x10] = { "q", "Q", "Q" },
    [0x11] = { "w", "W", "W" },
    [0x12] = { "e", "E", "E" },
    [0x13] = { "r", "R", "R" },
    [0x14] = { "t", "T", "T" },
    [0x15] = { "y", "Y", "Y" },
    [0x16] = { "u", "U", "U" },
    [0x17] = { "i", "I", "I" },
    [0x18] = { "o", "O", "O" },
    [0x19] = { "p", "P", "P" },
    [0x1A] = { "[", "{", "[" },
    [0x1B] = { "]", "}", "]" },
    [0x1C] = { "\n", "\n", "\n" }, // Enter
    [0x1D] = { "", "", "" }, // Left control
    [0x1E] = { "a", "A", "A" },
    [0x1F] = { "s", "S", "S" },
    [0x20] = { "d", "D", "D" },
    [0x21] = { "f", "F", "F" },
    [0x22] = { "g"", ""G", "G" },
    [0x23] = { "h", "H", "H" },
    [0x24] = { "j", "J", "J" },
    [0x25] = { "k", "K", "K" },
    [0x26] = { "l", "L", "L" },
    [0x27] = { ";", ":", ";" },
    [0x28] = { "\"", """, """ },
    [0x29] = { "`", "~", "`" },
    [0x2A] = { "", "", "" }, // Left shift
    [0x2B] = { "\\", "|", "\\" },
    [0x2C] = { "z", "Z", "Z" },
    [0x2D] = { "x", "X", "X" },
    [0x2E] = { "c", "C", "C" },
    [0x2F] = { "v", "V", "V" },
    [0x30] = { "b", "B", "B" },
    [0x31] = { "n", "N", "N" },
    [0x32] = { "m", "M", "M" },
    [0x33] = { ",", "<", "," },
    [0x34] = { ".", ">", "." },
    [0x35] = { "/", "?", "/" },
    [0x36] = { "", "", "" }, // Right shift
    [0x37] = { "*", "*", "*" },
    [0x38] = { "", "", "" }, // Left alt
    [0x39] = { " ", " ", " " },
    [0x3A] = { "", "", "" }, // Caps lock
    [0x3B ... 0xFF] = { "", "", "" }
};

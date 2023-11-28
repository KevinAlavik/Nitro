#ifndef LAYOUTS_H
#define LAYOUTS_H

struct KeyState {
    char normal;
    char shifted;
    char caps;
};

extern struct KeyState se_sv_layout[0xFF + 1];
extern struct KeyState us_layout[0xFF + 1];

#endif /* LAYOUTS_H */

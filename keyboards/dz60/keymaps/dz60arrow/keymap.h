#include QMK_KEYBOARD_H

#define _01_BASE 0
#define _02_MODIFIER 1
#define TAPPING_TOGGLE 2
#define FORCE_NKRO
#define INIT_DELAY 2000

enum custom_keycodes{
    _01_MACRO = SAFE_RANGE,
};

void PreInitRGB(void);
void InitRGB(void);
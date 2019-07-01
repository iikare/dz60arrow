#include QMK_KEYBOARD_H

#define _01_BASE 0
#define _02_MODIFIER 1
#define TAPPING_TOGGLE 2
#define FORCE_NKRO
#define INIT_DELAY 10
#define TAP_CODE_DELAY 75

#define BASE_COLOR 17, 255, 190
#define MODIFIER_COLOR 255, 255, 212

enum custom_keycodes{
    _01_MACRO = SAFE_RANGE,
    _02_MACRO
};
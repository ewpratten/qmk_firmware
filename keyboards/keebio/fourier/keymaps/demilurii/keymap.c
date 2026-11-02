// Pull in the QMK lib
#include QMK_KEYBOARD_H

// Shorthands for transparent and empty keys
#define _____ KC_NO
#define _PASS KC_TRNS

// Layer definitions
// clang-format off
enum miwu_layers {
    QWERTY,
    NUMERIC,
    NAVIGATION,
    MEDIA,
    SWAP,
};
// clang-format on

// Layers
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // QWERTY
    [QWERTY] = LAYOUT(
        KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_DEL,      KC_BSPC,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SLSH, KC_QUOT, KC_RSFT, MO(NUMERIC),
        KC_LCTL, KC_LGUI, KC_LALT, MO(NUMERIC), MO(NAVIGATION), KC_SPC, MO(MEDIA), KC_LBRC, KC_RBRC, KC_BSLS
    ),

    // NUMERIC
    [NUMERIC] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, _PASS, _____, _____, KC_F1,  KC_F2,  KC_F3,  KC_F4, KC_MINS, _PASS,
        _PASS,  KC_4, KC_5, KC_6, _____, _PASS, _PASS, KC_F5,  KC_F6,  KC_F7,  KC_F8, KC_EQL,
        _PASS,  KC_7, KC_8, KC_9, KC_0,  _____, KC_F9, KC_F10, KC_F11, KC_F12, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _____, _____, _____
    ),

    // NAVIGATION
    [NAVIGATION] = LAYOUT(
        KC_ESC, KC_COMM, KC_UP,   KC_DOT,  _____, _____, _____, _____, _____, _____, _____, KC_DEL, _PASS,
        _PASS,  KC_LEFT, KC_DOWN, KC_RGHT, _____, _____, _____, _____, _____, _____, _____, KC_ENT,
        _PASS,  KC_T,    KC_I,    KC_L,    _____, _____, _____, _____, _____, _____, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _____, _____, _____
    ),

    // MEDIA
    [MEDIA] = LAYOUT(
        _____, KC_VOLD, KC_VOLU, KC_MUTE, _____, _____, _____,   _____, KC_PGUP, KC_PGDN, KC_PSCR, _PASS, _PASS,
        _PASS, KC_MPRV, KC_MPLY, KC_MNXT, _____, _____, KC_HOME, _____, _____,   _____,   _____,   _PASS,
        _PASS, _____,   _____,   _____,   _____, _____, KC_END,  _____, _____,   _____,   _PASS,   _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _____, _____, TG(SWAP)
    ),

    // SWAP - toggled from the MEDIA layer; swaps the space bar with the NAVIGATION key
    [SWAP] = LAYOUT(
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, KC_SPC, MO(NAVIGATION), _PASS, _PASS, _PASS, TG(SWAP)
    ),

};
// clang-format on

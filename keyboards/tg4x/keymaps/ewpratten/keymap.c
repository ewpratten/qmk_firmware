// Pull in the QMK lib
#include QMK_KEYBOARD_H
#include "os_detection.h"

/* Trickery to make VSCode happy */
#include <stdint.h>
#define _____ KC_NO
#define _PASS KC_TRNS

/* Layer Definitions */
// clang-format off
enum tg4x_layers {
    QWERTY,
    NUMERIC,
    ACTIONS,
    MOUSE,
    MOUSE_SCROLL,
};
// clang-format on

// Custom keycodes
enum tg4x_keycodes {
    MS_EXIT = SAFE_RANGE, // leave the MOUSE layer (bound to Escape while MOUSE is held)
};

/* Layers */
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // QWERTY
    [QWERTY] = LAYOUT(
        KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_DEL,     KC_BSPC,
        KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, TG(MOUSE), MO(NUMERIC),
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE, KC_SPACE, MO(ACTIONS), _____, _____, KC_RSFT
    ),

    // NUMERIC
    [NUMERIC] = LAYOUT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,
        KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
        _PASS,  _____, _____, _____, _____, KC_QUOTE, KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS, _____,   _____,
        _PASS, _PASS, _PASS, KC_SPACE, KC_SPACE, _____, _____, _____, _____
    ),

    // ACTIONS
    [ACTIONS] = LAYOUT(
        _____,   KC_VOLD, KC_VOLU, KC_MUTE, _____, _____,   _____,   KC_PGUP, _____, KC_PGDN,  KC_PSCR, KC_SCRL, KC_PAUS,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _____, _____,   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_INS,  _____,
        _PASS,   UG_TOGG, _____,   _____,   _____, KC_HOME, KC_END,  _____,   _____, _____,    _PASS,   _____,
        _PASS, _PASS, _PASS, KC_SPACE, UC(0x00A0), _____, _____, _____, _____
    ),

    // MOUSE
    [MOUSE] = LAYOUT(
        MS_EXIT, _____, MS_UP, _____, _____,       _____,       _____, _____, _____, _____, _____, _____, _____,
        _____, MS_LEFT, MS_DOWN, MS_RGHT, _____,       _____, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, _____, _____,
        MS_ACL2, _____, _____, _____,       _____,       _____, _____, _____, _____, _____, _PASS, MO(MOUSE_SCROLL),
        MS_ACL0, _PASS, _PASS, MS_BTN1, MS_BTN2, _____, _____, _____, _____
    ),

    // MOUSE_SCROLL (held on top of MOUSE to turn hjkl/wasd into scroll)
    [MOUSE_SCROLL] = LAYOUT(
        _PASS, _____, MS_WHLU, _____,   _____,   _____, _____, _____,   _____,   _____,   _____, _____, _____,
        _____, MS_WHLL, MS_WHLD, MS_WHLR, _____, _____, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _____, _____,
        _PASS, _____, _____,   _____,   _____,   _____, _____, _____,   _____,   _____,   _PASS, _____,
        _PASS, _PASS, _PASS, _PASS, _PASS, _____, _____, _____, _____
    ),

};
// clang-format on

// On macOS, physical Ctrl and Windows/GUI are swapped versus Windows/Linux
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MS_EXIT) {
        if (record->event.pressed) {
            layer_off(MOUSE);
        }
        return false;
    }
    if (detected_host_os() == OS_MACOS) {
        switch (keycode) {
            case KC_LCTL:
                keycode = KC_LGUI;
                break;
            case KC_LGUI:
                keycode = KC_LCTL;
                break;
            default:
                return true;
        }
        if (record->event.pressed) {
            register_code(keycode);
        } else {
            unregister_code(keycode);
        }
        return false;
    }
    return true;
}

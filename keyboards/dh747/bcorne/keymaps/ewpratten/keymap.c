#include QMK_KEYBOARD_H

// Shorthands for transparent and empty keys
#define _____ KC_NO
#define _PASS KC_TRNS

// Layer definitions
enum bcorne_layers {
    BASE,
    COLEMAK,
    NUMERIC,
    ACTIONS,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Default Layer
    [BASE] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,                          KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,     LGUI(KC_SPC), _____, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_QUOT,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,    KC_MCTL,       _____, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_ENT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_SLSH, _____,         _____, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  MO(NUMERIC),
                        KC_LGUI, KC_SPC, MO(NUMERIC),            KC_RALT, KC_SPC, MO(ACTIONS)
    ),

    // Colemak overlay, toggled from the actions layer
    [COLEMAK] = LAYOUT(
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,                       _PASS, _PASS, _PASS, _PASS,    _PASS,   _PASS,
        _PASS, _PASS, _PASS, KC_F,  KC_P,  KC_G,   _PASS, _PASS,        KC_J,  KC_L,  KC_U,  KC_Y,    KC_SCLN, _PASS,
        _PASS, _PASS, KC_R,  KC_S,  KC_T,  KC_D,   _PASS, _PASS,        _PASS, KC_N,  KC_E,  KC_I,    KC_O,    _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,  _PASS, _PASS,        _PASS, KC_K,  _PASS, _PASS,   _PASS,   _PASS,
                              _PASS, _PASS, _PASS,                      _PASS, _PASS, _PASS
    ),

    // F-keys & extra symbols
    [NUMERIC] = LAYOUT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                     KC_F8, KC_F9, KC_F10,  KC_F11,  KC_F12,  _PASS,
        _PASS,  _____, _____, _____, _____, _____,   KC_F6, KC_F7,     _____, _____, _____,   _____,   _____,   _PASS,
        _PASS,  _____, _____, _____, _____, _____,   _____, _____,     _____, _____, _____,   _____,   KC_MINS, KC_EQL,
        _PASS,  _____, _____, _____, _____, KC_BSLS, QK_BOOT, QK_BOOT, KC_QUOT, KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS, _PASS,
                              _PASS, _PASS, _PASS,                     _PASS, _PASS, _PASS
    ),

    // Actions/Navigation
    [ACTIONS] = LAYOUT(
        TG(COLEMAK), _____, _____, _____, _____, _____,         _____,  _____,   _____, _____,   _____, _____,
        _____, _____, _____, _____, _____, _____, _____, _____, _____,   _____,   _____, _____,   _____, _____,
        _PASS, _____, _____, _____, _____, _____, _____, _____, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _____, _____,
        _PASS, _____, _____, _____, _____, _____, _____, _____, _____,   _____,   _____, _____,   _____, _____,
                         _PASS,   _PASS,   _PASS,               _PASS,   _PASS,   _PASS
    ),

};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [COLEMAK] = { ENCODER_CCW_CW(_PASS, _PASS),     ENCODER_CCW_CW(_PASS, _PASS) },
    [NUMERIC] = { ENCODER_CCW_CW(_PASS, _PASS),     ENCODER_CCW_CW(_PASS, _PASS) },
    [ACTIONS] = { ENCODER_CCW_CW(_PASS, _PASS),     ENCODER_CCW_CW(_PASS, _PASS) },
};
// clang-format on

// Light only the keys bound on the active layer, tinted by that layer
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t active_layer = get_highest_layer(layer_state);
    uint8_t layer_hue;
    switch (active_layer) {
        case COLEMAK:
            layer_hue = 191;
            break;
        case NUMERIC:
            layer_hue = 170;
            break;
        case ACTIONS:
            layer_hue = 85;
            break;
        default:
            return true;
    }

    RGB layer_color = hsv_to_rgb((HSV){layer_hue, 255, rgb_matrix_get_val()});
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index == NO_LED || led_index < led_min || led_index >= led_max) {
                continue;
            }

            uint16_t keycode = keymap_key_to_keycode(active_layer, (keypos_t){.row = row, .col = col});
            bool is_unbound = keycode == KC_NO || keycode == KC_TRNS;
            if (is_unbound && active_layer != COLEMAK) {
                rgb_matrix_set_color(led_index, RGB_OFF);
            } else {
                rgb_matrix_set_color(led_index, layer_color.r, layer_color.g, layer_color.b);
            }
        }
    }
    return false;
}

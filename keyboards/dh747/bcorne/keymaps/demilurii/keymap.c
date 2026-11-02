#include QMK_KEYBOARD_H

// Shorthands for transparent and empty keys
#define _____ KC_NO
#define _PASS KC_TRNS

// Layer definitions
enum bcorne_layers {
    QWERTY,
    EXTRAS,
    OVERLAY,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,               KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, _____, _____, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_ENT,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, _____, _____, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, _____, _____, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_DEL,
                  KC_LGUI, MO(EXTRAS), KC_SPC,               KC_SPC, TG(OVERLAY), KC_RALT
    ),
    [EXTRAS] = LAYOUT(
        KC_GRV, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                KC_F8, KC_F9, KC_F10,  KC_F11,  KC_F12,  _____,
        _____,  KC_COMM, KC_UP,   KC_DOT,  _____,   _____,  KC_F6, KC_F7, _____, _____, _____,   _____,   _____,   _____,
        _PASS,  KC_LEFT, KC_DOWN, KC_RGHT, _____,   _____,  _____, _____, _____, _____, _____,   _____,   KC_MINS, KC_EQL,
        _PASS,  KC_T,    KC_I,    KC_L,    _____,   _____,  _____, _____, _____, _____, KC_LBRC, KC_RBRC, KC_BSLS, _____,
                                  _PASS,   _PASS,   _PASS,                _PASS,   _PASS,   _PASS
    ),
    [OVERLAY] = LAYOUT(
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,               _PASS, _PASS,   _PASS,   _PASS,   _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,   KC_UP,   _PASS,   _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, KC_LEFT, KC_DOWN, KC_RGHT, _PASS, _PASS,
        _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS, _PASS,   _PASS,   _PASS,   _PASS, _PASS,
                      _PASS, _PASS, _PASS,                      _PASS, _PASS,   _PASS
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY] = { ENCODER_CCW_CW(KC_F13, KC_F14), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [EXTRAS] = { ENCODER_CCW_CW(_PASS, _PASS),     ENCODER_CCW_CW(_PASS, _PASS) },
    [OVERLAY] = { ENCODER_CCW_CW(_PASS, _PASS),    ENCODER_CCW_CW(_PASS, _PASS) },
};
// clang-format on

// Color the keys by the active layer: white by default, green for bound keys on EXTRAS, red for non-passthrough keys on OVERLAY
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t active_layer = get_highest_layer(layer_state);
    uint8_t brightness = rgb_matrix_get_val();
    RGB white = hsv_to_rgb((HSV){0, 0, brightness});
    RGB green = hsv_to_rgb((HSV){85, 255, brightness});
    RGB red = hsv_to_rgb((HSV){0, 255, brightness});

    // Base layer is solid white, including non-key LEDs
    if (active_layer != EXTRAS && active_layer != OVERLAY) {
        rgb_matrix_set_color_all(white.r, white.g, white.b);
        return false;
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index == NO_LED || led_index < led_min || led_index >= led_max) {
                continue;
            }

            uint16_t keycode = keymap_key_to_keycode(active_layer, (keypos_t){.row = row, .col = col});
            bool is_unbound = keycode == KC_NO || keycode == KC_TRNS;
            RGB key_color;
            if (active_layer == EXTRAS) {
                key_color = is_unbound ? (RGB){0, 0, 0} : green;
            } else {
                key_color = keycode == KC_TRNS ? white : red;
            }
            rgb_matrix_set_color(led_index, key_color.r, key_color.g, key_color.b);
        }
    }
    return false;
}

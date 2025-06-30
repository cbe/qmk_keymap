/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _BASE_HD, // Hands Down Neu
    _BASE_QW, // QWERTY
    _NUM,
    _NAV,
    _SYM,
    _MED,
    _MOUSE,
    _FN
};

enum custom_keycodes {
    TOGGLE_CAPS_WORD = SAFE_RANGE
};

// Combos
#ifdef COMBO_ENABLE
    const uint16_t PROGMEM toggle_cw[]     = {KC_W, HD2_LRA, COMBO_END};
    const uint16_t PROGMEM num_arrow[]     = {KC_4, KC_EQL , COMBO_END};
    const uint16_t PROGMEM num_colon[]     = {KC_4, KC_ASTR, COMBO_END};
    const uint16_t PROGMEM num_backspace[] = {KC_4, KC_0   , COMBO_END};

    combo_t key_combos[] = {
        COMBO(toggle_cw    , TOGGLE_CAPS_WORD),
        COMBO(num_arrow    , KC_GT  ),
        COMBO(num_colon    , KC_SCLN),
        COMBO(num_backspace, KC_BSPC),
    };
#endif

// Custom Tap-Hold
// See: https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
    if (record->tap.count == 0) {  // Key is being held.
        if (record->event.pressed) {
            tap_code16(long_press_keycode);
        }
        return false;  // Skip default handling.
    }

    return true;  // Continue default handling.
}

// Tapping term per key
const int LAYER_SWITCH_TAPPING_TERM_REDUCTION = 40;
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_NUM,KC_SPC):
        case LT(_NAV,KC_TAB):
        case LT(_MED,KC_ENT):
        case LT(_SYM,KC_BSPC):
        case LT(_FN,XXXXXXX):
            return TAPPING_TERM - LAYER_SWITCH_TAPPING_TERM_REDUCTION;
        default:
            return TAPPING_TERM;
    }
}

// Flow tap per key
// See: https://docs.qmk.fm/tap_hold#is-flow-tap-key
bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys.
    }

    switch (get_tap_keycode(keycode)) {
        case KC_A ... KC_E: // Exclude 'KC_F' as it's required for umlauts (via 'RALT_T', see 'HD2_LRA')
        case KC_G ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }

    return false;
}

// Keep track of the current default layer
int default_layer = _BASE_HD;
void track_default_layer(void) {
    uint32_t layer_state = default_layer_state;

    // Check which layer is active
    if (layer_state & (1UL << _BASE_HD)) {
        default_layer = _BASE_HD;
    } else if (layer_state & (1UL << _BASE_QW)) {
        default_layer = _BASE_QW;
    }
}

// Callbacks
void matrix_scan_user(void) {
    track_default_layer();
}

// Key processing
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Toggle caps word
        case TOGGLE_CAPS_WORD:
            if (record->event.pressed) {
                caps_word_toggle();
            }
            return false;
        // Left click on tap, Middle click on hold
        case MS_BTN1:
            return process_tap_or_long_press_key(record, MS_BTN3);
        // F4 on tap, Alt + F4 on hold
        case C_ALT_F4:
            return process_tap_or_long_press_key(record, LALT(KC_F4));
    }

    return true;
}

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_HD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 DF(_BASE_QW),    KC_W, HD2_LRA, HD2_LME, HD2_LHY,    KC_V,                      KC_SLSH, HD2_RHY, HD2_RME, HD2_RRA,    KC_Z, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, HD3_LGU, HD3_LLA, HD3_LCT, HD3_LSH,    KC_B,                      KC_COMM, HD3_RSH, HD3_RCT, HD3_RLA, HD3_RGU,    KC_J,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_X,    KC_C,    KC_L,    KC_D,    KC_G,                      KC_SCLN,    KC_U,    KC_O,    KC_Y,    KC_K, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,  LT(_NUM,KC_SPC),  LT(_NAV,KC_TAB),     LT(_MED,KC_ENT), LT(_SYM,KC_BSPC), XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_BASE_QW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 DF(_BASE_HD),    KC_Q, HR2_LRA, HR2_LME, HR2_LHY,    KC_T,                         KC_Y, HR2_RHY, HR2_RME, HR2_RRA,    KC_P, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, HR3_LGU, HR3_LLA, HR3_LCT, HR3_LSH,    KC_G,                         KC_H, HR3_RSH, HR3_RCT, HR3_RLA, HR3_RGU, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,  LT(_NUM,KC_SPC),  LT(_NAV,KC_TAB),     LT(_MED,KC_ENT), LT(_SYM,KC_BSPC), XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_RALT,  KC_MEH, KC_HYPR, XXXXXXX,                      KC_MINS,    KC_7,    KC_8,    KC_9, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,LT(_FN,XXXXXXX),               KC_PLUS,    KC_4,    KC_5,    KC_6, KC_ASTR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_DOT,    KC_1,    KC_2,    KC_3,  KC_EQL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         XXXXXXX,         _______,          XXXXXXX,              KC_DEL,             KC_0, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_RALT,  KC_MEH, KC_HYPR, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,A(KC_LEFT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,A(KC_RGHT),XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX,C(S(KC_TAB)),C(KC_TAB), XXXXXXX, QK_LLCK, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,          XXXXXXX,          _______,             XXXXXXX,          XXXXXXX, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      XXXXXXX, KC_HYPR,  KC_MEH, KC_RALT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CIRC, KC_LCBR, KC_LBRC, KC_LPRN, KC_TILD,                      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_AMPR, KC_RCBR, KC_RBRC, KC_RPRN,  KC_GRV,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,           KC_SPC,          KC_BSLS,             XXXXXXX,          _______, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_MED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MUTE, UG_TOGG,                      XXXXXXX, KC_HYPR,  KC_MEH, KC_RALT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   XXXXXXX,XXXXXXX,HYPR(KC_F12), KC_MNXT, KC_VOLU, UG_VALU,                      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, UG_VALD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,          XXXXXXX,          XXXXXXX,             _______,          XXXXXXX, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_RALT,  KC_MEH, KC_HYPR, XXXXXXX,                      MS_WHLU, MS_WHLL,   MS_UP, MS_WHLR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LLCK, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,          XXXXXXX,          _______,             MS_BTN2,          MS_BTN1, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  ),

    [_FN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_RALT,  KC_MEH, KC_HYPR, XXXXXXX,                       KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                       KC_F11,C_ALT_F4,   KC_F5,   KC_F6, KC_SCRL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        XXXXXXX,          XXXXXXX,          XXXXXXX,             QK_BOOT,          XXXXXXX, XXXXXXX
                    //`--------------------------------------------'  `--------------------------------------------'
  )
};

// Layer template
// [___] = LAYOUT_split_3x6_3(
//     //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//     //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//     //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//     //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                           XXXXXXX,          XXXXXXX,          XXXXXXX,             XXXXXXX,          XXXXXXX, XXXXXXX
//                       //`--------------------------------------------'  `--------------------------------------------'
//     ),

#ifdef OLED_ENABLE
    static void render_image(void) {
        static const char PROGMEM boba_fett[] = {
            0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
            0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F,
            0x3F, 0x3F, 0x1F, 0x1F, 0x7F, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0x00, 0xDB, 0xDB, 0xDB,
            0x5B, 0xFF, 0xFF, 0xFF, 0xFF, 0x9B,
            0xC3, 0xDF, 0xFF, 0x5F, 0xFF, 0xBD,
            0xFC, 0xDE, 0xFF, 0xFD, 0xFF, 0xFF,
            0xFF, 0x6F, 0x7F, 0x7F, 0x7F, 0x7F,
            0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
            0xFF, 0xFB, 0xE1, 0xE1, 0xC1, 0x80,
            0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
            0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
            0x7F, 0x7F, 0xFF, 0xFF, 0xDF, 0xCF,
            0xCF, 0x1F, 0x1F, 0x0B, 0x03, 0x63,
            0x23, 0x23, 0x23, 0x23, 0x61, 0x41,
            0x41, 0xE0, 0xF0, 0xF8, 0xF0, 0xF0,
            0xF0, 0xF0, 0x60, 0x60, 0x60, 0x30,
            0x30, 0xD8, 0xEC, 0xFC, 0xF0, 0x60,
            0xC0, 0x81, 0x07, 0x7F, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD,
            0x7D, 0x7F, 0x7F, 0x7F, 0x3F, 0x1F,
            0xBF, 0xFF, 0xFF, 0xFF, 0xE0, 0xED,
            0xE0, 0xED, 0xEC, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFD, 0x3D, 0x1E, 0x1F, 0x9F,
            0xD7, 0x5F, 0x2F, 0x03, 0x61, 0xF8,
            0xB8, 0xF8, 0x78, 0x78, 0x78, 0xB8,
            0xB8, 0x90, 0x98, 0x98, 0xD8, 0xC8,
            0xCD, 0xC7, 0xCF, 0x83, 0x01, 0x01,
            0x00, 0x01, 0x00, 0x01, 0x01, 0x01,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            0xC1, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xF9,
            0xF9, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC,
            0xFC, 0xFC, 0xFC, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0x7F, 0x10, 0x00, 0x80,
            0xD8, 0xFC, 0xFC, 0x40, 0x60, 0x70,
            0xF0, 0xBE, 0x03, 0x3B, 0x93, 0xC3,
            0x81, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x48, 0xDA, 0xDF, 0xEF, 0xFD,
            0xFF, 0x00, 0x00, 0x01, 0x02, 0x0C,
            0x3F, 0xFF, 0xFF, 0xFF, 0x3F, 0x3D,
            0x1E, 0x1C, 0x00, 0x00, 0x00, 0x00,
            0x00, 0xF3, 0xFB, 0xF9, 0x7D, 0x3F,
            0x1F, 0x0F, 0x0F, 0x13, 0x89, 0xCF,
            0xE3, 0xE1, 0xF1, 0xF0, 0xF8, 0xF8,
            0xFC, 0xFC, 0xFE, 0x7E, 0x0E, 0x02,
            0x01, 0x81, 0xA0, 0xFE, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xEF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFD, 0xFD, 0xFD, 0xFC,
            0xF4, 0xFC, 0xF9, 0xFF, 0xF0, 0xF0,
            0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
            0x00, 0x37, 0x33, 0x0B, 0x01, 0x01,
            0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFC,
            0xFE, 0xFF, 0x3F, 0x07, 0x01, 0x00,
            0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x06, 0x00, 0x07, 0xFF, 0xE8, 0x00,
            0x00, 0x03, 0x07, 0x0F, 0x1F, 0x3E,
            0x3C, 0x7C, 0xB8, 0x77, 0x1F, 0x1F,
            0x1F, 0x1F, 0x09, 0x08, 0x08, 0x08,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0B,
            0x88, 0x00, 0x00, 0x00, 0x00, 0xE0,
            0x02, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x30, 0x78, 0x7C, 0x7E, 0x3F, 0x1F,
            0x9F, 0xCF, 0xC7, 0xE7, 0xE3, 0xE3,
            0xE1, 0xF1, 0xF0, 0xF8, 0xE0, 0x00,
            0x00, 0x01, 0x01, 0x03, 0x07, 0x07,
            0x0F, 0x0F, 0x0F, 0x07, 0x0F, 0x07,
            0x07, 0x07, 0x07, 0x07, 0x07, 0x03,
            0x03, 0x03, 0x03, 0x01, 0x01, 0x01,
            0x01, 0x81, 0x80, 0x81, 0xC1, 0xC0,
            0xC0, 0x60, 0x60, 0x20, 0x20, 0x30,
            0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00,
        };

        oled_write_raw_P((boba_fett), sizeof(boba_fett));
    };

    bool oled_task_user() {
        if (is_keyboard_master()) {
            // Left screen
            // Operating system
            oled_write("OS: ", false);
            const os_variant_t detected_os = detected_host_os();
            switch (detected_os) {
                case OS_LINUX:
                    oled_write("Linux", false);
                    break;
                case OS_MACOS:
                    oled_write("MacOS", false);
                    break;
                case OS_WINDOWS:
                    oled_write("Windows", false);
                    break;
                case OS_IOS:
                    oled_write("iOS", false);
                    break;
                case OS_UNSURE:
                    oled_write("Unknown", false);
                    break;
            }
            oled_advance_page(true);

            // Layer
            oled_write("Layer: ", false);
            if (get_highest_layer(layer_state) <= _BASE_QW) {
                switch (default_layer) {
                    case _BASE_HD:
                        oled_write("base [rsnt]", false);
                        break;
                    case _BASE_QW:
                        oled_write("base [asdf]", false);
                        break;
                }
            } else {
                switch (get_highest_layer(layer_state)) {
                    case _BASE_HD:
                    case _BASE_QW:
                        // Do nothing as it has to be handled differently, see `track_default_layer`
                        break;
                    case _NUM:
                        oled_write("numbers", false);
                        break;
                    case _NAV:
                        oled_write("navigation", false);
                        break;
                    case _SYM:
                        oled_write("symbols", false);
                        break;
                    case _MED:
                        oled_write("media", false);
                        break;
                    case _MOUSE:
                        oled_write("mouse", false);
                        break;
                    case _FN:
                        oled_write("function", false);
                        break;
                }
            }
            oled_advance_page(true);

            // Active modifiers
            uint8_t active_modifiers = get_mods() | get_oneshot_mods();
            oled_write("Modifier: ", false);
            if (!active_modifiers) {
                oled_write("-", false);
            }
            if (active_modifiers & MOD_MASK_GUI) {
                oled_write("G", false);
            }
            if (active_modifiers & MOD_MASK_ALT) {
                oled_write("A", false);
            }
            if (active_modifiers & MOD_MASK_CTRL) {
                oled_write("C", false);
            }
            if (active_modifiers & MOD_MASK_SHIFT) {
                oled_write("S", false);
            }
            oled_advance_page(true);

            // Caps word
            bool caps_word_state = is_caps_word_on();
            oled_write("Caps word: ", false);
            oled_write_P(caps_word_state ? PSTR("on") : PSTR("off"), false);
            oled_advance_page(true);
        } else {
            // Right screen
            render_image();
        }

        return false;
    }
#endif

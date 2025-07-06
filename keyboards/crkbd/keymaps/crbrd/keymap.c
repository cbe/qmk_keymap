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

#include "combos.c"
#include "tap_dances.c"
#include "flow_tap.c"
#include "oled.c"

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
        case TD(TD_TNM):
        case LT(_MED,KC_ENT):
        case LT(_SYM,KC_BSPC):
        case LT(_FN,XXXXXXX):
            return TAPPING_TERM - LAYER_SWITCH_TAPPING_TERM_REDUCTION;
        default:
            return TAPPING_TERM;
    }
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
                        XXXXXXX,  LT(_NUM,KC_SPC),       TD(TD_TNM),     LT(_MED,KC_ENT), LT(_SYM,KC_BSPC), XXXXXXX
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
                        XXXXXXX,  LT(_NUM,KC_SPC),       TD(TD_TNM),     LT(_MED,KC_ENT), LT(_SYM,KC_BSPC), XXXXXXX
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

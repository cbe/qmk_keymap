/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#define CHORDAL_HOLD
#define FLOW_TAP_TERM 150
#define OLED_TIMEOUT 10000
#define PERMISSIVE_HOLD
#define TAPPING_TERM 220

// Custom keycodes to keep keymap a little less cluttered, see:
// https://docs.qmk.fm/faq_keymap#how-can-i-make-custom-names-for-complex-keycodes
// Home Row Mods Row 3
#define HR3_LGU LGUI_T(KC_A)
#define HR3_LLA LALT_T(KC_S)
#define HR3_LCT LCTL_T(KC_D)
#define HR3_LSH LSFT_T(KC_F)
#define HR3_RSH RSFT_T(KC_J)
#define HR3_RCT RCTL_T(KC_K)
#define HR3_RLA LALT_T(KC_L)
#define HR3_RGU RGUI_T(KC_SCLN)
// Home Row Mods Row Row 2
#define HR2_LRA RALT_T(KC_W)
#define HR2_LME MEH_T(KC_E)
#define HR2_LHY ALL_T(KC_R)
#define HR2_RHY ALL_T(KC_U)
#define HR2_RME MEH_T(KC_I)
#define HR2_RRA RALT_T(KC_O)
// Hands Down Neu
// Home Row Mods Row 3
#define HD3_LGU LGUI_T(KC_R)
#define HD3_LLA LALT_T(KC_S)
#define HD3_LCT LCTL_T(KC_N)
#define HD3_LSH LSFT_T(KC_T)
#define HD3_RSH RSFT_T(KC_A)
#define HD3_RCT RCTL_T(KC_E)
#define HD3_RLA LALT_T(KC_I)
#define HD3_RGU RGUI_T(KC_H)
// Home Row Mods Row Row 2
#define HD2_LRA RALT_T(KC_F)
#define HD2_LME MEH_T(KC_M)
#define HD2_LHY ALL_T(KC_P)
#define HD2_RHY ALL_T(KC_DOT)
#define HD2_RME MEH_T(KC_Q)
#define HD2_RRA RALT_T(KC_QUOT)

// Custom Tap-Hold
#define C_ALT_F4 LT(0, KC_F4)

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 64

    // Custom colors
    #define RGB_CATPPUCCIN_SKY 0x04, 0xA5, 0xE5
    #define RGB_CATPPUCCIN_GREEN 0x40, 0xA0, 0x2B
    #define RGB_CATPPUCCIN_YELLOW 0xDF, 0x8E, 0x1D
    #define RGB_CATPPUCCIN_MAROON 0xE6, 0x45, 0x53
    #define RGB_CATPPUCCIN_MAUVE 0x88, 0x39, 0xEF
    #define RGB_CATPPUCCIN_PINK 0xEA, 0x76, 0xCB

    // Disable all animations to save space
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_BREATHING
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_KNIGHT
    #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
    #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #undef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_STATIC_GRADIENT
    #undef RGBLIGHT_EFFECT_TWINKLE
#endif

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
#define OLED_TIMEOUT 15000
#define QUICK_TAP_TERM 120
#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY

// Custom keycodes to keep keymap a little less cluttered, see:
// https://docs.qmk.fm/faq_keymap#how-can-i-make-custom-names-for-complex-keycodes
// Home Row Mods
// QWERTY
#define HR3_LGU LGUI_T(KC_A)
#define HR3_LLA LALT_T(KC_S)
#define HR3_LCT LCTL_T(KC_D)
#define HR3_LSH LSFT_T(KC_F)
#define HR3_RSH RSFT_T(KC_J)
#define HR3_RCT RCTL_T(KC_K)
#define HR3_RLA LALT_T(KC_L)
#define HR3_RGU RGUI_T(KC_SCLN)
#define HR2_LRA RALT_T(KC_W)
#define HR2_LME MEH_T(KC_E)
#define HR2_LHY ALL_T(KC_R)
#define HR2_RHY ALL_T(KC_U)
#define HR2_RME MEH_T(KC_I)
#define HR2_RRA RALT_T(KC_O)
// Hands Down Neu
#define HR_F RALT_T(KC_F)
#define HR_M MEH_T(KC_M)
#define HR_P ALL_T(KC_P)
#define HR_DOT ALL_T(KC_DOT)
#define HR_Q MEH_T(KC_Q)
#define HR_QUO RALT_T(KC_QUOT)
#define HR_R LGUI_T(KC_R)
#define HR_S LALT_T(KC_S)
#define HR_N LCTL_T(KC_N)
#define HR_T LSFT_T(KC_T)
#define HR_A RSFT_T(KC_A)
#define HR_E RCTL_T(KC_E)
#define HR_I LALT_T(KC_I)
#define HR_H RGUI_T(KC_H)

// Custom keycodes
#define C_SWIN   G(KC_GRV)    // Switch window instance
#define C_PTAB   C(S(KC_TAB)) // Previous tab
#define C_NTAB   C(KC_TAB)    // Next tab
// Custom Tap-Hold
#define C_ALT_F4 LT(0, KC_F4)
#define C_MS_CLK LT(0, MS_BTN1)

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef MOUSEKEY_ENABLE
    #define MOUSEKEY_DELAY 2
    #define MOUSEKEY_INTERVAL 15
    #define MOUSEKEY_MAX_SPEED 8
    #define MOUSEKEY_TIME_TO_MAX 80
#endif

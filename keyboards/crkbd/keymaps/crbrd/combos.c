/*
Copyright 2025 @cbe

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

#ifdef COMBO_ENABLE
    const uint16_t PROGMEM toggle_cw[]     = {KC_W, HR_F,    COMBO_END};
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

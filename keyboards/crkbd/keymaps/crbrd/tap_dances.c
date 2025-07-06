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

#ifdef TAP_DANCE_ENABLE
    enum {
        TD_TNM, // Tab/Navigation/Mouse
    };

    // Possible tap dance states
    typedef enum {
        TD_NONE,
        TD_UNKNOWN,
        TD_SINGLE_TAP,
        TD_SINGLE_HOLD,
        TD_DOUBLE_TAP,
        TD_DOUBLE_TAP_HOLD
    } td_state_t;
    static td_state_t td_state;

    td_state_t cur_dance(tap_dance_state_t *state);

    void dance_enter_mouse_media_finished(tap_dance_state_t *state, void *user_data) {
        td_state = cur_dance(state);
        switch (td_state) {
            case TD_SINGLE_TAP:
                register_code16(KC_TAB);
                break;
            case TD_SINGLE_HOLD:
                layer_on(_NAV);
                break;
            case TD_DOUBLE_TAP_HOLD:
                layer_on(_MOUSE);
                break;
            default:
                break;
        }
    }

    void dance_enter_mouse_media_reset(tap_dance_state_t *state, void *user_data) {
        switch (td_state) {
            case TD_SINGLE_TAP:
                unregister_code16(KC_TAB);
                break;
            case TD_SINGLE_HOLD:
                layer_off(_NAV);
                break;
            case TD_DOUBLE_TAP_HOLD:
                layer_off(_MOUSE);
                break;
            default:
                break;
        }
    }

    tap_dance_action_t tap_dance_actions[] = {
        [TD_TNM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_enter_mouse_media_finished, dance_enter_mouse_media_reset),
    };

    // Determine the tapdance state to return
    td_state_t cur_dance(tap_dance_state_t *state) {
        if (state->count == 1) {
            if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        }
        if (state->count == 2) {
            if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
            else return TD_DOUBLE_TAP_HOLD;
        }
        else return TD_UNKNOWN;
    }
#endif

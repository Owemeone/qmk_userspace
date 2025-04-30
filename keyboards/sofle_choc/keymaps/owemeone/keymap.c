/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// #include <stdint.h>
#pragma once
#include <stdint.h>
#include "raw_hid.h"
#include QMK_KEYBOARD_H

enum choc_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _OLED
};

enum my_keycodes {
    TM_BUTN = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    LT(1,KC_GRV),   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                      KC_LCTL, KC_LGUI, KC_LCMD, KC_LALT, KC_ENT,    KC_SPC, KC_RALT,  KC_RCMD,  KC_RGUI, KC_RCTL
),
[_OLED] = LAYOUT(
    _______, _______, _______, _______, _______, QK_BOOT,                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
    TM_BUTN, TM_BUTN, _______, _______, _______, QK_RBT,  _______,      RM_TOGG, _______, _______, _______, _______,  _______, _______,
                      _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_OLED] = { ENCODER_CCW_CW(RM_NEXT, RM_PREV), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }
};
#endif

#ifdef OLED_ENABLE

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 3; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (is_keyboard_master()) {
    //     return OLED_ROTATION_180;
    // }
    return rotation;
}

bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _OLED:
            oled_write_P(PSTR("OLED\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    #ifdef RGB_MATRIX_ENABLE
    switch (rgb_matrix_get_mode()) {
        case 1:
            oled_write_ln_P(PSTR("Solid Color\n"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Alphas Mods\n"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Gradient Up Down\n"), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("Gradient Left Right\n"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("Breathing\n"), false);
            break;
        case 6:
            oled_write_ln_P(PSTR("Band Sat\n"), false);
            break;
        case 7:
            oled_write_ln_P(PSTR("Band Val\n"), false);
            break;
        case 8:
            oled_write_ln_P(PSTR("Band Pinwheel Sat\n"), false);
            break;
        case 9:
            oled_write_ln_P(PSTR("Band Pinwheel Val\n"), false);
            break;
        case 10:
            oled_write_ln_P(PSTR("Band Spiral Sat\n"), false);
            break;
        case 11:
            oled_write_ln_P(PSTR("Band Spiral Val\n"), false);
            break;
        case 12:
            oled_write_ln_P(PSTR("Cycle All\n"), false);
            break;
        case 13:
            oled_write_ln_P(PSTR("Cycle Left Right\n"), false);
            break;
        case 14:
            oled_write_ln_P(PSTR("Cycle Up Down\n"), false);
            break;
        case 15:
            oled_write_ln_P(PSTR("Rainbow\nMoving Chevron"), false);
            break;
        case 16:
            oled_write_ln_P(PSTR("Cycle Out In\n"), false);
            break;
        case 17:
            oled_write_ln_P(PSTR("Cycle Out In Dual\n"), false);
            break;
        case 18:
            oled_write_ln_P(PSTR("Cycle Pinwheel\n"), false);
            break;
        case 19:
            oled_write_ln_P(PSTR("Cycle Spiral\n"), false);
            break;
        case 20:
            oled_write_ln_P(PSTR("Dual Beacon\n"), false);
            break;
        case 21:
            oled_write_ln_P(PSTR("Rainbow Beacon\n"), false);
            break;
        case 22:
            oled_write_ln_P(PSTR("Rainbow Pinwheels\n"), false);
            break;
        case 23:
            oled_write_ln_P(PSTR("Raindrops\n"), false);
            break;
        case 24:
            oled_write_ln_P(PSTR("Jellybean Raindrops\n"), false);
            break;
        case 25:
            oled_write_ln_P(PSTR("Hue Breathing\n"), false);
            break;
        case 26:
            oled_write_ln_P(PSTR("Hue Pendulum\n"), false);
            break;
        case 27:
            oled_write_ln_P(PSTR("Hue Wave\n"), false);
            break;
        case 28:
            oled_write_ln_P(PSTR("Pixel Rain\n"), false);
            break;
        case 29:
            oled_write_ln_P(PSTR("Pixel Flow\n"), false);
            break;
        case 30:
            oled_write_ln_P(PSTR("Pixel Fractal\n"), false);
            break;
        case 31:
            oled_write_ln_P(PSTR("Typing Heatmap\n"), false);
            break;
        case 32:
            oled_write_ln_P(PSTR("Digital Rain\n"), false);
            break;
        case 33:
            oled_write_ln_P(PSTR("Solid Reactive\nSimple"), false);
            break;
        case 34:
            oled_write_ln_P(PSTR("Solid Reactive\n"), false);
            break;
        case 35:
            oled_write_ln_P(PSTR("Solid Reactive\nWide"), false);
            break;
        case 36:
            oled_write_ln_P(PSTR("Solid Reactive\nMultiwide"), false);
            break;
        case 37:
            oled_write_ln_P(PSTR("Solid Reactive\nCross"), false);
            break;
        case 38:
            oled_write_ln_P(PSTR("Solid Reactive\nMulticross"), false);
            break;
        case 39:
            oled_write_ln_P(PSTR("Solid Reactive\nNexus"), false);
            break;
        case 40:
            oled_write_ln_P(PSTR("Solid Reactive\nMultinexus"), false);
            break;
        case 41:
            oled_write_ln_P(PSTR("Splash\n"), false);
            break;
        case 42:
            oled_write_ln_P(PSTR("Multisplash\n"), false);
            break;
        case 43:
            oled_write_ln_P(PSTR("Solid Splash\n"), false);
            break;
        case 44:
            oled_write_ln_P(PSTR("Solid Multisplash\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }
    #endif
    oled_write_P(PSTR("OS: "), false);
    switch (detected_host_os()) {
        case OS_UNSURE:
            oled_write_P(PSTR("Unsure           "), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("Linux            "), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("Windows          "), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR("MacOS            "), false);
            break;
        case OS_IOS:
            oled_write_P(PSTR("iOS              "), false);
            break;
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}

#endif

#ifdef RAW_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    switch (keycode) {
      case TM_BUTN:
        print("In raw button pressed");
        if (record->event.pressed) {
            printf("In pressed");
            // Do something when pressed
            uint8_t report[32];
            memset(report, 0, 32);

            report[0] = 0x9B;
            raw_hid_send(report, 32);
            printf("Sent raw hid");
        } else {
          // Do something else when release
        }
        return false; // Skip all further processing of this key
      default:
        return true; // Process all other keycodes normally
    }
  }
#endif

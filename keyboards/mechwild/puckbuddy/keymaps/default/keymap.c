// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

<<<<<<< HEAD
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

=======
>>>>>>> f71ee6074f1021dea83d0ee9931f08d60f38c806
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

/*   Physical Layout:
 *   /-------------------\
 *   |ENC| 1 | 2 | 3 |ENC|
 *   |---+---'---'---+---|
 *   | 4 |           | 5 |
 *   |---|           |---|
 *   | 6 |           | 7 |
 *   |---|           |---|
 *   | 8 |           | 9 |
 *   \-----,---,---,-----/
 *     | A | B | C | D |
 *     \---'---'---'---/
 *
 *   Keymap Layout:
 *   ENC, 1, 2, 3,    ENC,
 *   4,               5,
 *   6,               7,
 *   8,   A, B, C, D, 9,
 *   
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    KC_MUTE,  MO(_FN3), MO(_FN2), MO(_FN1),       LGUI(KC_D),
    MO(_FN2),                                     KC_HOME,
    MO(_FN3),                                     KC_END,
<<<<<<< HEAD
    KC_BTN3,  KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, DPI_FINE
=======
    KC_BTN3,                                      DPI_FINE,
              KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1
>>>>>>> f71ee6074f1021dea83d0ee9931f08d60f38c806
    ),
    [_FN1] = LAYOUT(
    RGB_TOG, KC_TRNS, KC_TRNS, KC_TRNS,          TAP_TOG,
    DPI_UP,                                      TAP_UP,
    DPI_DN,                                      TAP_DN,
<<<<<<< HEAD
    KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_TRNS
=======
    KC_TRNS,                                     KC_TRNS,
             KC_HOME, KC_PGUP, KC_PGDN, KC_END
>>>>>>> f71ee6074f1021dea83d0ee9931f08d60f38c806
    ),
    [_FN2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_TOG,
    KC_TRNS,                                     RGB_MOD,
    KC_TRNS,                                     RGB_RMOD,
<<<<<<< HEAD
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RESET,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
=======
    KC_TRNS,                                     KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FN3] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          QK_BOOT,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS,                                     KC_TRNS,
    KC_TRNS,                                     KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
>>>>>>> f71ee6074f1021dea83d0ee9931f08d60f38c806
    )
};

// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "puckbuddy.h"

#ifndef GLIDEPOINT_DPI_OPTIONS
#    define GLIDEPOINT_DPI_OPTIONS \
        { 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000 }
#    ifndef GLIDEPOINT_DPI_DEFAULT
#        define GLIDEPOINT_DPI_DEFAULT 1
#    endif
#endif
#ifndef GLIDEPOINT_DPI_DEFAULT
#    define GLIDEPOINT_DPI_DEFAULT 1
#endif

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = GLIDEPOINT_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    setPinInputHigh(B9);
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) { 
    if (!dip_switch_update_user(index, active)) { return false; }
    switch (index) {
        case 0:
            if(active) { tap_code(KC_CLCK); }
            break;
        break;
    }
    return true;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_PGDN);
            }
        break;
    }
    return true;
}
#endif

#ifdef OLED_ENABLE   // OLED Functionality
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;       // flips the display 180 degrees
}

bool clear_screen = false;          // used to manage singular screen clears to prevent display glitch
static void render_name(void) {     // Render Puckbuddy "Get Puck'd" text
    static const char PROGMEM name_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0xB6, 0xB6, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92};
    static const char PROGMEM name_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xB6, 0xB6, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2};
    static const char PROGMEM name_3[] = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xB6, 0xB6, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2};
    oled_set_cursor(0,0);
    oled_write_P(name_1, false);
    oled_set_cursor(0,1);
    oled_write_P(name_2, false);
    oled_set_cursor(0,2);
    oled_write_P(name_3, false);
}

static void render_logo(void) {     // Render MechWild "MW" Logo
    static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
    static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
    static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
    static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
    oled_set_cursor(0,0);
    oled_write_P(logo_1, false);
    oled_set_cursor(0,1);
    oled_write_P(logo_2, false);
    oled_set_cursor(0,2);
    oled_write_P(logo_3, false);
    oled_set_cursor(0,3);
    oled_write_P(logo_4, false);
}

bool oled_task_kb(void) {
    if ( IS_HOST_LED_OFF(USB_LED_NUM_LOCK) && IS_HOST_LED_OFF(USB_LED_CAPS_LOCK) && get_highest_layer(layer_state) == 0 ) {
        render_name();
        oled_set_cursor(0,3);
        switch (keyboard_config.dpi_config) {   // { 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000 }
            case 0:
                oled_write_P(PSTR("      DPI: 400       "), false);
                break;
            case 1:
                oled_write_P(PSTR("      DPI: 800       "), false);
                break;
            case 2:
                oled_write_P(PSTR("      DPI: 1200      "), false);
                break;
            case 3:
                oled_write_P(PSTR("      DPI: 1600      "), false);
                break;
            case 4:
                oled_write_P(PSTR("      DPI: 2000      "), false);
                break;
            case 5:
                oled_write_P(PSTR("      DPI: 2400      "), false);
                break;
            case 6:
                oled_write_P(PSTR("      DPI: 2800      "), false);
                break;
            case 7:
                oled_write_P(PSTR("      DPI: 3200      "), false);
                break;
            case 8:
                oled_write_P(PSTR("      DPI: 3600      "), false);
                break;
            case 9:
                oled_write_P(PSTR("      DPI: 4000      "), false);
                break;
            default:
                oled_write_P(PSTR("      DPI: ????      "), false);    // Should never display, here as a catchall
        }
        clear_screen = true;
    } else {
        if (clear_screen == true) {
            oled_clear();
            oled_render();
            clear_screen = false;
        }
        render_logo();
        oled_set_cursor(8,2);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Layer 0"), false);
                break;
            case 1:
                oled_write_P(PSTR("Layer 1"), false);
                break;
            case 2:
                oled_write_P(PSTR("Layer 2"), false);
                break;
            case 3:
                oled_write_P(PSTR("Layer 3"), false);
                break;
            default:
                oled_write_P(PSTR("Layer ?"), false);    // Should never display, here as a catchall
        }
        led_t led_state = host_keyboard_led_state();
        oled_set_cursor(8,0);
        oled_write_P(led_state.scroll_lock ? PSTR("SCRLK") : PSTR("     "), false);
        oled_set_cursor(8,1);
        oled_write_P(led_state.num_lock ? PSTR("NLCK ") : PSTR("     "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
        oled_set_cursor(8,3);
        switch (keyboard_config.dpi_config) {   // 512, 1024, 2048, 3072, 4096
            case 0:
                oled_write_P(PSTR("DPI: 400 "), false);
                break;
            case 1:
                oled_write_P(PSTR("DPI: 800 "), false);
                break;
            case 2:
                oled_write_P(PSTR("DPI: 1200"), false);
                break;
            case 3:
                oled_write_P(PSTR("DPI: 1600"), false);
                break;
            case 4:
                oled_write_P(PSTR("DPI: 2000"), false);
                break;
            case 5:
                oled_write_P(PSTR("DPI: 2400"), false);
                break;
            case 6:
                oled_write_P(PSTR("DPI: 2800"), false);
                break;
            case 7:
                oled_write_P(PSTR("DPI: 3200"), false);
                break;
            case 8:
                oled_write_P(PSTR("DPI: 3600"), false);
                break;
            case 9:
                oled_write_P(PSTR("DPI: 4000"), false);
                break;
            default:
                oled_write_P(PSTR("DPI: ????"), false);    // Should never display, here as a catchall
        }
    }
    return false;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case DPI_UP:
            if (record->event.pressed) {
                keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_DN:
            if (record->event.pressed) {
                if (keyboard_config.dpi_config > 0) {
                    keyboard_config.dpi_config = (keyboard_config.dpi_config - 1) % DPI_OPTION_SIZE;
                } else {
                    keyboard_config.dpi_config = DPI_OPTION_SIZE - 1;
                }
                eeconfig_update_kb(keyboard_config.raw);
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }
            return false;
        case DPI_FINE:
            if (record->event.pressed) {
                pointing_device_set_cpi(dpi_array[0]);
            } else {
                pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
            }                
            return false;
    }
    return process_record_user(keycode, record);
}

void pointing_device_init_kb(void) {
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = GLIDEPOINT_DPI_DEFAULT;
    eeconfig_update_kb(keyboard_config.raw);
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}

void keyboard_post_init_kb(void) {
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);

    keyboard_post_init_user();
    
    rgblight_toggle_noeeprom();     //double toggle post init removes the weirdness with rgb strips having a yellow first LED
    rgblight_toggle_noeeprom();

}

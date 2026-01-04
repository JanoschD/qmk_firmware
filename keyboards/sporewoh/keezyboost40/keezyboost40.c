/*
Copyright 2022 sporewoh

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

#include "keezyboost40.h"

#include <string.h>
#include "quantum.h"
#include <hal_pal.h>
#include "hal.h"
#include "stdlib.h"

#include "qp.h"
#include "qp_comms.h"
#include "qp_st77xx_opcodes.h"

#include "thintel15.qff.c"


#include "layer_names.h"

static painter_device_t lcd;
static painter_font_handle_t font;

void ui_init(void) {

    // Turn on the LCD
    gpio_set_pin_output(GP15);
    gpio_write_pin_high(GP15);

    // Let the LCD get some power...
    wait_ms(LCD_WAIT_TIME);

    // Initialise the LCD
    lcd = qp_st7789_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);

    qp_init(lcd, LCD_ROTATION);
    
    // Disable color inversion (driver enables it by default)
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_OFF);
    qp_comms_stop(lcd);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);

    // begin drawing space
    qp_rect(lcd, 0, 0, LCD_WIDTH, LCD_HEIGHT, HSV_BLACK, true);

    font = qp_load_font_mem(font_thintel15);
}

void keyboard_post_init_kb(void) {
    ui_init();
    // Allow for user post-init
    keyboard_post_init_user();
}

void ui_task(void) {
    static uint8_t last_layer = 0xFF;  // Track last layer
    static bool last_os_mode = false;  // Track last OS mode
    static bool last_lang_mode = false;  // Track last language mode
    static bool last_shift_state = false;  // Track shift state
    static bool last_caps_state = false;   // Track caps lock state
    static bool initialized = false;   // Track first run
    
    extern bool is_linux;
    extern bool is_french;
    uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);
    
    // Get current shift and caps lock states
    bool shift_pressed = get_mods() & MOD_MASK_SHIFT;
    bool caps_locked = host_keyboard_led_state().caps_lock;
    
    // Only redraw if something changed
    bool layer_changed = (current_layer != last_layer);
    bool os_changed = (is_linux != last_os_mode);
    bool lang_changed = (is_french != last_lang_mode);
    bool shift_changed = (shift_pressed != last_shift_state);
    bool caps_changed = (caps_locked != last_caps_state);
    
    if (!layer_changed && !os_changed && !lang_changed && !shift_changed && !caps_changed && initialized) {
        return;  // Nothing to update
    }
    
    if (font == NULL) {
        return;  // Font not loaded, skip update
    }

    // Calculate the maximum width of the labels to align the values.
    int16_t value_x_pos = 20;
    if (layer_changed || os_changed || shift_changed || caps_changed || lang_changed || !initialized) {
        const char *labels[] = {"Layer:", "OS:", "Shift:", "Caps:", "Lang:"};
        int16_t     max_width = 0;
        for (uint8_t i = 0; i < 5; i++) {
            int16_t w = qp_textwidth(font, labels[i]);
            if (w > max_width) {
                max_width = w;
            }
        }
        value_x_pos += max_width + 5; // 5 pixels for spacing
    }

    if (layer_changed || !initialized) {
        // Draw layer text
        static const char *text  = "Layer:";
        qp_drawtext_recolor(lcd, 20, 140, font, text, HSV_RED, HSV_BLACK);
        
        // clear previous layer name
        qp_rect(lcd, value_x_pos, 140, LCD_WIDTH - 1, 140 + font->line_height, HSV_BLACK, true);

        const char *layer_name;
        switch (current_layer) {
            case _AZ:      layer_name = "AZERTY"; break;
            case _AZ_EN:   layer_name = "AZERTY_EN"; break;
            case _NUM:     layer_name = "NUMBER"; break;
            case _NUM_EN:  layer_name = "NUMBER_EN"; break;
            case _SYMB:    layer_name = "SYMBOL"; break;
            case _SYMB_EN: layer_name = "SYMBOL_EN"; break;
            case _FNTN:    layer_name = "FUNCTION"; break;
            case _FNTN_EN: layer_name = "FUNCTION_EN"; break;
            case _LANG:    layer_name = "LANGUAGE"; break;
            default:       layer_name = "_PANIC_"; break;
        }
        qp_drawtext_recolor(lcd, value_x_pos, 140, font, layer_name, HSV_RED, HSV_BLACK);
        
        last_layer = current_layer;
    }
    
    if (os_changed || !initialized) {
        // Draw OS text
        static const char *os_text = "OS:";
        qp_drawtext_recolor(lcd, 20, 120, font, os_text, HSV_RED, HSV_BLACK);
        
        qp_rect(lcd, value_x_pos, 120, LCD_WIDTH - 1, 120 + font->line_height, HSV_BLACK, true);

        if (is_linux) {
            qp_drawtext_recolor(lcd, value_x_pos, 120, font, "Linux", HSV_RED, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd, value_x_pos, 120, font, "Windows", HSV_RED, HSV_BLACK);
        }
        last_os_mode = is_linux;
    }
    
    if (shift_changed || !initialized) {
        // Draw Shift status
        static const char *shift_text = "Shift:";
        qp_drawtext_recolor(lcd, 20, 100, font, shift_text, HSV_RED, HSV_BLACK);

        qp_rect(lcd, value_x_pos, 100, LCD_WIDTH - 1, 100 + font->line_height, HSV_BLACK, true);
        
        if (shift_pressed) {
            qp_drawtext_recolor(lcd, value_x_pos, 100, font, "ON", HSV_RED, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd, value_x_pos, 100, font, "OFF", HSV_RED, HSV_BLACK);
        }
        last_shift_state = shift_pressed;
    }
    
    if (caps_changed || !initialized) {
        // Draw Caps Lock status
        static const char *caps_text = "Caps:";
        qp_drawtext_recolor(lcd, 20, 80, font, caps_text, HSV_RED, HSV_BLACK);

        qp_rect(lcd, value_x_pos, 80, LCD_WIDTH - 1, 80 + font->line_height, HSV_BLACK, true);
        
        if (caps_locked) {
            qp_drawtext_recolor(lcd, value_x_pos, 80, font, "ON", HSV_RED, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd, value_x_pos, 80, font, "OFF", HSV_RED, HSV_BLACK);
        }
        last_caps_state = caps_locked;
    }

    if (lang_changed || !initialized) {
        // Draw Language text
        static const char *lang_text = "Lang:";
        qp_drawtext_recolor(lcd, 20, 60, font, lang_text, HSV_RED, HSV_BLACK);

        qp_rect(lcd, value_x_pos, 60, LCD_WIDTH - 1, 60 + font->line_height, HSV_BLACK, true);

        if (is_french) {
            qp_drawtext_recolor(lcd, value_x_pos, 60, font, "French", HSV_RED, HSV_BLACK);
        } else {
            qp_drawtext_recolor(lcd, value_x_pos, 60, font, "English", HSV_RED, HSV_BLACK);
        }
        last_lang_mode = is_french;
    }
    
    initialized = true;
    qp_flush(lcd);
}

void housekeeping_task_kb(void) {
    ui_task();
}

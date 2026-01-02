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

#pragma once

/* pin-out for PCB */

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* COL2ROW or ROW2COL */

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

/* SPI settings. */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
// We don't actually use MISO, so set it to a pin we don't use.
// Otherwise it likely get's tripped up as we use GP16 for D/C
#define SPI_MISO_PIN GP10 

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_LOAD_FONTS_TO_RAM TRUE
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 128
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
// #define QUANTUM_PAINTER_DEBUG

#define LCD_RST_PIN GP14
#define LCD_CS_PIN GP17
#define LCD_DC_PIN GP16

// #define LCD_INVERT_COLOUR
#define LCD_WAIT_TIME 150
#define LCD_WIDTH 128
#define LCD_HEIGHT 160
#define LCD_ROTATION QP_ROTATION_180
#define LCD_SPI_DIVISOR 1
#define LCD_SPI_MODE 3

#define UNICODE_TYPE_DELAY 10
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_WINDOWS
#define UNICODE_CYCLE_PERSIST false
#define TAPPING_TERM 200
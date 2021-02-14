/* Copyright 2017 Wunder
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
//make xd75:jdufrene_1

#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "sendstring_french.h"

bool is_linux = false; // default to windows

// Layer shorthand
#define _AZ 0
#define _SFT 1
#define _NUM 2
#define _PROG 3
#define _FNTN 4
#define _LANG 5
#define _RAND 6


// Key Combo
#define KC_CAD   LALT(LCTL(KC_DEL)) // ctrl + atl + del
#define ALTTAB   LALT(KC_TAB)       // alt + tab
#define CTLTAB   LCTL(KC_TAB)       // ctrl + tab
#define CTL_PGDN LCTL(KC_PGDN)      // back one tab
#define CTL_PGUP LCTL(KC_PGUP)      // forward one tab
#define SAVE     LCTL(KC_S)         // ctrl + S = save
#define CUT      LCTL(KC_X)         // ctrl + X = cut
#define COPY     LCTL(KC_C)         // ctrl + C = copy
#define PASTE    LCTL(KC_V)         // ctrl + V = paste
#define UNDO     LCTL(FR_Z)         // ctrl + Z = undo
#define REDO     LCTL(KC_Y)         // ctrl + Y = redo
#define CTLD     LCTL(KC_D)         // ctrl + D
#define NEWTAB   LCTL(KC_T)         // ctrl + T = new tab
#define CLSTAB   LCTL(FR_W)         // ctrl + W = close tab
#define FIND     LCTL(KC_F)         // ctrl + F = find
#define REPLACE  LCTL(KC_H)         // ctrl + H = replace
#define SELECTA  LCTL(FR_A)         // ctrl + A = select all
#define COMMENT  LCTL(FR_SLSH)      // ctrl + / = comment
#define CLSWIN   LALT(KC_F4)        // close window
#define CTL_F4   LCTL(KC_F4)        // close tab
#define HREFRSH  LCTL(KC_F5)        // hard refresh
#define CODEPT   LCTL(S(KC_U))      // linux code point
#define PALETTE  LCTL(S(KC_P))      // vs code palette
#define COMP     KC_RWIN            // linux compose
#define MMDLBTN  KC_BTN3            // mouse middle button
#define SELECTW  S(LALT(KC_RIGHT))  // select word
#define CTL_F2   LCTL(KC_F2)        // vs code : replace all word
#define CTLK     LCTL(S(KC_K))      // ctrl + K = delete line
#define EXPAND   LCTL(LALT(FR_A))   // vs code custom: Expand Braket Seletion
#define COMPOSE  X_RGUI             // linux compose
// nano shortcut
#define NCUT     LCTL(KC_K)         // nano cut
#define NCOPY    LALT(FR_6)         // nano copy
#define NPASTE   LCTL(KC_U)         // nano paste

// 
#define ________ KC_TRNS
#define ___XX___ KC_NO

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_RALT_MASK   (MOD_BIT(KC_RALT))

// Tap Dance Declarations
// https://jayliu50.github.io/qmk-cheatsheet/
enum {
    TD1 = 0,
    TD2,
    TD3,
    TD4,
    TD5,
    TD6,
    TD7,
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1] = ACTION_TAP_DANCE_DOUBLE(FR_EQL, KC_F12),
    [TD2] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTA),
    [TD3] = ACTION_TAP_DANCE_DOUBLE(UNDO, REDO),
    [TD4] = ACTION_TAP_DANCE_DOUBLE(KC_F5, HREFRSH),
    [TD5] = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTAB),
    [TD6] = ACTION_TAP_DANCE_DOUBLE(PASTE, MMDLBTN),
    [TD7] = ACTION_TAP_DANCE_DOUBLE(ALTTAB, CTLTAB),
};
#define EQF12  TD(TD1) // = -> F12
#define ALTALL TD(TD2) // alt -> select all
#define UNREDO TD(TD3) // undo -> redo
#define REFRSH TD(TD4) // refresh -> hard refresh
#define NCTAB  TD(TD5) // new tab -> close tab
#define PPASTE TD(TD6) // new tab -> close tab
#define ACTAB  TD(TD7) // alt tab -> ctrl tab

// TODO
// browser back <-> forward (mouse button)


// https://altcodeunicode.com/alt-codes-for-french-letters-with-accents-or-diacritics/
// https://en.wikipedia.org/wiki/List_of_Unicode_characters
// https://unicode-table.com/en/blocks/latin-extended-a/
// Lead Key Combo: Umlaut, Circumflex, Tilde (Linux + Windows)

// Linux AltGr + Compose + é + n
// https://math.dartmouth.edu/~sarunas/Linux_Compose_Key_Sequences.html
// Windows ALtGr + é + n


// Unicode definition: /!\ only works with US International layout
// https://www.fileformat.info/tip/microsoft/enter_unicode.htm
// https://jayliu50.github.io/qmk-cheatsheet/
// https://beta.docs.qmk.fm/using-qmk/software-features/feature_unicode#input-modes
enum unicode_names {
    U_AACUTE_LO,
    U_AACUTE_HI,
    U_CACUTE_LO,
    U_CACUTE_HI,
    U_CCARON_LO,
    U_CCARON_HI,
    U_DSTROK_LO,
    U_DSTROK_HI,
    U_ECARON_LO,
    U_ECARON_HI,
    U_IACUTE_LO,
    U_IACUTE_HI,
    U_LSTROK_LO,
    U_LSTROK_HI,
    U_NTILDE_LO,
    U_NTILDE_HI,
    U_NACUTE_LO,
    U_NACUTE_HI,
    U_NCARON_LO,
    U_NCARON_HI,
    U_OACUTE_LO,
    U_OACUTE_HI,
    U_RCARON_LO,
    U_RCARON_HI,
    U_SSHARP_LO,
    U_SCARON_LO,
    U_SCARON_HI,
    U_SACUTE_LO,
    U_SACUTE_HI,
    U_TCARON_LO,
    U_TCARON_HI,
    U_UACUTE_LO,
    U_UACUTE_HI,
    U_YACUTE_LO,
    U_YACUTE_HI,
    U_ZACUTE_LO,
    U_ZACUTE_HI,
    U_ZDOT_LO,
    U_ZDOT_HI,
    U_ZCARON_LO,
    U_ZCARON_HI,
};

const uint32_t PROGMEM unicode_map[] = {
    [U_AACUTE_LO]  = 0x00E1,  // á
    [U_AACUTE_HI]  = 0x00C1,  // Á
    [U_CACUTE_LO]  = 0x0107,  // ć
    [U_CACUTE_HI]  = 0x0106,  // Ć
    [U_CCARON_LO]  = 0x010D,  // č
    [U_CCARON_HI]  = 0x010C,  // Č
    [U_DSTROK_LO]  = 0x0111,  // đ
    [U_DSTROK_HI]  = 0x0110,  // Đ
    [U_ECARON_LO]  = 0x011B,  // ě
    [U_ECARON_HI]  = 0x011A,  // Ě
    [U_IACUTE_LO]  = 0x00ED,  // í
    [U_IACUTE_HI]  = 0x00CD,  // Í
    [U_LSTROK_LO]  = 0x0142,  // ł
    [U_LSTROK_HI]  = 0x0141,  // Ł
    [U_NTILDE_LO]  = 0x00F1,  // ñ
    [U_NTILDE_HI]  = 0x00D1,  // Ñ
    [U_NACUTE_LO]  = 0x0144,  // ń
    [U_NACUTE_HI]  = 0x0143,  // Ń
    [U_NCARON_LO]  = 0x0148,  // ň
    [U_NCARON_HI]  = 0x0147,  // Ň
    [U_OACUTE_LO]  = 0x00F3,  // ó
    [U_OACUTE_HI]  = 0x00D3,  // Ó
    [U_RCARON_LO]  = 0x0159,  // ř
    [U_RCARON_HI]  = 0x0158,  // Ř
    [U_SSHARP_LO]  = 0x00DF,  // ß
    [U_SCARON_LO]  = 0x0161,  // š
    [U_SCARON_HI]  = 0x0160,  // Š
    [U_SACUTE_LO]  = 0x015B,  // ś
    [U_SACUTE_HI]  = 0x015A,  // Ś
    [U_TCARON_LO]  = 0x0165,  // ť
    [U_TCARON_HI]  = 0x0164,  // Ť
    [U_UACUTE_LO]  = 0x00FA,  // ú
    [U_UACUTE_HI]  = 0x00DA,  // Ú
    [U_YACUTE_LO]  = 0x00FD,  // ý
    [U_YACUTE_HI]  = 0x00DD,  // Ý
    [U_ZACUTE_LO]  = 0x017A,  // ź
    [U_ZACUTE_HI]  = 0x0179,  // Ź
    [U_ZDOT_LO]    = 0x017C,  // ż
    [U_ZDOT_HI]    = 0x017B,  // Ż
    [U_ZCARON_LO]  = 0x017E,  // ž
    [U_ZCARON_HI]  = 0x017D,  // Ž
};

// overwrite hex_to_keycode from quantum/process_keycode/process_unicode_common.c to work with AZERTY french layout
// https://www.reddit.com/r/olkb/comments/ajvte7/unicode_and_azerty_converting_char_to_keycode/
uint16_t hex_to_keycode(uint8_t hex) {
  uint16_t keycode;
  if (hex == 0x0) {
    // keycode = KC_KP_0;
    keycode = FR_0;
  } else if (hex < 0xA) {
    // keycode = KC_KP_1 + (hex - 0x1);
    keycode = FR_1 + (hex - 0x1);
  } else {
    keycode = KC_A + (hex - 0xA);
  }
  if (keycode == KC_A) {
    keycode = FR_A;
  }
  return keycode;
}

#define K_AACUTE XP(X(U_AACUTE_LO),X(U_AACUTE_HI))
#define K_CACUTE XP(X(U_CACUTE_LO),X(U_CACUTE_HI))
#define K_CCARON XP(X(U_CCARON_LO),X(U_CCARON_HI))
#define K_DSTROK XP(X(U_DSTROK_LO),X(U_DSTROK_HI))
#define K_ECARON XP(X(U_ECARON_LO),X(U_ECARON_HI))
#define K_IACUTE XP(X(U_IACUTE_LO),X(U_IACUTE_HI))
#define K_LSTROK XP(X(U_LSTROK_LO),X(U_LSTROK_HI))
#define K_NTILDE XP(X(U_NTILDE_LO),X(U_NTILDE_HI))
#define K_NACUTE XP(X(U_NACUTE_LO),X(U_NACUTE_HI))
#define K_NCARON XP(X(U_NCARON_LO),X(U_NCARON_HI))
#define K_OACUTE XP(X(U_OACUTE_LO),X(U_OACUTE_HI))
#define K_RCARON XP(X(U_RCARON_LO),X(U_RCARON_HI))
#define K_SSHARP X(U_SSHARP_LO)
#define K_SCARON XP(X(U_SCARON_LO),X(U_SCARON_HI))
#define K_SACUTE XP(X(U_SACUTE_LO),X(U_SACUTE_HI))
#define K_TCARON XP(X(U_TCARON_LO),X(U_TCARON_HI))
#define K_UACUTE XP(X(U_UACUTE_LO),X(U_UACUTE_HI))
#define K_YACUTE XP(X(U_YACUTE_LO),X(U_YACUTE_HI))
#define K_ZACUTE XP(X(U_ZACUTE_LO),X(U_ZACUTE_HI))
#define K_ZDOT   XP(X(U_ZDOT_LO),X(U_ZDOT_HI))
#define K_ZCARON XP(X(U_ZCARON_LO),X(U_ZCARON_HI))

// Defines the keycodes used by your macros in process_record_user
enum custom_keycodes {
  TOG_OS = SAFE_RANGE,
  DCLICK,
  DBLCUT,
  DBLCOPY,
  DBLPAST,
  PROXY1,
  PROXY2,
  USER,
  PASWD,
  SPACE4
};

#define SFT      MO(_SFT)
#define NUM      LT(_NUM, KC_SPC)
#define PROG     MO(_PROG)
#define PROGSPC  LT(_PROG, KC_SPC)
#define FNTN     LT(_FNTN, KC_SPC)
#define FNTNB    LT(_FNTN, KC_BSPC)
#define LANG     MO(_LANG)
#define RAND     MO(_RAND)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* CUSTOM AZERTY
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC     | &       | é       | "       | '       |         | DEL     | -       | è       | _       | ç       | à       |         |         | TOG OS  |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | TAB     | a       | z       | e       | r       | t       | BSPC    | y       | u       | i       | o       | p       | ^       | $       | CPGUP   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | (SFT)   | q       | s       | d       | f       | g       | ENT     | h       | j       | k       | l       | m       | ù       | *       | CPGDN   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | LSHIFT  | w       | x       | c       | v       | b       | ENT     | n       | ,       | ;       | :       | !       | HOME    | UP      | END     |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | LCTRL   | LGUI    | LALT    | (NUM)   | (FNTN)  | SPACE   | SPACE   | SPACE   | SPACE   | (PROG)  | (LANG)  | (RAND)  | LEFT    | DOWN    | RIGHT   |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */ 
/*  ,____1___, ____2___, ____3___, ____4___, ____5___, ____6___, ____7___, ____8___, ____9___, ___10___, ___11___, ___12___, ___13___, ___14___, ___15___,*/

  [_AZ] = LAYOUT_ortho_5x15( /* CUSTOM AZERTY */
    KC_ESC  , FR_AMP  , FR_EACU , FR_QUOT , FR_APOS , FR_LPRN , KC_DEL  , FR_MINS , FR_EGRV , FR_UNDS , FR_CCED , FR_AGRV , FR_RPRN , EQF12   , TOG_OS  ,
    KC_TAB  , FR_A    , FR_Z    , KC_E    , KC_R    , KC_T    , KC_BSPC , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , FR_CIRC , FR_DLR  , KC_PGUP ,
    SFT     , FR_Q    , KC_S    , KC_D    , KC_F    , KC_G    , KC_ENT  , KC_H    , KC_J    , KC_K    , KC_L    , FR_M    , FR_UGRV , FR_ASTR , KC_PGDN ,
    KC_LSFT , FR_W    , KC_X    , KC_C    , KC_V    , KC_B    , KC_ENT  , KC_N    , FR_COMM , FR_SCLN , FR_COLN , FR_EXLM , KC_HOME , KC_UP   , KC_END  ,
    KC_LCTL , KC_LGUI , KC_LALT , NUM     , FNTNB   , FNTN    , KC_SPC  , KC_LSFT , PROGSPC , PROGSPC , LANG    , RAND    , KC_LEFT , KC_DOWN , KC_RIGHT
  ),

/* SHIFT LAYER
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |    ¤    | 1       | 2       | 3       | 4       | 5       |    ¤    | 6       | 7       | 8       | 9       | 0       |         | +       | F12     |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    | A       | Z       | E       | R       | T       |    ¤    | Y       | U       | I       | O       | P       | ¨       |         | CPGUP   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * | (SFT)   | Q       | S       | D       | F       | G       |         | H       | J       | K       | L       | M       | %       |         | CPGDN   |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    | W       | X       | C       | V       | B       |    ¤    | N       | ?       | .       | /       |         | HOME    | UP      | END     |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |    ¤    |    ¤    |         | BSPC    | BSPC    |    ¤    | ENT     | ENT     |         |         |         | LEFT    | DOWN    | RIGHT   |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */ 

// Shift Layer
  [_SFT] = LAYOUT_ortho_5x15( /* CUSTOM AZERTY */
    ________, FR_1    , FR_2    , FR_3    , FR_4    , FR_5    , ________, FR_6    , FR_7    , FR_8    , FR_9    , FR_0    , ___XX___, FR_PLUS , ________,
    ________, S(FR_A) , S(FR_Z) , S(KC_E) , S(KC_R) , S(KC_T) , KC_WBAK , S(KC_Y) , S(KC_U) , S(KC_I) , S(KC_O) , S(KC_P) , FR_UMLT , ___XX___, CTL_PGUP,
    ________, S(FR_Q) , S(KC_S) , S(KC_D) , S(KC_F) , S(KC_G) , KC_WFWD , S(KC_H) , S(KC_J) , S(KC_K) , S(KC_L) , S(FR_M) , FR_PERC , ___XX___, CTL_PGDN,
    ___XX___, S(FR_W) , S(KC_X) , S(KC_C) , S(KC_V) , S(KC_B) , KC_WREF , S(KC_N) , FR_QUES , FR_DOT  , FR_SLSH , ___XX___, ________, ________, ________,
    KC_RCTL , ________, ________, ________, KC_BSPC , KC_BSPC , KC_WSTP , KC_ENT  , KC_ENT  , ________, ________, ________, ________, ________, ________
  ),

/* NUMPAD
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |    ¤    |         |         |         |         |         |    ¤    |         |         | /       | *       |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |         |         |         |         |         |    ¤    |         | 7       | 8       | 9       | +       |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |         | 2CUT    | 2COPY   | 2PASTE  | SPACE4  |    ¤    | ENT     | 4       | 5       | 6       | -       |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |         |         |         | .       | ,       |    ¤    |         | 1       | 2       | 3       | =       |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |    ¤    |    ¤    |    ¤    |         |   ¤     |    ¤    |    ¤    | 0       |         |         | ENTER   |         |         |         |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NUM] = LAYOUT_ortho_5x15( /* NUMPAD */
    ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ________, ___XX___, ___XX___, FR_SLSH , FR_ASTR , ___XX___, KC_PSLS , KC_PAST , KC_PMNS ,
    ________, EXPAND  , PROXY1  , PROXY2  , USER    , PASWD   , ________, ___XX___, FR_7    , FR_8    , FR_9    , FR_PLUS , KC_P7   , KC_P8   , KC_P9   ,
    ________, CTLK    , NCUT    , NCOPY   , NPASTE  , SPACE4  , ________, KC_ENT  , FR_4    , FR_5    , FR_6    , FR_MINS , KC_P4   , KC_P5   , KC_P6   ,
    ________, ___XX___, ___XX___, ___XX___, FR_DOT  , FR_COMM , ________, ___XX___, FR_1    , FR_2    , FR_3    , FR_EQL  , KC_P1   , KC_P2   , KC_P3   ,
    ________, ________, ________, ________, ___XX___, ________, ________, ________, FR_0    , ________, ________, KC_ENT  , KC_P0   , KC_PPLS , KC_PENT
  ),

/* ,____1___, ____2___, ____3___, ____4___, ____5___, ____6___, ____7___, ____8___, ____9___, ___10___, ___11___, ___12___, ___13___, ___14___, ___15___ */

/* PROG LAYER
 * .------------------------------------------------------------------------------------------------------------------------------------------------------.
 * |    ¤    | €       | ~       | #       | {       | [       |    ¤    | |       | `       | \       | ^       | @       | ]       | }       | °        |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |    ¤    | A = &   | ~       | "       | '       | `       |    ¤    | -       | U = _   | I = |   | $       | P = %   |         |    ¤    |          |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |    ¤    | <       | [       | {       | (       | =       |    ¤    | +       | )       | }       | ]       | >       |  -      |    ¤    |          |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |    ¤    |         | X = *   | C = ^   | #       | /       |    ¤    | \       |    ¤    |    ¤    |    ¤    |    ¤    |         |         |          |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |    ¤    |    ¤    |    ¤    |         |         |   ¤     |    ¤    |    ¤    |    ¤    |    ¤    |         |         |         |         |          |
 * '------------------------------------------------------------------------------------------------------------------------------------------------------'
 */ 
  [_PROG] = LAYOUT_ortho_5x15( /* PROG */
    ________, FR_EURO , FR_TILD , FR_HASH , FR_LCBR , FR_LBRC , ________, FR_PIPE , FR_GRV  , FR_BSLS , FR_CCIRC, FR_AT   , FR_RBRC , FR_RCBR , FR_OVRR ,
    ________, FR_AMP  , FR_TILD , FR_QUOT , FR_APOS , FR_GRV  , ________, FR_MINS , FR_UNDS , FR_PIPE , FR_DLR  , FR_PERC , FR_HASH , ________, ___XX___,
    ________, FR_LESS , FR_LBRC , FR_LCBR , FR_LPRN , FR_EQL  , ________, FR_PLUS , FR_RPRN , FR_RCBR , FR_RBRC , FR_GRTR , FR_MINS , ________, ___XX___,
    ________, ___XX___, FR_ASTR , FR_CCIRC, FR_HASH , FR_SLSH , ________, FR_BSLS , ________, ________, ________, ________, ___XX___, ___XX___, ___XX___,
    ________, ________, ________, ___XX___, ___XX___, ________, ________, ________, ________, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___
  ),

/* ,____1___, ____2___, ____3___, ____4___, ____5___, ____6___, ____7___, ____8___, ____9___, ___10___, ___11___, ___12___, ___13___, ___14___, ___15___ */

/* FUNCTION LAYER
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |   ¤    |         | REDO    |         | CLSWIN  | REFRSH  |    ¤    | F6      |         |         |         |         | F11     | F12     | PRINT SCR|
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    | ALT     | UNDO    | DEL     | ENT     | NEWTAB  |    ¤    |         | HOME    | UP      | END     | MENU    |         |         | BRIGHT UP|
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * | SHIFT  | CTRL    | CUT     | COPY    | PASTE   | TAB     |    ¤    | ENT     | LEFT    | DOWN    | RIGHT   | BSPC    | DEL     |         | BRIGHT DW|
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    | COMMENT | SAVE    | CTLD    | FIND    | REPLACE |    ¤    | DBL CLK |    ¤    |    ¤    |    ¤    | DEL     | PLAY    | VOL UP  | MUTE     |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |    ¤    |    ¤    | PALETTE | ¤       | CTL_F2  |    ¤    |    ¤    | SHIFT   | SPACE   |         |         | PREV TRA| VOL DOWN| NEXT TRA |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FNTN] = LAYOUT_ortho_5x15( /* FUNCTION */
    ________, ACTAB   , REDO    , ___XX___, CLSWIN  , REFRSH  , KC_CAD  , KC_F6   , ___XX___, ___XX___, ___XX___, ___XX___, KC_F11  , KC_F12  , KC_PSCR ,
    ________, ALTALL  , UNDO    , KC_DEL  , KC_ENT  , NCTAB   , ________, ___XX___, KC_HOME , KC_UP   , KC_END  , KC_APP  , KC_PGUP , ___XX___, KC_BRIU ,
    KC_LSFT , KC_LCTL , CUT     , COPY    , PPASTE  , KC_TAB  , ________, KC_ENT  , KC_LEFT , KC_DOWN , KC_RIGHT, KC_BSPC , KC_PGDN , ___XX___, KC_BRID ,
    ________, COMMENT , SAVE    , CTLD    , FIND    , REPLACE , ________, DCLICK  , FR_QUES , FR_DOT  , FR_SLSH , KC_DEL  , KC_MPLY , KC_VOLU , KC_MUTE ,
    ________, ________, ________, PALETTE , ________, CTL_F2  , ________, KC_LSFT , KC_LSFT , KC_SPC  , KC_RWIN , ___XX___, KC_MPRV , KC_VOLD , KC_MNXT
  ),

/* LANGUAGE LAYER
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |   ¤    | å       |         |         |         |         |    ¤    |         |         |         | ø       |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    | á       | ž       | ě       | ř       | ť       |    ¤    | ý       | ú       | í       | ó       |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * | SHIFT  | ß       | š       | đ       |         |         |    ¤    |         |         |         | ł       |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |         | ś       | ć       | č       |         |    ¤    | ñ       | ň       | ń       |         |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |    ¤    |    ¤    |         |         |   ¤     |    ¤    |    ¤    |         |         |         |         |         |         |          |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */ 

  [_LANG] = LAYOUT_ortho_5x15( /* LANGUAGE */
    ________, ___XX___, K_ZACUTE, K_ZDOT  , ___XX___, ___XX___, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ________, K_AACUTE, K_ZCARON, K_ECARON, K_RCARON, K_TCARON, ________, K_YACUTE, K_UACUTE, K_IACUTE, K_OACUTE, ___XX___, ___XX___, ___XX___, COMP    ,
    KC_LSFT , K_SSHARP, K_SCARON, K_DSTROK, ___XX___, ___XX___, ________, ___XX___, ___XX___, ___XX___, K_LSTROK, ___XX___, ___XX___, ___XX___, CODEPT  ,
    ________, ___XX___, K_SACUTE, K_CACUTE, K_CCARON, ___XX___, ________, K_NTILDE, K_NCARON, K_NACUTE, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ________, ________, ________, ___XX___, KC_LSFT , ___XX___, ________, ________, ___XX___, ___XX___, LANG    , ___XX___, ___XX___, ___XX___, ___XX___
  ),

  /* RANDOM LAYER
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |    ¤    |         |         |         |         |         |    ¤    |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    | RGB TOG | NEXT MOD| HUE UP  | SATUR UP| BRIGHTUP|    ¤    |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    | STATIC  | BREATH  | RAINBOW | SWIRLI  |         |    ¤    |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    | SNAKE   | KNIGTHR | XMAS    | GRADIANT| RGB TEST|    ¤    |         |         |         |         |         |         |         |         |
 * |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
 * |    ¤    |    ¤    |    ¤    |    ¤    |         |   ¤     |    ¤    |    ¤    |         |         |         |         |         |         |         |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_RAND] = LAYOUT_ortho_5x15( /* RANDOM */
    ________, KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , ________, KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , ___XX___,
    ________, RGB_TOG , RGB_MOD , RGB_HUI , RGB_SAI , RGB_VAI , ________, KC_F13  , KC_F14  , KC_F15  , KC_F16  , KC_F17  , KC_F18  , KC_F19  , ___XX___,
    ________, RGB_M_P , RGB_M_B , RGB_M_R , RGB_M_SW, ___XX___, RESET   , KC_F20  , KC_F21  , KC_F22  , KC_F23  , KC_F24  , ___XX___, ___XX___, ___XX___,
    ________, RGB_M_SN, RGB_M_K , RGB_M_X , RGB_M_G , RGB_M_T , ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ________, ________, ________, ________, ___XX___, ________, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___
  ),
};
/* ,____1___, ____2___, ____3___, ____4___, ____5___, ____6___, ____7___, ____8___, ____9___, ___10___, ___11___, ___12___, ___13___, ___14___, ___15___ */


void shift_key_function(uint16_t KC1, uint16_t KC2, keyrecord_t *record) {
  static bool mods = false;
  static uint8_t shift_mask;
  if (record->event.pressed) {
    // on keydown
    shift_mask = get_mods()&MODS_SHIFT_MASK;
    if (shift_mask) {
      // if Shift is pressed down, clear shift and register KC2
      unregister_code(KC_LSFT);
      register_code(KC2);
      mods = true;
    } else {
      // else register KC1
      register_code(KC1);
    }
  } else {
    // on keyup
    if (mods) {
      unregister_code(KC2);
      register_code(KC_LSFT);
      mods = false;
    } else {
      unregister_code(KC1);
    }
  }
}

// void send_unicode_function(bool is_linux, char *str) { 
//   if (is_linux) {
//     tap_code16(LCTL(LSFT(KC_U)));
//     SEND_STRING(str);
//     tap_code(KC_SPC);
//   } else {
//     register_code(KC_LALT);
//     tap_code(KC_PPLS);
//     SEND_STRING(str);
//     unregister_code(KC_LALT);
//   }
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  //static bool bspcdel_mods = false;
  //static bool spcent_mods = false;

  switch (keycode) {
    case TOG_OS:
      if (record->event.pressed) {
        // on keydown
        if (is_linux) {
          rgblight_sethsv_yellow();
          // switch to Linux input
          set_unicode_input_mode(UC_LNX);
        } else {
          rgblight_sethsv_blue();
          // switch to Windows input using WinCompose
          set_unicode_input_mode(UC_WIN);
        }
        is_linux = ! is_linux;
      } else {
        // on key up
        // if (is_linux) {
        //   rgblight_sethsv_yellow();
        // } else {
        //   rgblight_sethsv_blue();
        // }
      }
      break;
    case DCLICK:
      // double click
      if (record->event.pressed) {
        // on keydown
        tap_code16(SELECTW);
      } else {
        // on key up
      }
      break;
    case DBLCUT:
      // double click + cut
      if (record->event.pressed) {
        // on keydown
        tap_code16(SELECTW);
        tap_code16(CUT);
      } else {
        // on key up
      }
      break;
    case DBLCOPY:
      // double click + copy
      if (record->event.pressed) {
        // on keydown
        tap_code16(SELECTW);
        tap_code16(COPY);
      } else {
        // on key up
      }
      break;
    case DBLPAST:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        tap_code16(SELECTW);
        tap_code16(PASTE);
      } else {
        // on key up
      }
      break;
    case PROXY1:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("http://10.249.10.183:8080");
      } else {
        // on key up
      }
      break;
    case PROXY2:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("http://152.110.212.8:8080");
      } else {
        // on key up
      }
      break;
    case USER:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("janosch.dufrene");
      } else {
        // on key up
      }
      break;
    case PASWD:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("");
      } else {
        // on key up
      }
      break;
    case SPACE4:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("    ");
      } else {
        // on key up
      }
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case _AZ:
        if(is_linux) {
          rgblight_sethsv_yellow();
        } else {
          rgblight_sethsv_blue();
        }
        break;
      case _NUM:
          rgblight_sethsv_orange();
          break;
      case _PROG:
          rgblight_sethsv_purple();   
          break;
    }
  return state;
}

void matrix_init_user(void) {
  // default to win compose
  set_unicode_input_mode(UC_WIN);
}

void keyboard_post_init_user(void) {
  // default to win compose
  set_unicode_input_mode(UC_WIN);
  is_linux = false;
  rgblight_sethsv_blue();
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

/* TEMPLATE LAYER
 * .-----------------------------------------------------------------------------------------------------------------------------------------------------.
 * |   ¤    |         |         |         |         |         |    ¤    |         |         |         |         |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |         |         |         |         |         |    ¤    |         |         |         |         |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |        |         |         |         |         |         |    ¤    |         |         |         |         |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |         |         |         |         |         |    ¤    |         |         |         |         |         |         |         |          |
 * |--------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----------|
 * |   ¤    |    ¤    |    ¤    |         |         |   ¤     |    ¤    |    ¤    |         |         |         |         |         |         |          |
 * '-----------------------------------------------------------------------------------------------------------------------------------------------------'
*
*
* [_XXX] = LAYOUT_ortho_5x15(
*   ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ________, ________, ________, ___XX___, ___XX___, ___XX___, ________, ________, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___, ___XX___
* ) 
*/ 
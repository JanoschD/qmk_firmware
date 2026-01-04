// qmk compile -kb=sporewoh/keezyboost40 -km=jan
// qmk flash -kb=sporewoh/keezyboost40 -km=jan

#include "print.h"
#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "layer_names.h"
#include "sendstring_french.h"

bool is_linux = false; // default to windows
bool is_french = true; // default to french

// Key Combo
#define KC_CAD   LALT(LCTL(KC_DEL))   // ctrl + atl + del
#define CTLPGDN  LCTL(KC_PGDN)        // back one tab
#define CTLPGUP  LCTL(KC_PGUP)        // forward one tab
#define SAVE     LCTL(KC_S)           // ctrl + S = save
#define CUT      LCTL(KC_X)           // ctrl + X = cut
#define COPY     LCTL(KC_C)           // ctrl + C = copy
#define PASTE    LCTL(KC_V)           // ctrl + V = paste
#define UNDO     LCTL(FR_Z)           // ctrl + Z = undo
#define UNDOE    LCTL(KC_Z)           // ctrl + Z = undo (for english)
#define REDO     LCTL(KC_Y)           // ctrl + Y = redo
#define NEWTAB   LCTL(KC_T)           // ctrl + T = new tab
#define CLSTAB   LCTL(FR_W)           // ctrl + W = close tab
#define CLSTABE  LCTL(KC_W)           // ctrl + W = close tab (for english)
#define FIND     LCTL(KC_F)           // ctrl + F = find
#define REPLACE  LCTL(KC_H)           // ctrl + H = replace
#define SELECTA  LCTL(FR_A)           // ctrl + A = select all
#define SELECTAE LCTL(KC_A)           // ctrl + A = select all (for english)
#define CLOSWIN  LALT(KC_F4)          // close window
#define CLOSTAB  LCTL(KC_F4)          // close tab
#define HREFRSH  LCTL(KC_F5)          // hard refresh
#define CODEPT   LCTL(S(KC_U))        // linux code point
#define PALETTE  LCTL(S(KC_P))        // vs code palette
#define COMP     KC_RWIN              // linux compose
#define MMDLBTN  MS_BTN3              // mouse middle button
#define SELECTW  S(LALT(KC_RIGHT))    // select word

// vs code shortcut
#define CTLD     LCTL(KC_D)           // ctrl + D
#define COMLIN   LCTL(FR_SLSH)        // ctrl + / = comment line (linux)
#define COMLINE  LCTL(KC_SLSH)        // ctrl + / = comment line (linux for english)
#define COMWIN   LCTL(FR_COLN)        // ctrl + : = comment line (windows)
#define COMWINE  LCTL(KC_COLN)        // ctrl + : = comment line (windows for english)
#define COMBLIN  LCTL(S(FR_A))        // ctrl + A = comment block (linux)
#define COMBLINE LCTL(S(KC_A))        // ctrl + A = comment block (linux for english)
#define COMBWIN  S(LALT(FR_A))        // shift + alt + a = comment block (windows)
#define COMBWINE S(LALT(KC_A))        // shift + alt + a = comment block (windows for english)
#define CTLK     LCTL(S(KC_K))        // ctrl + K = delete line
#define CTL_F2   LCTL(KC_F2)          // vs code : replace all word
#define EXPAND   S(LALT(KC_RIGHT))    // vs code custom: Expand Seletion
#define PRVMAT   LCTL(LALT(KC_D))     // vs code custom: Previous match
#define TERM     LCTL(S(LALT(KC_T)))  // vs code custom: Focus linux terminal
#define BKTOG    LCTL(LALT(KC_K))     // vs code: Bookmark toggle
#define BKNEXT   LCTL(LALT(KC_L))     // vs code: Bookmark next
#define BKPRV    LCTL(LALT(KC_J))     // vs code: Bookmark previous

#define TEAMUTE  LCTL(S(FR_M))        // ms team: mute
#define SFTENT   S(KC_ENT)            // shift enter
#define COMPOSE  X_RGUI               // linux compose

// nano shortcut
#define NCUT     LCTL(KC_K)         // nano cut
#define NCOPY    LALT(FR_6)         // nano copy
#define NCOPYE   LALT(KC_6)         // nano copy (for english)
#define NPASTE   LCTL(KC_U)         // nano paste

// ^
#define FR_CCIRC ALGR(FR_CCED)

// 
#define ________ KC_TRNS
#define ___XX___ KC_NO



// Tap Dance Declarations
void comment_tap_dance(tap_dance_state_t *state, void *user_data) {
    uprintf("Comment tap dance, count: %d\n", state->count);
    uint16_t line_comment;
    uint16_t block_comment;

    if (is_linux) {
        uprintf("Comment tap dance, linux\n");
        line_comment = is_french ? COMLIN : COMLINE;
        block_comment = is_french ? COMBLIN : COMBLINE;
    } else {
        uprintf("Comment tap dance, windows\n");
        line_comment = is_french ? COMWIN : COMWINE;
        block_comment = is_french ? COMBWIN : COMBWINE;
    }

    if (state->count == 1) {
        uprintf("Comment tap dance, single tap\n");
        // On single tap, register the line comment shortcut
        register_code16(line_comment);
    } else if (state->count == 2) {
        uprintf("Comment tap dance, double tap\n");
        // On double tap, register the block comment shortcut
        // Unregister the line comment first to avoid conflicts
        unregister_code16(line_comment);
        register_code16(block_comment);
    }
}

void comment_tap_dance_reset(tap_dance_state_t *state, void *user_data) {
    uprint("Comment tap dance reset\n");
    // Unregister all possible comment shortcuts on reset (key up)
    unregister_code16(COMLIN);
    unregister_code16(COMLINE);
    unregister_code16(COMWIN);
    unregister_code16(COMWINE);
    unregister_code16(COMBLIN);
    unregister_code16(COMBLINE);
    unregister_code16(COMBWIN);
    unregister_code16(COMBWINE);
}

// https://jayliu50.github.io/qmk-cheatsheet/
enum {
    TD1 = 0,
    TD2,
    TD3,
    TD4,
    TD5,
    TD6,
    TD7,
    TD8,
    TD9,
    TD10,
    TD11,
    TD12,
    TD13,
    TD14
};

tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTA),
    [TD2]  = ACTION_TAP_DANCE_DOUBLE(KC_F5, HREFRSH),
    [TD3]  = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTAB),
    [TD4]  = ACTION_TAP_DANCE_DOUBLE(PASTE, MMDLBTN),
    [TD5]  = ACTION_TAP_DANCE_DOUBLE(CTLD, PRVMAT),
    [TD6]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD7]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAD),
    [TD8]  = ACTION_TAP_DANCE_DOUBLE(CLOSTAB, CLOSWIN),
    //[TD9]  = ACTION_TAP_DANCE_DOUBLE(COMLIN, COMBLIN),
    //[TD10] = ACTION_TAP_DANCE_DOUBLE(COMWIN, COMBWIN),
    // english tap dance
    [TD9]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTAE),
    [TD10]  = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTABE),
    //[TD13]  = ACTION_TAP_DANCE_DOUBLE(COMLINE, COMBLINE),
    //[TD14]  = ACTION_TAP_DANCE_DOUBLE(COMWINE, COMBWINE),
    [TD11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comment_tap_dance, comment_tap_dance_reset),
};

#define ALTALL   TD(TD1) // alt           -> select all
#define REFRSH   TD(TD2) // refresh       -> hard refresh
#define NCTAB    TD(TD3) // new tab       -> close tab
#define PPASTE   TD(TD4) // ctrl v        -> mouse scroll wheel button
#define TCTLD    TD(TD5) // ctrl d        -> ctrl alt d
#define SFTCAP   TD(TD6) // shift         -> all caps
#define ESCAD    TD(TD7) // esc           -> ctrl alt del
#define CLOSTW   TD(TD8) // close tab     -> close window
//#define COMML    TD(TD9) // comment line  -> comment block (linux)
//#define COMMW    TD(TD10) // comment line -> comment block (windows)
// english versions
#define ALTALLE  TD(TD9) // alt          -> select all
#define NCTABE   TD(TD10) // new tab      -> close tab
//#define COMMLE   TD(TD13) // comment line -> comment block (linux)
//#define COMMWE   TD(TD14) // comment line -> comment block (windows)
#define COMMENT  TD(TD11) // comment line/block

// Unicode characters
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


#define K_AACUTE UP(U_AACUTE_LO, U_AACUTE_HI)
#define K_CACUTE UP(U_CACUTE_LO, U_CACUTE_HI)
#define K_CCARON UP(U_CCARON_LO, U_CCARON_HI)
#define K_DSTROK UP(U_DSTROK_LO, U_DSTROK_HI)
#define K_ECARON UP(U_ECARON_LO, U_ECARON_HI)
#define K_IACUTE UP(U_IACUTE_LO, U_IACUTE_HI)
#define K_LSTROK UP(U_LSTROK_LO, U_LSTROK_HI)
#define K_NTILDE UP(U_NTILDE_LO, U_NTILDE_HI)
#define K_NACUTE UP(U_NACUTE_LO, U_NACUTE_HI)
#define K_NCARON UP(U_NCARON_LO, U_NCARON_HI)
#define K_OACUTE UP(U_OACUTE_LO, U_OACUTE_HI)
#define K_RCARON UP(U_RCARON_LO, U_RCARON_HI)
#define K_SSHARP UM(U_SSHARP_LO)
#define K_SCARON UP(U_SCARON_LO, U_SCARON_HI)
#define K_SACUTE UP(U_SACUTE_LO, U_SACUTE_HI)
#define K_TCARON UP(U_TCARON_LO, U_TCARON_HI)
#define K_UACUTE UP(U_UACUTE_LO, U_UACUTE_HI)
#define K_YACUTE UP(U_YACUTE_LO, U_YACUTE_HI)
#define K_ZACUTE UP(U_ZACUTE_LO, U_ZACUTE_HI)
#define K_ZDOT   UP(U_ZDOT_LO, U_ZDOT_HI)
#define K_ZCARON UP(U_ZCARON_LO, U_ZCARON_HI)

// Defines the keycodes used by your macros in process_record_user
enum custom_keycodes {
  TOG_OS = SAFE_RANGE,
  TOG_LANG,
  SPACE4,
  C_COMM ,
  C_SCLN ,
  C_COLN ,
  C_EXLM,
  //COMMENT
};

#define SFT      MO(_SFT)
#define NUM      LT(_NUM, KC_SPC)
// #define PROG     MO(_SYMB)
#define SYMSPC   LT(_SYMB, KC_SPC)
#define FNTN     LT(_FNTN, KC_SPC)
#define FNTNB    LT(_FNTN, KC_BSPC)
#define LANG     MO(_LANG)

/*
TODO:

  FUNC layer: Page Up/Down on arrow when locking bottom right corner
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* CUSTOM AZERTY
  *.-----------------------------------------------------------------------------------------------------.
  *| a       | z       | e       | r       | t       ||| y       | u       | i       | o       | p       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| q       | s       | d       | f       | g       ||| h       | j       | k       | l       | m       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| w       | x       | c       | v       | b       ||| n       | ,       | ;       | :       | !       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| LGUI    | LALT    | (NUM)   | (FNTNB) | (ENG)   ||| (SFTCAP)| (SYMSPC)| (LANG)  | TOG OS  | TOG_LANG|
  *'-----------------------------------------------------------------------------------------------------'
  */
  /*____1___, ____2___, ____3___, ____4___, ____5___,    ____6___, ____7___, ____8___, ____9___, ___10___, */

  [_AZ] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
    FR_A    , FR_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    FR_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , FR_M    ,
    FR_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , FR_COMM , FR_SCLN , FR_COLN , FR_EXLM ,
    KC_LGUI , KC_LALT , NUM     , FNTNB   , SFTCAP  ,    SFTCAP  , SYMSPC  , LANG    , TOG_OS  , TOG_LANG    
  ),

  [_AZ_EN] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
    KC_A    , KC_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    KC_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , KC_M    ,
    KC_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , C_COMM  , C_SCLN  , C_COLN  , KC_EXLM ,
    KC_LGUI , KC_LALT , NUM     , FNTNB   , SFTCAP  ,    SFTCAP  , SYMSPC  , LANG    , TOG_OS  , TOG_LANG
  ),

  /* NUMPAD
  * .-----------------------------------------------------------------------------------------------------.
  * | EXPAND  | REDO    |PRINT SCR| SFTENT  |         |||         | 7       | 8       | 9       | REBOOT  |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | COMMENT | NCUT    | NCOPY   | NPASTE  | SPACE4  |||         | 4       | 5       | 6       | .       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | CTLK    | TERM    | BKTOG   | BKPRV   | BKNEXT  |||         | 1       | 2       | 3       | ,       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |    ¤    |    ¤    | XXXXXXX |         |   ¤     |||    ¤    | 0       |         |         | FLASH   |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_NUM] = LAYOUT_ortho_4x10( /* NUMPAD */
    EXPAND  , REDO    , KC_PSCR , SFTENT  , ___XX___,    ___XX___, FR_7    , FR_8    , FR_9    , QK_RBT  ,
    COMMENT , NCUT    , NCOPY   , NPASTE  , SPACE4  ,    ___XX___, FR_4    , FR_5    , FR_6    , FR_DOT  ,
    CTLK    , TERM    , BKTOG   , BKPRV   , BKNEXT  ,    ___XX___, FR_1    , FR_2    , FR_3    , FR_COMM ,
    ___XX___, ___XX___, ________, ___XX___, ___XX___,    KC_LSFT , FR_0    , ___XX___, ___XX___, QK_BOOT
  ),

  [_NUM_EN] = LAYOUT_ortho_4x10( /* NUMPAD */
    EXPAND  , REDO    , KC_PSCR , SFTENT  , ___XX___,    ___XX___, KC_7    , KC_8    , KC_9    , QK_RBT  ,
    COMMENT , NCUT    , NCOPYE  , NPASTE  , SPACE4  ,    ___XX___, KC_4    , KC_5    , KC_6    , KC_DOT  ,
    CTLK    , TERM    , BKTOG   , BKPRV   , BKNEXT  ,    ___XX___, KC_1    , KC_2    , KC_3    , KC_COMM ,
    ___XX___, ___XX___, ________, ___XX___, ___XX___,    KC_LSFT , KC_0    , ___XX___, ___XX___, QK_BOOT
  ),

  /* SYMBOL LAYER
  *.-----------------------------------------------------------------------------------------------------.
  *| A = &   | ~       | "       | '       | `       ||| -       | U = _   | I = |   | O = °   | P = %   |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| <       | [       | {       | (       | =       ||| +       | )       | }       | ]       | >       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| €       | X = *   | C = ^   | #       | /       ||| \       | $       | ^ (dead)| ¨       | @       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|    ¤    |    ¤    |         |         |   ¤     |||    ¤    | XXXXXXX |    ¤    |         |         |
  *'-----------------------------------------------------------------------------------------------------'
  */ 
  [_SYMB] = LAYOUT_ortho_4x10( /* SYMBOL */
    FR_AMPR , FR_TILD , FR_DQUO , FR_QUOT , FR_GRV  ,    FR_MINS , FR_UNDS , FR_PIPE , FR_DEG  , FR_PERC ,
    FR_LABK , FR_LBRC , FR_LCBR , FR_LPRN , FR_EQL  ,    FR_PLUS , FR_RPRN , FR_RCBR , FR_RBRC , FR_RABK ,
    FR_EURO , FR_ASTR , FR_CCIRC, FR_HASH , FR_SLSH ,    FR_BSLS , FR_DLR  , FR_CIRC , FR_DIAE , FR_AT   ,
    ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,    ___XX___, ________, ___XX___, ___XX___, ___XX___
  ),

  /* SYMBOL ENGLISH LAYER
  *.-----------------------------------------------------------------------------------------------------.
  *| A = &   | ~       | "       | '       | `       ||| -       | U = _   | I = |   |         | P = %   |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| <       | [       | {       | (       | =       ||| +       | )       | }       | ]       | >       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|         | X = *   | C = ^   | #       | /       ||| \       | $       |    ¤    |         | @       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|    ¤    |    ¤    |         |         |   ¤     |||    ¤    | XXXXXXX |    ¤    |         |         |
  *'-----------------------------------------------------------------------------------------------------'
  */ 
  [_SYMB_EN] = LAYOUT_ortho_4x10( /* SYMBOL */
    KC_AMPR , KC_TILD , KC_DQUO , KC_QUOT , KC_GRV  ,    KC_MINS , KC_UNDS , KC_PIPE , ___XX___, KC_PERC ,
    KC_LABK , KC_LBRC , KC_LCBR , KC_LPRN , KC_EQL  ,    KC_PLUS , KC_RPRN , KC_RCBR , KC_RBRC , KC_RABK ,
    ___XX___, KC_ASTR , KC_CIRC , KC_HASH , KC_SLSH ,    KC_BSLS , KC_DLR  , ___XX___, ___XX___, KC_AT   ,
    ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,    ___XX___, ________, ___XX___, ___XX___, ___XX___
  ),

  /* FUNCTION LAYER
  * .-----------------------------------------------------------------------------------------------------.
  * | ALT     | UNDO    | DEL     | ENT     | NEWTAB  ||| F6      | HOME    | UP      | END     | MENU    |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | CTRL    | CUT     | COPY    | PASTE   | TAB     |||    ¤    | LEFT    | DOWN    | RIGHT   | BSPC    |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | SHIFT   | SAVE    | CTLD    | FIND    | REPLACE ||| DBL CLK |    ¤    | REFRSH  | F11     | F12     |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | ESCAD   | CLOSTW  | PALETTE | XXXXXXX | F2      |||         | SHIFT   | RGUI    |         | RCTL    |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_FNTN] = LAYOUT_ortho_4x10( /* FUNCTION */
    ALTALL  , UNDO    , KC_DEL  , KC_ENT  , NCTAB   ,    KC_F6   , KC_HOME , KC_UP   , KC_END  , KC_APP  ,
    KC_LCTL , CUT     , COPY    , PPASTE  , KC_TAB  ,    ___XX___, KC_LEFT , KC_DOWN , KC_RIGHT, KC_BSPC ,
    KC_LSFT , SAVE    , TCTLD   , FIND    , REPLACE ,    SELECTW , ___XX___, REFRSH  , KC_F11  , KC_F12  ,
    ESCAD   , CLOSTW  , PALETTE , ________, KC_F2   ,    ___XX___, KC_RSFT , KC_RGUI , ___XX___, KC_RCTL
  ),

  [_FNTN_EN] = LAYOUT_ortho_4x10( /* FUNCTION */
    ALTALLE , UNDOE   , KC_DEL  , KC_ENT  , NCTABE  ,    KC_F6   , KC_HOME , KC_UP   , KC_END  , KC_APP  ,
    KC_LCTL , CUT     , COPY    , PPASTE  , KC_TAB  ,    ___XX___, KC_LEFT , KC_DOWN , KC_RIGHT, KC_BSPC ,
    KC_LSFT , SAVE    , TCTLD   , FIND    , REPLACE ,    SELECTW , ___XX___, REFRSH  , KC_F11  , KC_F12  ,
    ESCAD   , CLOSTW  , PALETTE , ________, KC_F2   ,    ___XX___, KC_RSFT , KC_RGUI , ___XX___, KC_RCTL
  ),

  /* LANGUAGE LAYER
  * .-----------------------------------------------------------------------------------------------------.
  * | á       | ž       | ě       | ř       | ť       ||| ý       | ú       | í       | ó       |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | š       | ß       | đ       |         |         |||         |         |         | ł       |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | ś       | ź       | ć       | č       |         ||| ñ       | ň       | ń       |         |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | à       | é       | ç       | è       | (SFTCAP)|||    ¤    |         | XXXXXXX |         |         |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_LANG] = LAYOUT_ortho_4x10( /* LANGUAGE */
    K_AACUTE, K_ZCARON, K_ECARON, K_RCARON, K_TCARON,    K_YACUTE, K_UACUTE, K_IACUTE, K_OACUTE, ___XX___,
    K_SCARON, K_SSHARP, K_DSTROK, ___XX___, ___XX___,    ___XX___, ___XX___, ___XX___, K_LSTROK, ___XX___,
    K_SACUTE, K_ZACUTE, K_CACUTE, K_CCARON, ___XX___,    K_NTILDE, K_NCARON, K_NACUTE, ___XX___, ___XX___,
    FR_AGRV , FR_EACU , FR_CCED , FR_EGRV , SFTCAP  ,    ___XX___, ___XX___, ________, ___XX___, ___XX___
  ),
};

bool process_lang_key(keyrecord_t *record, uint16_t en_key, uint16_t fr_key) {
    uint16_t key_to_process = is_french ? fr_key : en_key;
    uprintf("Processing lang key: %s as %s\n", get_keycode_string(en_key), get_keycode_string(key_to_process));
    if (record->event.pressed) {
        register_code16(key_to_process);
    } else {
        unregister_code16(key_to_process);
    }
    return false;
}

bool scln_was_shifted = false;
bool cln_was_shifted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  uprintf("KL: kc: 0x%04X (%s), col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, get_keycode_string(keycode), record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

  const bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;

  uprintf("shifted: %u\n", shifted);

  switch (keycode) {
    case TOG_OS:
      if (record->event.pressed) {
        // Toggle the OS mode
        is_linux = !is_linux;
        // Update unicode input mode
        if (is_linux) {
          set_unicode_input_mode(UNICODE_MODE_LINUX);
        } else {
          set_unicode_input_mode(UNICODE_MODE_WINDOWS);
        }
      }
      break;
    case TOG_LANG:
      if (record->event.pressed) {
        is_french = !is_french;
        if (is_french) {
          uprintf("Switching to French layout\n");
          set_single_default_layer(_AZ);
        } else {
          uprintf("Switching to English layout\n");
          set_single_default_layer(_AZ_EN);
        }
      }
      break;
    case SPACE4:
      if (record->event.pressed) {
        SEND_STRING("    ");
      }
      break;

    // case COMMENT:
    //   uprint("COMMENT");
    //   if (is_linux) {
    //     uprintf("COMMENT LINUX");
    //     return process_lang_key(record, COMMLE, COMML);
    //   } else {
    //     uprintf("COMMENT WINDOW");
    //     return process_lang_key(record, COMMWE, COMMW);
    //   }
    //   break;
    
    case C_COMM:
      // custom comma for english keyboard (output , and ? if shifted)
      uprintf("C_COMM kc: %s\n", get_keycode_string(keycode));
      if (record->event.pressed) {
        // on keydown
        if (shifted) {
          uprintf("C_COMM shifted down sending /\n");
          register_code16(KC_SLSH); // S(/) = ?
        } else {
          uprintf("C_COMM unshifted down sending ,\n");
          register_code16(KC_COMM);
        }
      } else {
        // on keyup
        if (shifted) {
          uprintf("C_COMM shifted up unregistering /\n");
          unregister_code16(KC_SLSH);
        } else {
          uprintf("C_COMM unshifted up unregistering ,\n");
          unregister_code16(KC_COMM);
        }
      }
      return false;

    case C_SCLN:
      // custom semicolon for english keyboard (output ; and . if shifted)
      uprintf("C_SCLN kc: %s\n", get_keycode_string(keycode));
      if (record->event.pressed) {
        // on keydown - store the shift state
        scln_was_shifted = shifted;
        if (shifted) {
          uprintf("C_SCLN shifted down sending .\n");
          unregister_code(KC_LSFT);
          register_code16(KC_DOT);
        } else {
          uprintf("C_SCLN unshifted down sending ;\n");
          register_code16(KC_SCLN);
        } 
      } else {
        // on keyup - use the stored shift state
        if (scln_was_shifted) {
          uprintf("C_SCLN shifted up unregistering .\n");
          unregister_code16(KC_DOT);
          register_code16(KC_LSFT);
        } else {
          uprintf("C_SCLN unshifted up unregistering ;\n");
          unregister_code16(KC_SCLN);
        }
      }
      return false;
    
    case C_COLN:
      // custom colon for english keyboard (output : and / if shifted)
      uprintf("C_COLN kc: %s\n", get_keycode_string(keycode));
      if (record->event.pressed) {
        // on keydown
        cln_was_shifted = shifted;
        if (shifted) {
          uprintf("C_COLN shifted down sending /\n");
          unregister_code(KC_LSFT);
          register_code16(KC_SLSH);
        } else {
          uprintf("C_COLN unshifted down sending :\n");
          register_code16(KC_LSFT);
          register_code16(KC_SCLN); 
        }
      } else {
        // on keyup
        if (cln_was_shifted) {
          uprintf("C_COLN shifted up unregistering /\n");
          unregister_code16(KC_SLSH);
          register_code16(KC_LSFT);
        } else {
          uprintf("C_COLN unshifted up unregistering :\n");
          unregister_code16(KC_SCLN);
          unregister_code16(KC_LSFT);
        }
      }
      return false;

 
    
    /* 
    case KC_A:
      return process_lang_key(record, KC_A, FR_A);
    
    case KC_Z:
      uprintf("KC_Z kc: %s\n", get_keycode_string(keycode));
      return process_lang_key(record, KC_Z, FR_Z);

    case KC_Q:
      return process_lang_key(record, KC_Q, FR_Q);
    
    case KC_W:
      return process_lang_key(record, KC_W, FR_W);

    case KC_M:
      return process_lang_key(record, KC_M, FR_M);

    // case EXLM:
    //   return process_lang_key(record, KC_EXLM, FR_EXLM);

    case KC_EXLM:
      uprintf("KC_EXLM kc: %s\n", get_keycode_string(keycode));
      if (record->event.pressed) {
        // on keydown
        if (shifted) {
          uprintf("KC_EXLM shifted down\n");
          //register_code16(KC_NO);
        } else {
          uprintf("KC_EXLM unshifted down\n");
          if (is_french) {
            uprintf("KC_EXLM unshifted down - French\n");
            register_code16(FR_EXLM);
          } else {
            uprintf("KC_EXLM unshifted down - English\n");
            register_code16(KC_EXLM);
          }
        }
      } else {
        // on keyup
        if (shifted) {
          uprintf("KC_EXLM shifted up\n");
          //unregister_code16(KC_NO);
        } else {
          uprintf("KC_EXLM unshifted up\n");
          if (is_french) {
            uprintf("KC_EXLM unshifted up - French\n");
            unregister_code16(FR_EXLM);
          } else {
            uprintf("KC_EXLM unshifted up - English\n");
            unregister_code16(KC_EXLM);
          }
        }
      }
      return false;

    case KC_COLN:
      if (record->event.pressed) {
        // on keydown
        if (shifted) {
          register_code16(KC_NO);
        } else {
          if (is_french) {
            register_code16(FR_COLN);
          } else {
            register_code16(KC_COLN);
          }
        }
      } else {
        // on keyup
        if (shifted) {
          unregister_code16(KC_NO);
        } else {
          if (is_french) {
            unregister_code16(FR_COLN);
          } else {
            unregister_code16(KC_COLN);
          }
        }
      }
      return false;
    
    case KC_SCLN:
      if (record->event.pressed) {
        // on keydown - store the shift state
        scln_was_shifted = shifted;
        if (shifted) {
          if (is_french) {
            register_code16(FR_DOT);
          } else {
            unregister_code(KC_LSFT);
            register_code16(KC_DOT);
          }
        } else {
          if (is_french) {
            register_code16(FR_SCLN);
          } else {
            register_code16(KC_SCLN);
          }
        }
      } else {
        // on keyup - use the stored shift state
        if (scln_was_shifted) {
          if (is_french) {
            unregister_code16(FR_DOT);
          } else {
            unregister_code16(KC_DOT);
            register_code16(KC_LSFT);
          }
        } else {
          if (is_french) {
            unregister_code16(FR_SCLN);
          } else {
            unregister_code16(KC_SCLN);
          }
        }
      }
      return false;

    case KC_COMM:
      if (record->event.pressed) {
        // on keydown
        if (shifted) {
          if (is_french) {
            register_code16(FR_QUES);
          } else {
            register_code16(KC_SLSH); // S(/) = ?
          }
        } else {
          if (is_french) {
            register_code16(FR_COMM);
          } else {
            register_code16(KC_COMM);
          }
        }
      } else {
        // on keyup
        if (shifted) {
          if (is_french) {
            unregister_code16(FR_QUES);
          } else {
            unregister_code16(KC_SLSH);
          }
        } else {
          if (is_french) {
            unregister_code16(FR_COMM);
          } else {
            unregister_code16(KC_COMM);
          }
        }
      }
      return false; 
    */

    // case KC_DOT:
    //   return process_lang_key(record, KC_DOT, FR_DOT);


  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // AZERTY
    // if (layer_state_cmp(state, _AZ)) {
    //   if (!is_french) {
    //     state &= ~(1UL << _AZ);    // Turn OFF French AZERTY layer
    //     state |= (1UL << _AZ_EN);  // Turn ON English AZERTY layer
    //   }
    // } else {
    //   state &= ~(1UL << _AZ_EN);   // Turn OFF English AZERTY layer
    // }
    // SYMBOL
    if (layer_state_cmp(state, _SYMB)) {
      if (!is_french) {
        state &= ~(1UL << _SYMB);    // Turn OFF French Symbol layer
        state |= (1UL << _SYMB_EN);  // Turn ON English Symbol layer
      }
    } else {
      state &= ~(1UL << _SYMB_EN);   // Turn OFF English Symbol layer
    }
    // FUNCTION
    if (layer_state_cmp(state, _FNTN)) {
      if (!is_french) {
        state &= ~(1UL << _FNTN);    // Turn OFF French Function layer
        state |= (1UL << _FNTN_EN);  // Turn ON English Function layer
      }
    } else {
      state &= ~(1UL << _FNTN_EN);   // Turn OFF English Function layer
    }
    // NUMBER
    if (layer_state_cmp(state, _NUM)) {
      if (!is_french) {
        state &= ~(1UL << _NUM);    // Turn OFF French Numpad layer
        state |= (1UL << _NUM_EN);  // Turn ON English Numpad layer
      }
    } else {
      state &= ~(1UL << _NUM_EN);   // Turn OFF English Numpad layer
    }

    return state;
}

void matrix_init_user(void) {
  // default to win compose
  set_unicode_input_mode(UNICODE_MODE_WINDOWS);
}

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  set_unicode_input_mode(UNICODE_MODE_WINDOWS);
  is_linux = false;
  is_french = true;
}


/* TEMPLATE LAYER
 * .-----------------------------------------------------------------------------------------------------.
 * |         |         |         |         |         |||         |         |         |         |         |
 * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
 * |         |         |         |         |         |||         |         |         |         |         |
 * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
 * |         |         |         |         |         |||         |         |         |         |         |
 * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
 * |         |         |         |         |         |||         |         |         |         |         |
 * '-----------------------------------------------------------------------------------------------------'
*
*
* [_XXX] = LAYOUT_ortho_4x10(
*   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
*   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___
* ) 
*/ 
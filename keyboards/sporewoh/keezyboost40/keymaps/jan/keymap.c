// qmk compile -kb=sporewoh/keezyboost40 -km=jan

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
#define REDO     LCTL(KC_Y)           // ctrl + Y = redo
#define NEWTAB   LCTL(KC_T)           // ctrl + T = new tab
#define CLSTAB   LCTL(FR_W)           // ctrl + W = close tab
#define FIND     LCTL(KC_F)           // ctrl + F = find
#define REPLACE  LCTL(KC_H)           // ctrl + H = replace
#define SELECTA  LCTL(FR_A)           // ctrl + A = select all
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
#define COMWIN   LCTL(FR_COLN)        // ctrl + : = comment line (windows)
#define COMBLIN  LCTL(S(FR_A))        // ctrl + A = comment block (linux)
#define COMBWIN  S(LALT(FR_A))        // shift + alt + a = comment block (windows)
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
#define NPASTE   LCTL(KC_U)         // nano paste

// ^
#define FR_CCIRC ALGR(FR_CCED)

// 
#define ________ KC_TRNS
#define ___XX___ KC_NO



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
    TD8,
    TD9,
    TD10,
    TD11
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1]  = ACTION_TAP_DANCE_DOUBLE(FR_EQL, KC_F12),
    [TD2]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTA),
    [TD3]  = ACTION_TAP_DANCE_DOUBLE(KC_F5, HREFRSH),
    [TD4]  = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTAB),
    [TD5]  = ACTION_TAP_DANCE_DOUBLE(PASTE, MMDLBTN),
    [TD6]  = ACTION_TAP_DANCE_DOUBLE(CTLD, PRVMAT),
    [TD7]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD8]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAD),
    [TD9]  = ACTION_TAP_DANCE_DOUBLE(CLOSTAB, CLOSWIN),
    [TD10] = ACTION_TAP_DANCE_DOUBLE(COMLIN, COMBLIN),
    [TD11] = ACTION_TAP_DANCE_DOUBLE(COMWIN, COMBWIN),
};
#define EQF12  TD(TD1) // = -> F12
#define ALTALL TD(TD2) // alt     -> select all
#define REFRSH TD(TD3) // refresh -> hard refresh
#define NCTAB  TD(TD4) // new tab -> close tab
#define PPASTE TD(TD5) // ctrl v  -> mouse scroll wheel button
#define TCTLD  TD(TD6) // ctrl d  -> ctrl alt d
#define SFTCAP TD(TD7) // shift   -> all caps
#define ESCAD  TD(TD8) // esc     -> ctrl alt del
#define CLOSTW TD(TD9) // close tab -> close window
#define COMML  TD(TD10) // comment line -> comment block (linux)
#define COMMW  TD(TD11) // comment line -> comment block (windows)

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
  DYN_SYM
};

#define SFT      MO(_SFT)
#define NUM      LT(_NUM, KC_SPC)
// #define PROG     MO(_SYMB)
// #define SYMSPC   LT(_SYMB, KC_SPC)
#define FNTN     LT(_FNTN, KC_SPC)
#define FNTNB    LT(_FNTN, KC_BSPC)
#define LANG     MO(_LANG)

/*
TODO:
  
  EQF12
  KC_RCTL

  QWERTY / Language switcher
  LGUI + arrow for window management?
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

  // [_FR] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
  //   FR_A    , FR_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
  //   FR_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , FR_M    ,
  //   FR_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , FR_COMM , FR_SCLN , FR_COLN , FR_EXLM ,
  //   KC_LGUI , KC_LALT , NUM     , FNTNB   , SFTCAP  ,    SFTCAP  , SYMSPC  , LANG    , TOG_OS  , TOG_LANG    
  // ),

  /* CUSTOM AZERTY 
  *.-----------------------------------------------------------------------------------------------------.
  *| a       | z       | e       | r       | t       ||| y       | u       | i       | o       | p       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| q       | s       | d       | f       | g       ||| h       | j       | k       | l       | m       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| w       | x       | c       | v       | b       ||| n       | ,       | ;       | :       | !       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| LGUI    | LALT    | (NUM)   | (FNTNB) | (ENG)   ||| (SFTCAP)| (SYMBOL)| (LANG)  | TOG OS  | TOG_LANG|
  *'-----------------------------------------------------------------------------------------------------'
  */
  [_AZ] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
    KC_A    , KC_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    KC_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , KC_M    ,
    KC_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , KC_COMM , KC_SCLN , KC_COLN , KC_EXLM ,
    KC_LGUI , KC_LALT , NUM     , FNTNB   , SFTCAP  ,    SFTCAP  , DYN_SYM , LANG    , TOG_OS  , TOG_LANG
  ),

  /* SHIFT LAYER
  *.-----------------------------------------------------------------------------------------------------.
  *| A       | Z       | E       | R       | T       ||| Y       | U       | I       | O       | P       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| Q       | S       | D       | F       | G       ||| H       | J       | K       | L       | M       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| W       | X       | C       | V       | B       ||| N       | ?       | .       |         |         |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|    ¤    |    ¤    |         |         |         ||| XXXXXXX |         |         |         |         |
  *'-----------------------------------------------------------------------------------------------------'
  */
  /*____1___, ____2___, ____3___, ____4___, ____5___,    ____6___, ____7___, ____8___, ____9___, ___10___, */

  [_SFT] = LAYOUT_ortho_4x10( /* SHIFT */
    S(FR_A) , S(FR_Z) , S(KC_E) , S(KC_R) , S(KC_T) ,    S(KC_Y) , S(KC_U) , S(KC_I) , S(KC_O) , S(KC_P) ,
    S(FR_Q) , S(KC_S) , S(KC_D) , S(KC_F) , S(KC_G) ,    S(KC_H) , S(KC_J) , S(KC_K) , S(KC_L) , S(FR_M) ,
    S(FR_W) , S(KC_X) , S(KC_C) , S(KC_V) , S(KC_B) ,    S(KC_N) , FR_QUES , FR_DOT  , ___XX___, ___XX___,
    ________, ________, ________, ________, ________,    ________, ________, ________, ________, ________
  ),

  /* NUMPAD
  * .-----------------------------------------------------------------------------------------------------.
  * | EXPAND  | REDO    |PRINT SCR| SFTENT  |         |||         | 7       | 8       | 9       |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | CTLK    | NCUT    | NCOPY   | NPASTE  | SPACE4  |||         | 4       | 5       | 6       | .       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | COMMENT | TERM    | BKTOG   | BKPRV   | BKNEXT  |||         | 1       | 2       | 3       | ,       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |    ¤    |    ¤    | XXXXXXX |         |   ¤     |||    ¤    | 0       |         |         | FLASH   |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_NUM] = LAYOUT_ortho_4x10( /* NUMPAD */
    EXPAND  , REDO    , KC_PSCR , SFTENT  , ___XX___,    ___XX___, FR_7    , FR_8    , FR_9    , ___XX___,
    CTLK    , NCUT    , NCOPY   , NPASTE  , SPACE4  ,    ___XX___, FR_4    , FR_5    , FR_6    , FR_DOT  ,
    COMML   , TERM    , BKTOG   , BKPRV   , BKNEXT  ,    ___XX___, FR_1    , FR_2    , FR_3    , FR_COMM ,
    ___XX___, ___XX___, ________, ___XX___, ___XX___,    KC_LSFT , FR_0    , ___XX___, ___XX___, QK_BOOT
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
    if (record->event.pressed) {
        register_code(key_to_process);
    } else {
        unregister_code(key_to_process);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  //static bool bspcdel_mods = false;
  //static bool spcent_mods = false;

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
          // Toggle the language mode
          is_french = !is_french;
          // if (is_french) {
          //     set_single_default_layer(_EN);
          // } else {
          //     set_single_default_layer(_FR);
          // }
      }
      break;
    case SPACE4:
      // double click + paste
      if (record->event.pressed) {
        // on keydown
        SEND_STRING("    ");
      }
      break;
    
    case KC_A:
      return process_lang_key(record, KC_A, FR_A);
    
    case KC_Z:
      return process_lang_key(record, KC_Z, FR_Z);

    case KC_Q:
      return process_lang_key(record, KC_Q, FR_Q);  
    
    case KC_W:
      return process_lang_key(record, KC_W, FR_W);

    case KC_M:
      return process_lang_key(record, KC_M, FR_M);

    case KC_COMM:
      return process_lang_key(record, KC_COMM, FR_COMM);

    case KC_SCLN:
      return process_lang_key(record, KC_SCLN, FR_SCLN);

    case KC_COLN:
      return process_lang_key(record, KC_COLN, FR_COLN);

    case KC_EXLM:
      return process_lang_key(record, S(KC_1), FR_EXLM);

    case KC_DOT:
      return process_lang_key(record, KC_DOT, FR_DOT);

    case DYN_SYM:
      if (record->event.pressed) {
        // Activate layer on press
        if (is_french) {
            layer_on(_SYMB);
        } else {
            layer_on(_SYMB_EN);
        }
      } else { // On release
        // Deactivate layer
        if (is_french) {
            layer_off(_SYMB);
        } else {
            layer_off(_SYMB_EN);
        }
        // If it was a tap, send space
        if (record->tap.count > 0) {
          tap_code(KC_SPC);
        }
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
  // default to win compose
  set_unicode_input_mode(UNICODE_MODE_WINDOWS);
}

void keyboard_post_init_user(void) {
  // default to win compose
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
// qmk compile -kb=sporewoh/keezyboost40 -km=jan
// qmk flash -kb=sporewoh/keezyboost40 -km=jan

// #include "print.h"
#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "layer_names.h"
// #include "sendstring_french.h"

bool is_linux = true; // default to linux
bool is_french = true; // default to french

// Key Combo
#define KC_CAD   LALT(LCTL(KC_DEL))   // ctrl + atl + del
#define CTLPGDN  LCTL(KC_PGDN)        // back one tab
#define CTLPGUP  LCTL(KC_PGUP)        // forward one tab
#define SAVE     LCTL(KC_S)           // ctrl + S = save
#define CUT      LCTL(KC_X)           // ctrl + X = cut
#define COPY     LCTL(KC_C)           // ctrl + C = copy
#define PASTE    LCTL(KC_V)           // ctrl + V = paste
#define PASTEW   LGUI(KC_V)           // win  + V = paste with windows clipboard history
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
#define WINEMO   LGUI(FR_SCLN)        // windows emoji panel
#define WINEMOE  LGUI(KC_DOT)         // windows emoji panel (for english)

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
#define BKPRV    LCTL(LALT(S(KC_J)))  // vs code: Bookmark previous

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


// Tap Dance Declarations
void comment_tap_dance(tap_dance_state_t *state, void *user_data) {
    uint16_t line_comment;
    uint16_t block_comment;

    if (is_linux) {
        line_comment = is_french ? COMLIN : COMLINE;
        block_comment = is_french ? COMBLIN : COMBLINE;
    } else {
        line_comment = is_french ? COMWIN : COMWINE;
        block_comment = is_french ? COMBWIN : COMBWINE;
    }

    if (state->count == 1) {
        // On single tap, register the line comment shortcut
        tap_code16(line_comment);
    } else if (state->count == 2) {
        // On double tap, register the block comment shortcut
        tap_code16(block_comment);
    } else {
        reset_tap_dance(state);
    }
}

void bookmark_tap_dance(tap_dance_state_t *state, void *user_data) {
  
  const bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;

  if (state->count == 1) {
    if (shifted) {
      // If Shift is held, go to previous bookmark
      tap_code16(BKPRV);
    } else {
      // Otherwise, go to next bookmark
      tap_code16(BKNEXT);
    }
  } else if (state->count == 2) {
    // On double tap, toggle bookmark
    tap_code16(BKTOG);
  } else {
    reset_tap_dance(state);
  }

}

// triple tap: paste -> mouse middle button -> windows paste history
void paste_tap_dance(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      tap_code16(PASTE);
    } else if (state->count == 2) {
      tap_code16(MMDLBTN);
    } else if (state->count == 3) {
      tap_code16(PASTEW);
    } else {
      reset_tap_dance(state);
    }
}

// iter number key code
void iter_tap_dance(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(KC_1);
  } else if (state->count == 2) {
      tap_code16(KC_2);
    } else if (state->count == 3) {
      tap_code16(KC_3);
    } else {
      reset_tap_dance(state);
    }
}

void agrave_tap_dance(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(FR_AGRV);
  } else if (state->count == 2) {
    // À
    register_unicode(0x00C0);
  } else {
    reset_tap_dance(state);
  }
}

void cced_tap_dance(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code16(FR_CCED);
  } else if (state->count == 2) {
    // Ç
    register_unicode(0x00C7);
  } else {
    reset_tap_dance(state);
  }
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
    TD14,
    TD15,
    TD16
};

tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [TD1]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTA),
    [TD2]  = ACTION_TAP_DANCE_DOUBLE(KC_F5, HREFRSH),
    [TD3]  = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTAB),
    // [TD4]  = ACTION_TAP_DANCE_DOUBLE(PASTE, MMDLBTN),
    [TD4]  = ACTION_TAP_DANCE_FN(paste_tap_dance),
    [TD5]  = ACTION_TAP_DANCE_DOUBLE(CTLD, PRVMAT),
    [TD6]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD7]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAD),
    [TD8]  = ACTION_TAP_DANCE_DOUBLE(CLOSTAB, CLOSWIN),
    // english tap dance
    [TD9]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, SELECTAE),
    [TD10]  = ACTION_TAP_DANCE_DOUBLE(NEWTAB, CLSTABE),
    // comment tap dance
    // [TD11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comment_tap_dance, comment_tap_dance_reset),
    [TD11] = ACTION_TAP_DANCE_FN(comment_tap_dance),
    // bookmark tap dance
    // [TD12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bookmark_tap_dance, bookmark_tap_dance_reset),
    [TD12] = ACTION_TAP_DANCE_FN(bookmark_tap_dance),
    [TD13] = ACTION_TAP_DANCE_DOUBLE(KC_APP, WINEMO),
    // iter tap dance
    [TD14] = ACTION_TAP_DANCE_FN(iter_tap_dance),
    // french accented characters
    [TD15] = ACTION_TAP_DANCE_FN(agrave_tap_dance),
    [TD16] = ACTION_TAP_DANCE_FN(cced_tap_dance),
};

#define ALTALL   TD(TD1) // alt           -> select all
#define REFRSH   TD(TD2) // refresh       -> hard refresh
#define NCTAB    TD(TD3) // new tab       -> close tab
#define PPASTE   TD(TD4) // ctrl v        -> mouse scroll wheel button
#define TCTLD    TD(TD5) // ctrl d        -> ctrl alt d
#define SFTCAP   TD(TD6) // shift         -> all caps
#define ESCAD    TD(TD7) // esc           -> ctrl alt del
#define CLOSTW   TD(TD8) // close tab     -> close window
// english versions
#define ALTALLE  TD(TD9) // alt          -> select all
#define NCTABE   TD(TD10) // new tab      -> close tab
// comment
#define COMMENT  TD(TD11) // comment line/block
// bookmark
#define BOOKMARK TD(TD12) // bookmark next/previous/toggle
// windows emoji
#define APPWIN   TD(TD13) // apps -> windows emoji panel
// iter
#define ITER     TD(TD14) // increment number key code
// french accented characters
#define AGRAVE   TD(TD15) // à
#define CCED     TD(TD16) // ç


// Defines the keycodes used by your macros in process_record_user
enum custom_keycodes {
  TOG_OS = SAFE_RANGE,
  TOG_LANG,
  SPACE4,
  C_COMM ,
  C_SCLN ,
  C_COLN ,
  C_EXLM,
};

// Layer definitions
#define SFT      MO(_SFT)
#define NUM      LT(_NUM, KC_SPC)
#define SYMSPC   LT(_SYMB, KC_SPC)
#define FNTN     LT(_FNTN, KC_SPC)
#define FNTNB    LT(_FNTN, KC_BSPC)
#define LANG     MO(_LANG)
#define AZRT     MO(_AZ_RT)
#define BROWS    MO(_BROWS)

// Combo definitions
const uint16_t PROGMEM fn_sym_shift_combo[] = {FNTNB, SYMSPC, COMBO_END};

combo_t key_combos[] = {
  COMBO(fn_sym_shift_combo, KC_LSFT),
};

/*
TODO:

  - FUNC layer: Page Up/Down on arrow when locking bottom right corner

  - Ctrl + 1 ..9 to switch vs code split screens

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
  *| CTL     | LALT    | (NUM)   | (FNTNB) | (ENG)   ||| (SFTCAP)| (SYMSPC)| (LANG)  | TOG OS  | TOG_LANG|
  *'-----------------------------------------------------------------------------------------------------'
  */
  /*____1___, ____2___, ____3___, ____4___, ____5___,    ____6___, ____7___, ____8___, ____9___, ___10___, */

  [_AZ] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
    FR_A    , FR_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    FR_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , FR_M    ,
    FR_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , FR_COMM , FR_SCLN , FR_COLN , FR_EXLM ,
    KC_LCTL , KC_LALT , NUM     , FNTNB   , AZRT    ,    SFTCAP  , SYMSPC  , LANG    , TOG_OS  , TOG_LANG    
  ),

  [_AZ_EN] = LAYOUT_ortho_4x10( /* CUSTOM AZERTY */
    KC_A    , KC_Z    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    KC_Q    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , KC_M    ,
    KC_W    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , C_COMM  , C_SCLN  , C_COLN  , KC_EXLM ,
    KC_LCTL , KC_LALT , NUM     , FNTNB   , SFTCAP  ,    SFTCAP  , SYMSPC  , LANG    , TOG_OS  , TOG_LANG
  ),

  [_AZ_RT] = LAYOUT_ortho_4x10(  /* AZERTY RIGHT HAND */
    KC_P    , KC_O    , KC_I    , KC_U    , KC_Y    ,   ___XX___, MS_BTN1 , MS_UP   , MS_BTN2 , ___XX___,
    FR_M    , KC_L    , KC_K    , KC_J    , KC_H    ,   ___XX___, MS_LEFT , MS_DOWN , MS_RGHT , ___XX___,
    FR_MINS , FR_COLN , FR_DOT  , FR_COMM , KC_N    ,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ________, ________, ___XX___, ___XX___, ___XX___,   MS_ACL0 , MS_ACL1 , MS_ACL2 , ___XX___, ___XX___
  ),

  /* NUMPAD
  * .-----------------------------------------------------------------------------------------------------.
  * | ESCAPE  | REDO    |PRINT SCR| SFTENT  | UP      |||         | 7       | 8       | 9       | REBOOT  |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | COMMENT | NCUT    | NCOPY   | NPASTE  | SPACE4  |||         | 4       | 5       | 6       | .       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | CTLK    | TERM    |BOOKMARK | EXPAND  | DOWN    |||         | 1       | 2       | 3       | ,       |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |         |         | XXXXXXX |         |   ¤     |||    ¤    | 0       |         |         | FLASH   |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_NUM] = LAYOUT_ortho_4x10( /* NUMPAD */
    ESCAD   , REDO    , KC_PSCR , SFTENT  , KC_UP   ,    ___XX___, FR_7    , FR_8    , FR_9    , QK_RBT  ,
    COMMENT , NCUT    , NCOPY   , NPASTE  , SPACE4  ,    ITER    , FR_4    , FR_5    , FR_6    , FR_DOT  ,
    CTLK    , TERM    , BOOKMARK, EXPAND  , KC_DOWN ,    ___XX___, FR_1    , FR_2    , FR_3    , FR_COMM ,
    ________, ________, ___XX___, KC_BSPC , ___XX___,    KC_LSFT , FR_0    , ___XX___, ___XX___, QK_BOOT
  ),

  [_NUM_EN] = LAYOUT_ortho_4x10( /* NUMPAD */
    ESCAD   , REDO    , KC_PSCR , SFTENT  , KC_UP   ,    ___XX___, KC_7    , KC_8    , KC_9    , QK_RBT  ,
    COMMENT , NCUT    , NCOPYE  , NPASTE  , SPACE4  ,    ___XX___, KC_4    , KC_5    , KC_6    , KC_DOT  ,
    CTLK    , TERM    , BOOKMARK, EXPAND  , KC_DOWN ,    ___XX___, KC_1    , KC_2    , KC_3    , KC_COMM ,
    ________, ________, ___XX___, KC_BSPC , ___XX___,    KC_LSFT , KC_0    , ___XX___, ___XX___, QK_BOOT
  ),

  /* SYMBOL LAYER
  *.-----------------------------------------------------------------------------------------------------.
  *| A = &   | ~       | "       | '       | `       ||| -       | U = _   | I = |   | $       | P = %   |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| <       | [       | {       | (       | =       ||| +       | )       | }       | ]       | >       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| €       | X = *   | C = ^   | #       | /       ||| \       | °       | ^ (dead)| ¨       | @       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| è       |  é      | ç       |         |   ¤     |||    ¤    | XXXXXXX |    ¤    |         | à       |
  *'-----------------------------------------------------------------------------------------------------'
  */
  [_SYMB] = LAYOUT_ortho_4x10( /* SYMBOL */
    FR_AMPR , FR_TILD , FR_DQUO , FR_QUOT , FR_GRV  ,    FR_MINS , FR_UNDS , FR_PIPE , FR_DLR  , FR_PERC ,
    FR_LABK , FR_LBRC , FR_LCBR , FR_LPRN , FR_EQL  ,    FR_PLUS , FR_RPRN , FR_RCBR , FR_RBRC , FR_RABK ,
    FR_EURO , FR_ASTR , FR_CCIRC, FR_HASH , FR_SLSH ,    FR_BSLS , FR_DEG  , FR_CIRC , FR_DIAE , FR_AT   ,
    FR_EGRV , FR_EACU , CCED    , ___XX___, ___XX___,    ___XX___, ________, ___XX___, ___XX___, AGRAVE 
  ),

  /* SYMBOL ENGLISH LAYER
  *.-----------------------------------------------------------------------------------------------------.
  *| A = &   | ~       | "       | '       | `       ||| -       | U = _   | I = |   | $       | P = %   |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *| <       | [       | {       | (       | =       ||| +       | )       | }       | ]       | >       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|         | X = *   | C = ^   | #       | /       ||| \       |         |    ¤    |         | @       |
  *|---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  *|    ¤    |    ¤    |         |         |   ¤     |||    ¤    | XXXXXXX |    ¤    |         |         |
  *'-----------------------------------------------------------------------------------------------------'
  */ 
  [_SYMB_EN] = LAYOUT_ortho_4x10( /* SYMBOL */
    KC_AMPR , KC_TILD , KC_DQUO , KC_QUOT , KC_GRV  ,    KC_MINS , KC_UNDS , KC_PIPE , KC_DLR  , KC_PERC ,
    KC_LABK , KC_LBRC , KC_LCBR , KC_LPRN , KC_EQL  ,    KC_PLUS , KC_RPRN , KC_RCBR , KC_RBRC , KC_RABK ,
    ___XX___, KC_ASTR , KC_CIRC , KC_HASH , KC_SLSH ,    KC_BSLS , ___XX___, ___XX___, ___XX___, KC_AT   ,
    ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,    ___XX___, ________, ___XX___, ___XX___, ___XX___
  ),

  /* FUNCTION LAYER
  * .-----------------------------------------------------------------------------------------------------.
  * | ALT     | UNDO    | DEL     | ENT     | NEWTAB  ||| F6      | HOME    | UP      | END     | MENU    |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | CTRL    | CUT     | COPY    | PASTE   | TAB     ||| SELECTW | LEFT    | DOWN    | RIGHT   | BSPC    |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | SHIFT   | SAVE    | CTLD    | FIND    | REPLACE ||| REFRSH  |    ?    |    .    |    /    | F11     |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | (BROWS) | CLOSTW  | PALETTE | XXXXXXX | RENAME  |||         | SHIFT   | RGUI    | RCTL    | F12     |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_FNTN] = LAYOUT_ortho_4x10( /* FUNCTION */
    ALTALL  , UNDO    , KC_DEL  , KC_ENT  , NCTAB   ,    KC_F6   , KC_HOME , KC_UP   , KC_END  , APPWIN  ,
    KC_LCTL , CUT     , COPY    , PPASTE  , KC_TAB  ,    SELECTW , KC_LEFT , KC_DOWN , KC_RIGHT, KC_BSPC ,
    KC_LSFT , SAVE    , TCTLD   , FIND    , REPLACE ,    REFRSH  , FR_QUES , FR_DOT  , FR_SLSH , KC_F11  ,
    BROWS   , CLOSTW  , PALETTE , ________, KC_F2   ,    KC_SPC  , KC_RSFT , KC_RGUI , KC_RCTL , KC_F12
  ),

  [_FNTN_EN] = LAYOUT_ortho_4x10( /* FUNCTION */
    ALTALLE , UNDOE   , KC_DEL  , KC_ENT  , NCTABE  ,    KC_F6   , KC_HOME , KC_UP   , KC_END  , KC_APP  ,
    KC_LCTL , CUT     , COPY    , PPASTE  , KC_TAB  ,    SELECTW , KC_LEFT , KC_DOWN , KC_RIGHT, KC_BSPC ,
    KC_LSFT , SAVE    , TCTLD   , FIND    , REPLACE ,    REFRSH  , KC_QUES , KC_DOT  , KC_SLSH , KC_F11  ,
    BROWS   , CLOSTW  , PALETTE , ________, KC_F2   ,    KC_SPC  , KC_RSFT , KC_RGUI , KC_RCTL , KC_F12
  ),

  /* BROWSER LAYER
  * .-----------------------------------------------------------------------------------------------------.
  * |         |         | F6      |         |         |||         |         |         |         |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |         | PREV    | REFRSH  | NEXT    |         |||         |         |         |         |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |         |         | F12     |         |         |||         |         |         |         |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |         |         |         |         |         |||         |         |         |         |         |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_BROWS] = LAYOUT_ortho_4x10(
    ___XX___, ___XX___, KC_F6   , ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ___XX___, KC_WBAK , REFRSH  , KC_WFWD , ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ___XX___, ___XX___, KC_F12  , ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,
    ___XX___, ___XX___, ___XX___, ___XX___, ___XX___,   ___XX___, ___XX___, ___XX___, ___XX___, ___XX___
  ),


  /* LANGUAGE LAYER
  * .-----------------------------------------------------------------------------------------------------.
  * | á       | ž       | ě       | ř       | ť       ||| ý       | ú       | í       | ó       |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | š       | ß       | đ       |         |         |||         |         |         | ł       |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * | ś       | ź       | ć       | č       |         ||| ñ       | ň       | ń       |         |         |
  * |---------+---------+---------+---------+---------+++---------+---------+---------+---------+---------|
  * |         |         |         |         | (SFTCAP)||| (SFTCAP)|         | XXXXXXX |         |         |
  * '-----------------------------------------------------------------------------------------------------'
  */
  [_LANG] = LAYOUT_ortho_4x10( /* LANGUAGE */
    K_AACUTE, K_ZCARON, K_ECARON, K_RCARON, K_TCARON,    K_YACUTE, K_UACUTE, K_IACUTE, K_OACUTE, ___XX___,
    K_SCARON, K_SSHARP, K_DSTROK, ___XX___, ___XX___,    ___XX___, ___XX___, ___XX___, K_LSTROK, ___XX___,
    K_SACUTE, K_ZACUTE, K_CACUTE, K_CCARON, ___XX___,    K_NTILDE, K_NCARON, K_NACUTE, ___XX___, ___XX___,
    ___XX___, ___XX___, ___XX___, ___XX___, SFTCAP  ,    SFTCAP  , ___XX___, ________, ___XX___, ___XX___
  ),
};

bool process_lang_key(keyrecord_t *record, uint16_t en_key, uint16_t fr_key) {
    uint16_t key_to_process = is_french ? fr_key : en_key;
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

  const bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;

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
          set_single_default_layer(_AZ);
        } else {
          set_single_default_layer(_AZ_EN);
        }
      }
      break;

    case SPACE4:
      if (record->event.pressed) {
        SEND_STRING("    ");
      }
      break;

    case C_COMM:
      // custom comma for english keyboard (output , and ? if shifted)
      if (record->event.pressed) {
        // on keydown
        if (shifted) {
          register_code16(KC_SLSH); // S(/) = ?
        } else {
          register_code16(KC_COMM);
        }
      } else {
        // on keyup
        if (shifted) {
          unregister_code16(KC_SLSH);
        } else {
          unregister_code16(KC_COMM);
        }
      }
      return false;

    case C_SCLN:
      // custom semicolon for english keyboard (output ; and . if shifted)
      if (record->event.pressed) {
        // on keydown - store the shift state
        scln_was_shifted = shifted;
        if (shifted) {
          unregister_code(KC_LSFT);
          register_code16(KC_DOT);
        } else {
          register_code16(KC_SCLN);
        } 
      } else {
        // on keyup - use the stored shift state
        if (scln_was_shifted) {
          unregister_code16(KC_DOT);
          register_code16(KC_LSFT);
        } else {
          unregister_code16(KC_SCLN);
        }
      }
      return false;
    
    case C_COLN:
      // custom colon for english keyboard (output : and / if shifted)
      if (record->event.pressed) {
        // on keydown
        cln_was_shifted = shifted;
        if (shifted) {
          unregister_code(KC_LSFT);
          register_code16(KC_SLSH);
        } else {
          register_code16(KC_LSFT);
          register_code16(KC_SCLN); 
        }
      } else {
        // on keyup
        if (cln_was_shifted) {
          unregister_code16(KC_SLSH);
          register_code16(KC_LSFT);
        } else {
          unregister_code16(KC_SCLN);
          unregister_code16(KC_LSFT);
        }
      }
      return false;

  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
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
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  set_unicode_input_mode(UNICODE_MODE_WINDOWS);
  is_linux = true;
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
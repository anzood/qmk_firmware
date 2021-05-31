/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include "oneshot.h"
#include "swapper.h"
#include "altlayer.h"

// combo
enum combos {
  ED_DEL,
  TG_TAB,
  RF_CTRL,
  UJ_CTRL
  //AZ_FN
};

const uint16_t PROGMEM ed_combo[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM uj_combo[] = {KC_U, KC_J, COMBO_END};
//const uint16_t PROGMEM az_combo[] = {KC_A, KC_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ED_DEL] = COMBO(ed_combo, KC_DEL),
  [TG_TAB] = COMBO(tg_combo, KC_TAB),
  [RF_CTRL] = COMBO(rf_combo, KC_LCTL),
  [UJ_CTRL] = COMBO(uj_combo, KC_RCTL)
};

// layers
#define BSP_SFT SFT_T(KC_BSPC)
//#define ESC_NUM LT(NUM, KC_ESC)
//#define TAB_NUM LT(NUM, KC_TAB)
//#define ENT_NAV LT(NAV, KC_ENT)
//#define SPC_SYM LT(SYM, KC_SPC)


// helper commands
#define TABL C(S(KC_TAB))
#define TABR C(KC_TAB)
#define PGL C(KC_PGUP)
#define PGR C(KC_PGDN)


enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    FN,
    RSTL,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    // layer keycodes
    ESC_NUM,
    TAB_NUM,
    ENT_NAV,
    SPC_SYM,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                            KC_N,    KC_M,    KC_COMM, KC_DOT, KC_QUOT,
                                        BSP_SFT,  ESC_NUM,      ENT_NAV, SPC_SYM

  ),

  [SYM] = LAYOUT(
    KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                         KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_LBRC,
    KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,                          KC_DQUO, KC_HASH, KC_LT,   KC_GT,   KC_COLN,
    KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC,                         KC_EXLM, KC_SLSH, KC_AMPR, KC_QUES, KC_RBRC,
                                        KC_BSPC,  KC_TAB,      MO(RSTL),  _______
  ),

  [NAV] = LAYOUT(
    KC_APP,  KC_PGUP, SW_WIN,  KC_HOME, KC_PSCR,                         KC_NO,   TABL,    SW_WIN,    TABR,   KC_NO,  
    KC_INS,  KC_LEFT, KC_UP,   KC_RGHT, SW_LANG,                         SW_LANG, OS_CTRL, OS_ALT,    OS_SHFT,OS_CMD, 
    KC_DEL,  KC_PGDN, KC_DOWN, KC_END,  KC_ENT,                          KC_NO,   PGL,     KC_LALT,   PGR,    KC_LGUI,
                                        KC_BSPC,  TAB_NUM,      _______, MO(RSTL)
  ),

  [NUM] = LAYOUT(
    KC_NO,   TABL,    SW_WIN,  TABR,    KC_BTN3,                         KC_PSLS, KC_7,    KC_8,     KC_9,    KC_PMNS,
    OS_CMD,  OS_SHFT, OS_ALT,  OS_CTRL, KC_BTN1,                         KC_PAST, KC_4,    KC_5,     KC_6,    KC_PPLS,
    A(KC_SPC),PGL,    KC_RALT, PGR,     KC_BTN2,                         KC_0,    KC_1,    KC_2,     KC_3,    KC_PDOT,
                                        _______, _______,        ENT_NAV, KC_COMM
  ),

  [FN] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                           KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4, 
    OS_CMD,  OS_SHFT, OS_ALT,  OS_CTRL, KC_NO,                           KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8, 
    KC_CAPS, KC_SLCK, KC_NLCK, KC_PAUS, KC_NO,                           KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                                        _______,  _______,      _______,  _______
  ),

  [RSTL] = LAYOUT(
    RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                        _______,  _______,     _______, _______
  )
};

// bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case BSP_SFT:
//         case ESC_NUM:
//         case TAB_NUM:
//         case ENT_NAV:
//         case SPC_SYM:
//             return true;
//         default:
//             return false;
//     }
// }

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case ESC_NUM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

altlayer_state al_esc_num_state = al_up;
altlayer_state al_tab_num_state = al_up;
altlayer_state al_ent_nav_state = al_up;
altlayer_state al_spc_sym_state = al_up;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LGUI, KC_SPC, SW_LANG,
        keycode, record
    );

    update_altlayer(
        &al_esc_num_state, NUM, ESC_NUM, KC_ESC,
        keycode, record
    );
    update_altlayer(
        &al_tab_num_state, NUM, TAB_NUM, KC_TAB,
        keycode, record
    );
    update_altlayer(
        &al_ent_nav_state, NAV, ENT_NAV, KC_ENT,
        keycode, record
    );
    update_altlayer(
        &al_spc_sym_state, SYM, SPC_SYM, KC_SPC,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_CMD,
        keycode, record
    );


    // if (record->event.pressed) {
    //     set_keylog(keycode, record);
    // }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NUM, NAV, FN);
}

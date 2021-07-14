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

#include "analog.h"
#include "pointing_device.h"

// combo
enum combos {
  QA_WIN,
  WS_SHIFT,
  ED_ALT,
  RF_CTRL,
  TG_TAB,
  YH_DEL,
  UJ_CTRL,
  IK_ALT,
  OL_SHIFT,
  PC_WIN
  //AZ_FN
};

const uint16_t PROGMEM qa_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM ws_combo[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM ed_combo[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {KC_T, KC_G, COMBO_END};

const uint16_t PROGMEM yh_combo[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM uj_combo[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM ik_combo[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM ol_combo[] = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM pc_combo[] = {KC_P, KC_SCLN, COMBO_END};
//const uint16_t PROGMEM az_combo[] = {KC_A, KC_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [QA_WIN] = COMBO(qa_combo, KC_LGUI),
  [WS_SHIFT] = COMBO(ws_combo, KC_LSFT),
  [ED_ALT] = COMBO(ed_combo, KC_LALT),
  [RF_CTRL] = COMBO(rf_combo, KC_LCTL),
  [TG_TAB] = COMBO(tg_combo, KC_TAB),

  [YH_DEL] = COMBO(yh_combo, KC_DEL),
  [UJ_CTRL] = COMBO(uj_combo, KC_RCTL),
  [IK_ALT] = COMBO(ik_combo, KC_RALT),
  [OL_SHIFT] = COMBO(ol_combo, KC_RSFT),
  [PC_WIN] = COMBO(pc_combo, KC_RGUI),
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
#define RUL A(S(KC_6))
#define ENL A(S(KC_8))


enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    FN,
    RSTL,
    NAV_L,
    FN_L,
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
  [DEF] = LAYOUT_split_3x6_3(
    KC_NO,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_NO,
    KC_NO,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_NO,
    KC_NO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_QUOT, KC_NO,
                                         KC_NO,   BSP_SFT,  ESC_NUM,   ENT_NAV, SPC_SYM, KC_NO

  ),

  [SYM] = LAYOUT_split_3x6_3(
    KC_NO, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                         KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_LBRC,KC_NO,
    KC_NO, KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,                          KC_DQUO, KC_HASH, KC_LT,   KC_GT,   KC_COLN,KC_NO,
    KC_NO, KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC,                         KC_EXLM, KC_SLSH, KC_AMPR, KC_QUES, KC_RBRC,KC_NO,
                                      KC_NO,   KC_BSPC,  KC_TAB,     MO(RSTL),  _______, KC_NO
  ),

  [NAV] = LAYOUT_split_3x6_3(
    KC_NO, KC_APP,  KC_PGUP, SW_WIN,  KC_HOME, KC_PSCR,                         SW_LANG,   TABL,    SW_WIN,    TABR,   TG(NAV_L),  KC_NO,
    KC_NO, KC_INS,  KC_LEFT, KC_UP,   KC_RGHT, ENL,                             RUL,       OS_CTRL, OS_ALT,    OS_SHFT,OS_CMD, KC_NO,
    KC_NO, KC_DEL,  KC_PGDN, KC_DOWN, KC_END,  KC_ENT,                          ENL,   PGL,     KC_LALT,   PGR,    KC_LGUI,KC_NO,
                                      KC_NO,   KC_BSPC,  TAB_NUM,      _______, MO(RSTL),KC_NO
  ),

  [NUM] = LAYOUT_split_3x6_3(
    KC_NO, KC_NO,   TABL,    SW_WIN,  TABR,    KC_BTN3,                         KC_PSLS, KC_7,    KC_8,     KC_9,    KC_PMNS, KC_NO,
    KC_NO, OS_CMD,  OS_SHFT, OS_ALT,  OS_CTRL, KC_BTN1,                         KC_PAST, KC_4,    KC_5,     KC_6,    KC_PPLS, KC_NO,
    KC_NO, A(KC_SPC),PGL,    KC_RALT, PGR,     KC_BTN2,                         KC_0,    KC_1,    KC_2,     KC_3,    KC_PDOT, KC_NO,
                                      KC_NO,   _______, _______,        ENT_NAV, KC_PCMM, KC_NO
  ),

  [FN] = LAYOUT_split_3x6_3(
    KC_NO, TG(FN_L),KC_NO,   KC_NO,   KC_NO,   KC_NO,                           KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_NO,
    KC_NO, OS_CMD,  OS_SHFT, OS_ALT,  OS_CTRL, KC_NO,                           KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_NO,
    KC_NO, KC_CAPS, KC_SLCK, KC_NLCK, KC_PAUS, KC_NO,                           KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_NO,
                                      KC_NO,   _______,  _______,      _______,  _______, KC_NO
  ),

  [RSTL] = LAYOUT_split_3x6_3(
    KC_NO, RESET,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET, KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                                          KC_NO, _______,  _______,     _______, _______, KC_NO
  ),

  [NAV_L] = LAYOUT_split_3x6_3(
    KC_NO, KC_APP,  KC_PGUP, KC_ESC,  KC_HOME, KC_PSCR,                         RUL,     TABL,    KC_ESC,    TABR,   TG(NAV_L),  KC_NO,
    KC_NO, KC_INS,  KC_LEFT, KC_UP,   KC_RGHT, ENL,                             RUL,     KC_RCTL, KC_RALT,   KC_RSFT,KC_RGUI, KC_NO,
    KC_NO, KC_DEL,  KC_PGDN, KC_DOWN, KC_END,  KC_ENT,                          ENL,     PGL,     KC_LALT,   PGR,    KC_LGUI,KC_NO,
                                      KC_NO,   KC_BSPC,  TAB_NUM,      KC_ENT, KC_SPC, KC_NO
  ),

  [FN_L] = LAYOUT_split_3x6_3(
    KC_NO, TG(FN_L),KC_NO,   KC_NO,   KC_NO,   KC_NO,                           KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_NO,
    KC_NO, KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, KC_NO,                           KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_NO,
    KC_NO, KC_CAPS, KC_SLCK, KC_NLCK, KC_PAUS, KC_NO,                           KC_NO,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_NO,
                                      KC_NO,   _______,  _______,      _______,  _______, KC_NO
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


// Set Parameters
#define ONES(x) (fmax(fmin(x, 1.0), -1.0))
#define SIGN(x) ((x > 0) - (x < 0))
//int swPin = B6; // SW
const pin_t swPin = B6; // SW
const pin_t xPin = B5;
const pin_t yPin = B4;

uint16_t x_scale = 512;
uint16_t y_scale = 512;
uint16_t x_dead = 0;
uint16_t y_dead = 0;
int16_t xcen, ycen;

float maxCursorSpeed = 0.2;  // holding shift
float minCursorSpeed = 0.07;
//float maxScrollSpeed = 0.02;  // holding shift
//float minScrollSpeed = 0.01;

int8_t xPolarity = 1;
int8_t yPolarity = -1;

uint8_t cursorTimeout = 10;
uint16_t lastCursor = 0;
int16_t vcntr = 0;
int16_t hcntr = 0;
int16_t max_cntr = 256;


void pointing_device_task(void) {
    if (!is_master) return; // joystic is on the master
    if (timer_elapsed(lastCursor) < cursorTimeout) return;
    lastCursor = timer_read();

    report_mouse_t report = pointing_device_get_report();
    int16_t x = analogReadPin(xPin);
    int16_t y = analogReadPin(yPin);
    int16_t xd = x-xcen;
    int16_t yd = y-ycen;
    if ( abs(xd) > x_dead || abs(yd) > y_dead ) {
        float xperc = ONES( (float)xd / x_scale);
        float yperc = ONES( (float)yd / y_scale);
        int8_t xmove = (int8_t)(xperc * 127.0);
        int8_t ymove = (int8_t)(yperc * 127.0);

        //layer_state
        uint8_t layer = biton32(layer_state);
        //if (get_mods() & MOD_MASK_GUI) {
        if (layer == NAV) {
            //float scroll_speed = (get_mods() & MOD_MASK_SHIFT) ? maxScrollSpeed : minScrollSpeed;
            //report.h = xPolarity * xmove * scroll_speed;
            //report.v = xPolarity * ymove * scroll_speed;
            vcntr += xPolarity * ymove;
            hcntr += xPolarity * xmove;
            
            report.v = (int8_t)(vcntr / max_cntr);
            report.h = (int8_t)(hcntr / max_cntr);

            vcntr %= max_cntr;
            hcntr %= max_cntr;
            
        } else {
            float cursor_speed = (get_mods() & MOD_MASK_SHIFT) ? maxCursorSpeed : minCursorSpeed;
            report.x = xPolarity * xmove * cursor_speed;
            report.y = yPolarity * ymove * cursor_speed;
        }
    } 
    // mouse click
    // if (readPin(swPin)) {
    //     report.buttons |= MOUSE_BTN1;
    // } else {
    //     report.buttons &= ~MOUSE_BTN1;
    // }
    // OR:
    // if (digitalRead(swPin) == 1) {
    //   report.buttons |= MOUSE_BTN1;
    // }

    pointing_device_set_report(report);
    pointing_device_send();
}

// void matrix_init_keymap(void) {
void keyboard_post_init_user(void) {
    // init pin? Is needed?
    // setPinInputHigh(E6);
    // Account for drift
    xcen = analogReadPin(xPin);
    ycen = analogReadPin(yPin);
    debug_enable=true;
    //debug_matrix=true;
}

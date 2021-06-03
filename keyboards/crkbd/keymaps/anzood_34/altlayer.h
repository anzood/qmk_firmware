#pragma once

#include QMK_KEYBOARD_H


typedef enum {
    al_up,
    al_down_unused,
    al_down_used,
} altlayer_state;


void update_altlayer(
    altlayer_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t tapcode,
    uint16_t keycode,
    keyrecord_t *record
);

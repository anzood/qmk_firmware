#include "altlayer.h"

void update_altlayer(
    altlayer_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t tapcode,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == al_up) {
                layer_on(layer);
            }
            *state = al_down_unused;
        } else {
            // Trigger keyup
            layer_off(layer);
            if (*state == al_down_unused) {
                tap_code16(tapcode);
            }
            *state = al_up;
        }
    } else {
        if (record->event.pressed) {
            if (*state == al_down_unused) {
                // Trigger was used as layer mod
                *state = al_down_used;
            }
        }
    }
}

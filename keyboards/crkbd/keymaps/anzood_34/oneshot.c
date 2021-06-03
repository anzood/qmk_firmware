#include "oneshot.h"

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            //*state = os_down_unused;
            *state = os_down_waiting;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
            case os_down_waiting:
                // If we didn't use the mod while trigger was held, queue it.
                //*state = os_up_queued;
                *state = os_up_waiting;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (*state != os_up_unqueued) {
                if (is_oneshot_cancel_key(keycode)) {
                    // Cancel oneshot on designated cancel keydown.
                    *state = os_up_unqueued;
                    unregister_code(mod);
                } else if (!is_oneshot_ignored_key(keycode)) {
                    if (*state == os_up_waiting) {
                        *state = os_up_queued;
                    } else if (*state == os_down_waiting) {
                        *state = os_down_unused;
                    }
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_down_waiting:
                    *state = os_down_unused;
                    break;
                case os_up_waiting:
                    *state = os_up_queued;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

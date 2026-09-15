// Copyright 2021 @Yowkees
// Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
// Copyright 2026 Idan Kamara (@idank)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "users/holykeebs/holykeebs.h"

#define MOUSE_LAYER 1

enum custom_keycodes {
    MSE_OFF = SAFE_RANGE,  // Exit mouse layer without typing a character
    MSE_TOG,               // Toggle auto-mouse-layer on/off
};

// Whether auto-mouse-layer is enabled.  Starts on; toggled by MSE_TOG.
static bool mouse_layer_enabled = true;

// Accumulated movement counters for threshold gating.
static int16_t mouse_accu_x = 0;
static int16_t mouse_accu_y = 0;

// Soft-compress a scroll value: below threshold passes through 1:1,
// above threshold the excess is divided by SCROLL_CLAMP_DIVISOR.
static inline int16_t soft_clamp_scroll(int16_t v) {
    if (v == 0) return 0;
    int16_t sign  = v > 0 ? 1 : -1;
    int16_t abs_v = v > 0 ? v : -v;
    if (abs_v <= SCROLL_CLAMP_THRESHOLD) return v;
    return sign * (SCROLL_CLAMP_THRESHOLD + (abs_v - SCROLL_CLAMP_THRESHOLD) / SCROLL_CLAMP_DIVISOR);
}

// Called by the holykeebs userspace after it processes the combined mouse
// report.  We accumulate movement and only activate the mouse layer once the
// total exceeds MOUSE_LAYER_THRESHOLD, matching QMK's AML behaviour.
report_mouse_t pointing_device_task_combined_keymap(report_mouse_t report) {
    if (mouse_layer_enabled) {
        mouse_accu_x += report.x;
        mouse_accu_y += report.y;
        if (abs(mouse_accu_x) > MOUSE_LAYER_THRESHOLD || abs(mouse_accu_y) > MOUSE_LAYER_THRESHOLD) {
            layer_on(MOUSE_LAYER);
            mouse_accu_x = 0;
            mouse_accu_y = 0;
        }
    }
    // Soft-compress scroll output to tame OS acceleration on fast flicks
    // while leaving slow/medium scrolling unchanged.
    report.h = soft_clamp_scroll(report.h);
    report.v = soft_clamp_scroll(report.v);

    return report;
}

// Returns true for keycodes that should NOT deactivate the mouse layer.
static bool is_mouse_or_pass_key(uint16_t keycode) {
    // Mouse buttons / movement
    if (keycode >= MS_BTN1 && keycode <= MS_BTN8) return true;
    // Modifier keys (Shift, Ctrl, Alt, GUI)
    if (keycode >= KC_LEFT_CTRL && keycode <= KC_RIGHT_GUI) return true;
    // Layer keys (MO, LT, TO, TG, ...)
    if ((keycode >= QK_MOMENTARY        && keycode <= QK_MOMENTARY_MAX)  ||
        (keycode >= QK_LAYER_TAP        && keycode <= QK_LAYER_TAP_MAX)  ||
        (keycode >= QK_TO               && keycode <= QK_TO_MAX)         ||
        (keycode >= QK_TOGGLE_LAYER     && keycode <= QK_TOGGLE_LAYER_MAX)) return true;
    // Our own exit / toggle keys
    if (keycode == MSE_OFF || keycode == MSE_TOG) return true;
    if (keycode == KC_NO || keycode == XXXXXXX)   return true;
    // Sniping keys on Layer 1 — keep mouse layer active while adjusting precision
    if (keycode == HK_S_MODE || keycode == HK_S_MODE_T) return true;
    // Navigation / editing keys explicitly mapped on Layer 1
    if (keycode == KC_UP || keycode == KC_DOWN || keycode == KC_LEFT || keycode == KC_RIGHT) return true;
    if (keycode == KC_PGUP || keycode == KC_PGDN) return true;
    if (keycode == KC_ENT  || keycode == KC_DEL) return true;
    // Function keys mapped on Layer 1 row 1
    if (keycode >= KC_F1 && keycode <= KC_F12) return true;
    return false;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MSE_OFF:
            if (record->event.pressed) {
                layer_off(MOUSE_LAYER);
                mouse_accu_x = 0;
                mouse_accu_y = 0;
            }
            return false;

        case MSE_TOG:
            if (record->event.pressed) {
                mouse_layer_enabled = !mouse_layer_enabled;
                set_auto_mouse_enable(mouse_layer_enabled);
                if (!mouse_layer_enabled) layer_off(MOUSE_LAYER);
                mouse_accu_x = 0;
                mouse_accu_y = 0;
            }
            return false;
    }

    // Any regular key press while on the mouse layer exits it.
    if (record->event.pressed && layer_state_is(MOUSE_LAYER) && !is_mouse_or_pass_key(keycode)) {
        layer_off(MOUSE_LAYER);
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
              KC_LALT,KC_LGUI,LCTL_T(KC_LNG2)     ,LT(1,KC_SPC),LT(3,KC_LNG1),                  KC_BSPC,LT(2,KC_ENT), RCTL_T(KC_LNG2),     KC_RALT  , KC_PSCR
  ),

  // Mouse layer: activates automatically on ball movement, exits on any
  // regular key press or MSE_OFF (left inner thumb position).
  [1] = LAYOUT_universal(
    _______     ,  KC_F1   , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______     ,  _______ , _______  , KC_UP   , KC_ENT   , KC_DEL   ,                                         KC_PGUP  , MS_BTN1  , KC_UP    , MS_BTN2  , MS_BTN3  , KC_F12   ,
    _______     ,  _______ , KC_LEFT  , KC_DOWN , KC_RGHT  , KC_BSPC  ,                                         KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , HK_S_MODE_T, HK_S_MODE,
                  _______  , _______  , _______  ,         MSE_OFF  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,S(KC_QUOT), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                         S(KC_9)  , S(KC_1)  , S(KC_6)  , KC_LBRC  , S(KC_4)  , _______  ,
    _______  ,S(KC_SCLN), KC_4     , KC_5    , KC_6     , KC_RBRC  ,                                         KC_NUHS  , KC_MINS  , S(KC_EQL), S(KC_3)  , KC_QUOT  , S(KC_2)  ,
    _______  ,S(KC_MINS), KC_1     , KC_2    , KC_3     ,S(KC_RBRC),                                        S(KC_NUHS),S(KC_INT1), KC_EQL   ,S(KC_LBRC),S(KC_SLSH),S(KC_INT3),
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                   KC_DEL   , _______  , _______       , _______  , _______
  ),

  // Settings layer: hold right inner thumb.  Ball scrolls while held.
  // MSE_TOG toggles auto-mouse-layer on/off (replaces HK_AML_T).
  [3] = LAYOUT_universal(
    RM_TOGG  , MSE_TOG  , HK_AML_UP, HK_AML_DN, _______  , HK_BONGO_T,                                       HK_DUMP  , RM_SPDU  , RM_SPDD  , _______  , _______  , _______  ,
    _______  , _______  , _______  , RM_VALU  , KC_UP    , HK_S_MODE ,                                       HK_P_SET_D, HK_P_SET_S, HK_P_SET_THR, _______, _______  , _______  ,
    _______  , _______  , _______  , RM_VALD  , KC_DOWN  , HK_S_MODE_T,                                      _______  , _______  , HK_C_SCROLL, HK_I_SCROLL, _______  , HK_SAVE  ,
                  QK_BOOT  , HK_RESET , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , HK_RESET , QK_BOOT
  ),
};
// clang-format on

// Prevent QMK's built-in AML task from managing the mouse layer — we handle
// activation in pointing_device_task_combined_keymap and deactivation in
// process_record_keymap.  POINTING_DEVICE_AUTO_MOUSE_ENABLE is still defined
// so the OLED can read get_auto_mouse_enable() for its status display.
bool auto_mouse_activation(report_mouse_t mouse_report) {
    return false;
}

// Red on mouse layer, green otherwise.  Both scale with the RGB brightness
// setting (RM_VALU/RM_VALD on Layer 3) so the indicator respects dim/bright.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t val = rgb_matrix_get_val();
    uint8_t r   = layer_state_is(MOUSE_LAYER) ? val : 0;
    uint8_t g   = layer_state_is(MOUSE_LAYER) ? 0   : val;
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, r, g, 0);
    }
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    hk_set_dragscroll_both(get_highest_layer(state) == 3);
    return state;
}

// Called by holykeebs after EEPROM is loaded.  Drag scroll may have been saved
// as enabled (e.g. via HK_D_MODE_T); reset it here so the layer-managed
// behaviour in layer_state_set_user is always authoritative at boot.
void keyboard_post_init_keymap(void) {
    hk_set_dragscroll_both(false);
}

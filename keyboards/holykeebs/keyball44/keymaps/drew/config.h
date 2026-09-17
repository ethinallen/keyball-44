// Copyright 2026 Drew
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Default scroll throttle for PMW3360.  The hires-scroll formula is:
//   scroll_units = motion_counts × 120 / throttle
// where 120 hires units = 1 scroll line.  The factory default (5) is very
// fast for a 34 mm ball.  40 is a reasonable starting point (~8× slower).
// Adjust live: on layer 3, hold HK_P_SET_THR (right-side row 2, 3rd from center)
// then tap UP to slow down or DOWN to speed up, then press HK_SAVE to persist.
#define HK_MAIN_DEFAULT_POINTER_SCROLL_THROTTLE       40
#define HK_PERIPHERAL_DEFAULT_POINTER_SCROLL_THROTTLE 40

// POINTING_DEVICE_AUTO_MOUSE_ENABLE is defined so that:
//   - the holykeebs OLED can read get_auto_mouse_enable() for its status display
//   - set_auto_mouse_enable() / set_auto_mouse_layer() are available
// Actual layer switching is handled in keymap.c (not by QMK's AML task),
// because QMK's AML does not reliably detect movement through the holykeebs
// combined pointing device pipeline.
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1

// Soft scroll compression: hires scroll values (120 = 1 line) below
// SCROLL_CLAMP_THRESHOLD pass through unchanged.  Above the threshold the
// excess is divided by SCROLL_CLAMP_DIVISOR, so fast flicks are still faster
// than slow scrolling — just not insanely fast.
//
// Example at threshold=5, divisor=4:
//   input  5 →  5  (unchanged, slow scroll)
//   input 10 →  6  (5 + 5/4)
//   input 25 → 10  (5 + 20/4)
//   input 50 → 16  (5 + 45/4)
#define SCROLL_CLAMP_THRESHOLD 5
#define SCROLL_CLAMP_DIVISOR   4

// Minimum total mouse movement (x or y) required to activate the mouse layer.
// Matches QMK's AUTO_MOUSE_THRESHOLD default of 10.  Raise this value if the
// mouse layer triggers during typing from vibration; lower it if it feels slow
// to activate when you intentionally move the ball.
#define MOUSE_LAYER_THRESHOLD 10

// Bump this whenever the compiled keymap changes significantly, so that VIA's
// EEPROM keymap (which persists across flashes) is invalidated and re-initialized
// from the compiled layout.  Without this, Remap's stored keymap survives
// reflashes and can shadow keys that were changed in source (e.g. adding SNPT/SNIP
// to Layer 1).  Increment by 1 each time you need a forced EEPROM reset.
#define VIA_FIRMWARE_VERSION 2

// The userspace config.h applies ROTATION_270_RIGHT + INVERT_Y_RIGHT, which
// was calibrated for keyball61plus.  For keyball44 the sensor is mounted with
// a different orientation; the correct mapping is (sensor_y, sensor_x) for the
// right-side ball, which requires ROTATION_90_RIGHT + INVERT_Y_RIGHT.
#undef POINTING_DEVICE_ROTATION_270_RIGHT
#define POINTING_DEVICE_ROTATION_90_RIGHT

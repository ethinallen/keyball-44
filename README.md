# Keyball44 Keymap — drew

A custom QMK keymap for the [Keyball44](https://holykeebs.com) built on the
[holykeebs firmware fork](https://github.com/holykeebs/qmk_firmware). Designed
for daily use on macOS with Japanese IME (JIS-style thumb keys, English key layout).

## Features

- **Auto-mouse layer** — Layer 1 activates automatically on trackball movement
  once accumulated movement exceeds a configurable threshold (default 10 units,
  matching QMK's `AUTO_MOUSE_THRESHOLD`). Exits cleanly when any regular key is
  pressed. A dedicated `EXIT` key leaves the layer silently with no spurious character.
- **RGB layer indicator** — keyboard glows green on the base layer and red on the
  mouse layer so it's always obvious which mode is active.
- **Sniping on the mouse layer** — SNPT (toggle) and SNIP (hold) are available
  directly on Layer 1 so precise cursor positioning works without activating drag scroll.
- **Soft scroll compression** — tames macOS scroll acceleration on fast trackball
  flicks while leaving slow/medium scrolling unchanged. Tunable via `SCROLL_CLAMP_*`.
- **Adjustable scroll throttle** — linear hires-scroll divisor, default 40 (~8×
  slower than holykeebs factory default of 5). Tunable live on Layer 3 without reflashing.
- **Correct axis orientation** — fixes the sensor rotation for Keyball44 (different
  from the keyball61plus the holykeebs userspace defaults to).
- **RGB Matrix** — full RGB control keycodes on Layer 3.
- **OLED support** — bongocat animation, AML on/off status, pointer state display.
- **VIA/Remap compatible** — upload `via.json` from the holykeebs firmware tree to
  Remap for live keymap editing.

## Layer Overview

### Layer 0 — Base (QWERTY)

```
┌──────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬──────┐
│ ESC  │  Q  │  W  │  E  │  R  │  T  │   │  Y  │  U  │  I  │  O  │  P  │ DEL  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ TAB  │  A  │  S  │  D  │  F  │  G  │   │  H  │  J  │  K  │  L  │  ;  │  '   │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ SFT  │  Z  │  X  │  C  │  V  │  B  │   │  N  │  M  │  ,  │  .  │  /  │  ¥   │
└──────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴──────┘
┌─────┬─────┬─────────┬────────┬─────────┐  ┌──────┬────────┬─────────┬──────┬──────┐
│ ALT │ CMD │ 英·CTL  │ SPC·L1 │ かな·L3 │  │ BSP  │ ENT·L2 │  英·CTL │ RALT │ PSCR │
└─────┴─────┴─────────┴────────┴─────────┘  └──────┴────────┴─────────┴──────┴──────┘
```

Dual-role thumb keys (tap · hold):
- `英·CTL` — tap = 英数 (ASCII input), hold = Ctrl
- `SPC·L1` — tap = Space, hold = Layer 1 (Mouse)
- `かな·L3` — tap = かな (Japanese input), hold = Layer 3 (Settings)
- `ENT·L2` — tap = Enter, hold = Layer 2 (Symbols)
- `'` = S(KC_7) — apostrophe on JIS, `&` on US layout
- `¥` = INT1 key — yen/backslash

### Layer 1 — Mouse *(auto-activates on trackball movement)*

```
┌──────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬──────┐
│ ___  │ F1  │ F2  │ F3  │ F4  │ F5  │   │ F6  │ F7  │ F8  │ F9  │ F10 │ F11  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │ ___ │ ___ │  ↑  │ ENT │ DEL │   │PGUP │ LMB │  ↑  │ RMB │ MMB │ F12  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │ ___ │  ←  │  ↓  │  →  │ BSP │   │PGDN │  ←  │  ↓  │  →  │SNPT │SNIP  │
└──────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴──────┘
┌─────┬─────┬─────┬──────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┐
│ ___ │ ___ │ ___ │ EXIT │ ___ │           │ ___ │ ___ │ ___ │ ___ │ ___ │
└─────┴─────┴─────┴──────┴─────┘           └─────┴─────┴─────┴─────┴─────┘
```

- Auto-activates when accumulated trackball movement exceeds threshold (default 10 units)
- Keyboard glows **red** while this layer is active; **green** on all other layers
- `EXIT` (left inner thumb) — leave mouse layer without sending any character
- ESC and TAB fall through to base layer — pressing ESC actually sends ESC
- Left arrow cluster (D/X/C/V) — cursor keys for text navigation while on mouse layer
- Right side (J/K/L/;/M/,/.) — mouse buttons + mirrored cursor keys
- `SNPT` (/ position) — toggle sniping mode on/off for precise cursor positioning
- `SNIP` (¥ position) — hold to enter sniping mode, releases when finger lifts
- Arrow keys, page up/down, F1–F12, enter, delete, backspace, and sniping keys keep the layer active
- Any other key press exits the layer automatically

### Layer 2 — Symbols / Numpad *(hold ENT)*

```
┌──────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬──────┐
│ ___  │  "  │  7  │  8  │  9  │  *  │   │  (  │  !  │  ^  │  [  │  $  │ ___  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │  :  │  4  │  5  │  6  │  ]  │   │  \  │  -  │  +  │  #  │  '  │  @   │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │  _  │  1  │  2  │  3  │  }  │   │  |  │  ¥\ │  =  │  {  │  ?  │  ‡   │
└──────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴──────┘
┌─────┬─────┬─────┬─────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┐
│  0  │  .  │ ___ │ ___ │ ___ │           │ DEL │ ___ │ ___ │ ___ │ ___ │
└─────┴─────┴─────┴─────┴─────┘           └─────┴─────┴─────┴─────┴─────┘
```

Numpad (1–9, 0, .) on the left; symbols on the right. Some symbols (‡, ¥\\)
are JIS-specific and depend on your macOS keyboard layout setting.

### Layer 3 — Settings *(hold かな — drag scroll active while held)*

```
┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬─────┬─────┬──────┐
│ RTOG │ MTOG │ AML+ │ AML- │ ___  │ BNGO │   │ DUMP │ SPD+ │ SPD- │ ___ │ ___ │ ___  │
├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼─────┼─────┼──────┤
│ RNXT │ HUE+ │ SAT+ │ BRT+ │  ↑   │ SNIP │   │ SENS │ SNPS │ THRO │ ___ │ ___ │ ___  │
├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼─────┼─────┼──────┤
│ RPRV │ HUE- │ SAT- │ BRT- │  ↓   │ SNPT │   │ DRAG │ DRGT │ CSRL │ISRL │ ___ │ SAVE │
└──────┴──────┴──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴─────┴─────┴──────┘
┌──────┬──────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬──────┬──────┐
│ BOOT │ RST  │ ___ │ ___ │ ___ │               │ ___ │ ___ │ ___ │ RST  │ BOOT │
└──────┴──────┴─────┴─────┴─────┘               └─────┴─────┴─────┴──────┴──────┘
```

| Key  | Function |
|------|----------|
| RTOG | Toggle RGB on/off |
| RNXT / RPRV | Next / previous RGB animation mode |
| HUE± / SAT± / BRT± | Hue / saturation / brightness |
| SPD± | RGB animation speed |
| MTOG | Toggle auto-mouse layer on/off |
| AML± | Auto-mouse layer timeout ±50ms |
| BNGO | Toggle bongocat OLED animation |
| SNIP / SNPT | Enter / toggle sniping mode (reduced sensitivity). Also available on Layer 1 for use without activating drag scroll. |
| DRAG / DRGT | Enter / toggle drag-scroll mode |
| CSRL | Cycle scroll lock: off → horizontal-only → vertical-only → off |
| ISRL | Invert scroll direction |
| SENS | Hold + tap ↑/↓ to adjust default pointer sensitivity |
| SNPS | Hold + tap ↑/↓ to adjust sniping sensitivity |
| THRO | Hold + tap ↑/↓ to adjust scroll throttle (↑ = slower) |
| SAVE | Write all settings to EEPROM (¥ key, bottom-right corner) |
| RST  | Reset HK settings to firmware defaults |
| BOOT | Enter bootloader (keyboard appears as RPI-RP2 drive) |

> **Drag scroll** is always active while Layer 3 is held — you don't need
> DRAG/DRGT for a one-off scroll session. Use DRGT to leave it on permanently.

> **Sniping on Layer 3** activates drag scroll at the same time (Layer 3 forces
> drag scroll). Use the SNPT/SNIP keys on **Layer 1** instead when you want
> precise cursor movement without scrolling.

> **Adjusting THRO/SENS/SNPS:** hold the key, tap ↑ (F) or ↓ (V) on the left
> side, then press SAVE (¥, bottom-right) while still holding かな to persist.

## Configuration

Key build-time options in `config.h`:

| Define | Default | Description |
|--------|---------|-------------|
| `MOUSE_LAYER_THRESHOLD` | `10` | Accumulated movement required to activate the mouse layer. Raise if the layer triggers during typing; lower if it feels slow to activate. |
| `HK_MAIN_DEFAULT_POINTER_SCROLL_THROTTLE` | `40` | Default scroll speed divisor. Higher = slower. Adjustable live via THRO on Layer 3. |
| `HK_PERIPHERAL_DEFAULT_POINTER_SCROLL_THROTTLE` | `40` | Same for the peripheral (left) half. |
| `SCROLL_CLAMP_THRESHOLD` | `5` | Hires scroll values at or below this pass through unchanged. Above it, excess is compressed by the divisor. |
| `SCROLL_CLAMP_DIVISOR` | `4` | Divisor applied to scroll values above the threshold. Higher = more compression on fast flicks. |

## Prerequisites

- [holykeebs/qmk_firmware](https://github.com/holykeebs/qmk_firmware) — clone and
  check out the `hk-master` branch
- [holykeebs/qmk-userspace](https://github.com/holykeebs/qmk-userspace) — symlink
  `users/holykeebs` into your firmware tree:
  ```
  ln -s /path/to/qmk-userspace/users/holykeebs /path/to/qmk_firmware/users/holykeebs
  ```

## Installation

```bash
cp -r keyboards/holykeebs/keyball44/keymaps/drew \
      /path/to/qmk_firmware/keyboards/holykeebs/keyball44/keymaps/drew
```

## Building

```bash
cd /path/to/qmk_firmware
make holykeebs/keyball44:drew
```

The `.uf2` file will be at `.build/holykeebs_keyball44_drew.uf2`.

## Flashing

1. Double-tap the reset button on one half — it appears as `RPI-RP2` on your Mac
2. `cp .build/holykeebs_keyball44_drew.uf2 /Volumes/RPI-RP2/`
3. Repeat for the other half
4. Flash the right half (master/USB side) first

## Credits

- [holykeebs](https://holykeebs.com) — firmware fork, userspace, and keyboard design
- [Yowkees](https://github.com/Yowkees) — original Keyball series
- [QMK Firmware](https://qmk.fm)

# Keyball44 Keymap — drew

A custom QMK keymap for the [Keyball44](https://holykeebs.com) built on the
[holykeebs firmware fork](https://github.com/holykeebs/qmk_firmware). Designed
for daily use on macOS with Japanese IME (JIS-style thumb keys, English key layout).

## Features

- **Auto-mouse layer** — Layer 1 activates automatically on trackball movement and
  exits cleanly when any regular key is pressed. A dedicated `MSE_OFF` key exits the
  layer silently (no spurious character sent).
- **Adjustable scroll throttle** — Linear hires-scroll divisor, default 40 (~8×
  slower than holykeebs factory default of 5). Tunable live on Layer 3 without
  reflashing.
- **Correct axis orientation** — Fixes the sensor rotation for Keyball44 (different
  from the keyball61plus the holykeebs userspace defaults to).
- **RGB Matrix** — Full RGB control keycodes on Layer 3.
- **OLED support** — Bongocat animation, AML on/off status, pointer state display.
- **VIA/Remap compatible** — Upload `via.json` from the holykeebs firmware tree to
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

### Layer 1 — Mouse *(auto-activates on trackball movement)*

```
┌──────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬──────┐
│ ___  │ F1  │ F2  │ F3  │ F4  │ F5  │   │ F6  │ F7  │ F8  │ F9  │ F10 │ F11  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │ ___ │ ___ │  ↑  │ ENT │ DEL │   │PGUP │ LMB │  ↑  │ RMB │ MMB │ F12  │
├──────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼──────┤
│ ___  │ ___ │  ←  │  ↓  │  →  │ BSP │   │PGDN │  ←  │  ↓  │  →  │ ___ │ ___  │
└──────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴──────┘
┌─────┬─────┬─────┬──────┬─────┐           ┌─────┬─────┬─────┬─────┬─────┐
│ ___ │ ___ │ ___ │ EXIT │ ___ │           │ ___ │ ___ │ ___ │ ___ │ ___ │
└─────┴─────┴─────┴──────┴─────┘           └─────┴─────┴─────┴─────┴─────┘
```

- `EXIT` (left inner thumb) — leave mouse layer without sending any character
- Left arrow cluster (D/X/C/V) — cursor keys for text navigation
- Right side (J/K/L/;/M/,/.) — mouse buttons + mirrored cursor keys
- Any regular key press exits the layer automatically

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
depend on your macOS keyboard layout setting (Japanese vs US).

### Layer 3 — Settings *(hold かな — drag scroll active while held)*

```
┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬─────┬─────┬──────┐
│ RTOG │ MTOG │ AML+ │ AML- │ ___  │ BNGO │   │ DUMP │ SPD+ │ SPD- │ ___ │ ___ │ ___  │
├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼─────┼─────┼──────┤
│ RNXT │ HUE+ │ SAT+ │ BRT+ │  ↑   │ SNIP │   │ SENS │ SNPS │ THRO │ ___ │ ___ │ ___  │
├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼─────┼─────┼──────┤
│ RPRV │ HUE- │ SAT- │ BRT- │  ↓   │ SNPT │   │ DRAG │ DRGT │ ___  │ ___ │ ___ │ SAVE │
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
| SNIP / SNPT | Enter / toggle sniping mode (reduced sensitivity) |
| DRAG / DRGT | Enter / toggle drag-scroll mode |
| SENS | Hold + tap ↑/↓ to adjust default pointer sensitivity |
| SNPS | Hold + tap ↑/↓ to adjust sniping sensitivity |
| THRO | Hold + tap ↑/↓ to adjust scroll throttle (↑ = slower) |
| SAVE | Write all settings to EEPROM |
| RST  | Reset HK settings to firmware defaults |
| BOOT | Enter bootloader (keyboard appears as RPI-RP2 drive) |

> **Tip:** Drag scroll is always active while Layer 3 is held — you don't need
> DRAG/DRGT for a one-off scroll session. Use DRGT to leave it on permanently.

> **Tip:** After adjusting THRO/SENS/SNPS, press SAVE (¥ key, bottom-right corner)
> while still holding かな to persist across power cycles.

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

## Scroll Speed

Default scroll throttle is 40. To adjust live:

1. Hold **かな** (Layer 3)
2. Hold **K** (THRO) and tap **F** (↑ = slower) or **V** (↓ = faster)
3. Press **¥** (SAVE, bottom-right corner) while still holding かな

## Credits

- [holykeebs](https://holykeebs.com) — firmware fork, userspace, and keyboard design
- [Yowkees](https://github.com/Yowkees) — original Keyball series
- [QMK Firmware](https://qmk.fm)

/* Copyright 2019-2023 Thomas Baart <thomas@splitkb.com> with modifications by
 * Olaf Kokman <github handle Kolkman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "action_code.h"
#include "color.h"
#include "keycodes.h"
#include "kolkman.h"
#include "quantum_keycodes.h"
#include "rgblight.h"
#include <stdbool.h>
#include QMK_KEYBOARD_H

enum {
  TD_SCLN_ENT,
  TD_SPC_ENT,
};

// Aliases for readability
#define QWERTY DF(_QWERTY)
#ifdef ENABLE_COLEMAK
#define COLEMAK DF(_COLEMAK_DH)
#else
#define COLEMAK _______
#endif
#ifdef ENABLE_DVORAK
#define DVORAK DF(_DVORAK)
#else
#define DVORAK _______
#endif
#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define ADJUST MO(_ADJUST)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define GUI_ENT MT(MOD_LGUI, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard
// shortcut Alt+Enter. The notation `mod/tap` denotes a key that activates the
// modifier `mod` when held down, and produces the key `tap` when tapped (i.e.
// pressed and released).

// See https://precondition.github.io/home-row-mods
// Using a CAGS layout
// Control, ALT (Option), GUI (Command), Shift
// Results in
// LCTL_T(KC_A) ,  LALT_T(KC_S)  ,  LGUI_T(KC_D)  ,  LSFT_T(KC_F)
// RSFT_T(KC_J) ,  RGUI_T(KC_K),   LALT_T(KKC_L) , RCTL_T(K_SCLN)

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SCLN_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_ENT),
    [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
};

// clang-format off
      const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      /*
      * Base Layer: QWERTY
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |CapsLk|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
      *                        |      |      | Enter|      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_QWERTY] = LAYOUT(
          KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
          CTL_ESC , LCTL_T(KC_A) ,  LALT_T(KC_S)  ,  LGUI_T(KC_D)  ,  LSFT_T(KC_F) ,   KC_G ,           KC_H,   RSFT_T(KC_J) ,  RGUI_T(KC_K),   LALT_T(KC_L) , RCTL_T(KC_SCLN) ,KC_QUOTE
          ,
          KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                  ADJUST , KC_LALT, GUI_ENT, TD(TD_SPC_ENT) , NAV   ,     SYM    , TD(TD_SPC_ENT)  ,KC_RGUI, KC_RALT  , KC_APP
          ),


      #ifdef ENABLE_DVORAK
      /*
      * Base Layer: Dvorak
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  Bksp  |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |Ctrl/Esc|   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |Ctrl/- _|
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * | LShift | ; :  |   Q  |   J  |   K  |   X  | [ {  |CapsLk|  |F-keys|  ] } |   B  |   M  |   W  |   V  |   Z  | RShift |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
      *                        |      |      | Enter|      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_DVORAK] = LAYOUT(
          KC_TAB  ,KC_QUOTE,KC_COMM,  KC_DOT,   KC_P ,   KC_Y ,                                        KC_F,   KC_G ,  KC_C ,   KC_R ,  KC_L , KC_BSPC,
          CTL_ESC , KC_A ,  KC_O   ,  KC_E  ,   KC_U ,   KC_I ,                                        KC_D,   KC_H ,  KC_T ,   KC_N ,  KC_S , CTL_MINS,
          KC_LSFT ,KC_SCLN, KC_Q   ,  KC_J  ,   KC_K ,   KC_X , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_B,   KC_M ,  KC_W ,   KC_V ,  KC_Z , KC_RSFT,
                                      ADJUST, KC_LALT, GUI_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
          ),
      #endif

      #ifdef ENABLE_COLEMAK
      /*
      * Base Layer: Colemak DH
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Bksp  |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |Ctrl/Esc|   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |Ctrl/' "|
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * | LShift |   Z  |   X  |   C  |   D  |   V  | [ {  |CapsLk|  |F-keys|  ] } |   K  |   H  | ,  < | . >  | /  ? | RShift |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |Adjust| LGUI | LAlt/| Space| Nav  |  | Sym  | Space| AltGr| RGUI | Menu |
      *                        |      |      | Enter|      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_COLEMAK_DH] = LAYOUT(
          KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
          CTL_ESC , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , CTL_QUOT,
          KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , KC_LBRC,KC_CAPS,     FKEYS  , KC_RBRC, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                      ADJUST, KC_LALT, GUI_ENT, KC_SPC , NAV   ,     SYM    , KC_SPC ,KC_RALT, KC_RGUI, KC_APP
          ),
      #endif

      /*
      * Nav Layer: Media, navigation
      * Control Command ⌥ Option ⌘ Shift
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |        | Ctrl |  Alt | GUI | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_NAV] = LAYOUT(
          _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
          _______, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
          _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          ),

      /*
      * Sym Layer: Numbers and symbols
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_SYM] = LAYOUT(
          KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
          KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
          KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LPRN, _______, _______, KC_RPRN, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          ),

      /*
      * Function Layer: Function keys
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| GUI  |  Alt | CTRL |        |
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_FUNCTION] = LAYOUT(
          _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
          _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RGUI, KC_LALT, KC_RCTL, _______,
          _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
          ),

      /*
      * Adjust Layer: Default layer settings, RGB
      *
      * ,-------------------------------------------.                              ,-------------------------------------------.
      * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
      * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
      * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
      * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        |      |      |      |      |      |  |      |      |      |      |      |
      *                        `----------------------------------'  `----------------------------------'
      */
          [_ADJUST] = LAYOUT(
          _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
          _______, _______, _______, DVORAK , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
          _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                      _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
          ),

      // /*
      //  * Layer template
      //  *
      //  * ,-------------------------------------------.                              ,-------------------------------------------.
      //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
      //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
      //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
      //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
      //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
      //  *                        |      |      |      |      |      |  |      |      |      |      |      |
      //  *                        |      |      |      |      |      |  |      |      |      |      |      |
      //  *                        `----------------------------------'  `----------------------------------'
      //  */
      //     [_LAYERINDEX] = LAYOUT(
      //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      //     ),
      };

      /* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
      * These default settings can be overriden by your own settings in your keymap.c
      * For your convenience, here's a copy of those settings so tha6t you can uncomment them if you wish to apply your own modifications.
      * DO NOT edit the rev71.c file; instead override the weakly defined default functions by your own.
      */


      #ifdef OLED_ENABLE
      oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

      bool oled_task_user(void) {
          if (is_keyboard_master()) {
              // QMK Logo and version information
              // clang-format off
              static const char PROGMEM qmk_logo[] = {
                  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
                  0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
                  0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on

    oled_write_P(qmk_logo, false);
    oled_write_P(PSTR("Kyria\nThe XOLX Mod\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("QWERTY\n"), false);
      break;
#ifdef ENABLE_DVORAK
    case _DVORAK:
      oled_write_P(PSTR("Dvorak\n"), false);
      break;
#endif
#ifdef ENABLE_COLEMAK
    case _COLEMAK_DH:
      oled_write_P(PSTR("Colemak-DH\n"), false);
      break;
#endif
    case _NAV:
      oled_write_P(PSTR("Nav\n"), false);
      break;
    case _SYM:
      oled_write_P(PSTR("Sym\n"), false);
      break;
    case _FUNCTION:
      oled_write_P(PSTR("Function\n"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("Adjust\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined\n"), false);
    }

    // Write host Keyboard LED Status to OLEDs
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "),
                 false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "),
                 false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "),
                 false);
  } else {
    // clang-format off

              // 'XolX_Productions', 120x64px
      static const  char XOLX_logo[] PROGMEM = {
      // 'XolX_Productions', 120x64px
      // 'XolX_Productions', 128x64px
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x10, 0x18, 0x70, 0x78, 0xf0, 0xf8, 0xf0, 0xf8,
      0xf0, 0xf0, 0xc0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x30,
      0x08, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x48, 0xf8, 0xf0, 0xf8, 0xf8, 0xf0,
      0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x18, 0x70, 0x78, 0xf0, 0xf8, 0xf0,
      0xf8, 0xf0, 0xf0, 0xc0, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40,
      0x10, 0x08, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x0f,
      0x3f, 0x7f, 0xff, 0xff, 0xff, 0x7c, 0xf8, 0xf0, 0xe0, 0x88, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0x80, 0xc0, 0x40, 0x40, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0xc0, 0xc0, 0x80, 0x80, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07,
      0x1f, 0x1f, 0x7f, 0xff, 0xff, 0x7f, 0xfc, 0xf8, 0xe8, 0xf0, 0x80, 0x88, 0x02, 0x01, 0x01, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
      0x40, 0x10, 0x08, 0x05, 0x07, 0x0f, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xbe, 0xf8, 0xf8, 0xe0, 0xc0,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xfc, 0xfc, 0xff, 0xff,
      0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0xff, 0xff, 0xff,
      0xfe, 0xfe, 0xf8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x80, 0x60, 0x00, 0x08, 0x05, 0x07, 0x17, 0x2f, 0x3f, 0x7f, 0xff, 0xf7, 0xfe, 0xf8, 0xf8, 0xe0,
      0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x20, 0xa0, 0x08, 0xa4, 0x02, 0xa1, 0x00,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x03, 0x27, 0x9f, 0x1f, 0x3f, 0x9f,
      0x3f, 0x9e, 0x3c, 0x98, 0x30, 0xa0, 0x80, 0x20, 0x80, 0x20, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x0f,
      0x0f, 0x1f, 0x38, 0xb0, 0x20, 0x00, 0x20, 0x40, 0x00, 0x20, 0x20, 0x94, 0x38, 0x9f, 0x0f, 0x0f,
      0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x20, 0x24, 0xbf, 0x1f, 0xbf, 0x1f, 0xbf,
      0x08, 0xa0, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x20, 0x20, 0x88, 0x24, 0x82, 0x21,
      0x80, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x21, 0x03, 0x27, 0x8f, 0x3f, 0x1f,
      0xbf, 0x1f, 0xbf, 0x1c, 0xb8, 0x30, 0xa0, 0x20, 0x80, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x55, 0x8a, 0x71, 0x8e, 0x51,
      0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xa0, 0x40, 0xb0, 0x48, 0x94, 0x6a, 0x91, 0x4e,
      0x31, 0x0a, 0x15, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x58, 0xa4, 0x4a,
      0x95, 0x72, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xea, 0x12,
      0xac, 0x52, 0xa8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xb1, 0x4e, 0x91, 0x6a, 0x95,
      0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0xdb, 0x24, 0x49,
      0xb6, 0x49, 0xb2, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xd0, 0x28, 0x44, 0xba,
      0x04, 0x73, 0x0c, 0x23, 0x0c, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x55, 0xaa, 0x14, 0xe3, 0x1c,
      0xa2, 0x08, 0x10, 0x28, 0x12, 0x6c, 0x91, 0x4e, 0x31, 0x0a, 0x04, 0x03, 0x00, 0x02, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x02, 0x0c,
      0x13, 0x0c, 0x31, 0x00, 0x20, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x20, 0x40, 0x1d, 0x20, 0x0f,
      0x10, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdb, 0x24, 0x59, 0xa6, 0x29,
      0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0xb6, 0x49, 0x92,
      0x6d, 0x92, 0xa4, 0x12, 0x00, 0x38, 0x44, 0x1a, 0xe1, 0x0e, 0x31, 0x0a, 0x05, 0x02, 0x01, 0x00,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x55, 0xaa, 0x45, 0xb8, 0x47,
      0xa8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x10, 0x00, 0x40, 0x00, 0x00,
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x91, 0x2e, 0xd1, 0x2a,
      0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x6d, 0x12, 0xe4,
      0x0b, 0x74, 0x8a, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00, 0x20, 0x00,
      0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,
      0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02,
      0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x02, 0x01, 0x00, 0x01,
      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x00, 0x01,
      0x00, 0x01, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
      0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };

    // clang-format on
    oled_write_raw_P(XOLX_logo, sizeof(XOLX_logo));
  }
  return false;
}
#endif

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t mods_state = get_mods();
  if (index == 0) {
    encoder_action_volume(clockwise);
  } else if (index == 1) { /*right encoder*/
    if (IS_LAYER_ON(_QWERTY)
#ifdef ENABLE_DVORAK
        || IS_LAYER_ON(_DVORAK)
#endif
#ifdef ENABLE_COLEMACK
        || IS_LAYER_ON(_COLEMAK)
#endif
    ) { /* mouse uo */
      if (mods_state & MOD_BIT(KC_LSFT)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        encoder_action_navpage(clockwise);
        register_mods(MOD_BIT(KC_LSFT));
      } else {
        if (clockwise) {
          tap_code(KC_MS_WH_UP);
        } else {
          tap_code(KC_MS_WH_DOWN);
        }
      }
    } else if (IS_LAYER_ON(_ADJUST)) { /* all things color */

      if (mods_state & MOD_BIT(KC_LSFT)) {
        unregister_mods(MOD_BIT(KC_LSFT));
        encoder_action_rgb_mode(clockwise);
        register_mods(MOD_BIT(KC_LSFT));

      } else if (mods_state & MOD_BIT(KC_LEFT_GUI)) {
        encoder_action_rgb_saturation(clockwise);
      } else {
        if (clockwise) {
          rgblight_decrease_hue();
        } else {
          rgblight_increase_hue();
        }
      }
    } else if (IS_LAYER_ON(_NAV)) {
      if (mods_state & MOD_BIT(KC_LSFT)) {
        encoder_action_mediatrack(clockwise);

      } else {
        encoder_action_volume(clockwise);
      }
    }
  }
  return false;
}

#endif

#if defined(RGBLIGHT_LAYERS)
const rgblight_segment_t PROGMEM my_qwerty_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
const rgblight_segment_t PROGMEM my_dvorak_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
const rgblight_segment_t PROGMEM my_colemak_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_BLUE});

const rgblight_segment_t PROGMEM my_nav_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({12, 30, HSV_GOLDENROD}, {43, 30, HSV_GOLDENROD});

const rgblight_segment_t PROGMEM my_symbols_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({12, 30, HSV_GREEN}, {43, 30, HSV_GREEN});

const rgblight_segment_t PROGMEM my_fn_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({12, 30, HSV_PINK}, {43, 30, HSV_PINK});
const rgblight_segment_t PROGMEM my_adjust_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({6, 6, HSV_MAGENTA}, {37, 6, HSV_MAGENTA});

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED}, {7, 1, HSV_RED}, {10, 3, HSV_RED}, {17, 1, HSV_RED});

const rgblight_segment_t PROGMEM my_shift_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({12, 7, HSV_BLUE}, {43, 7, HSV_BLUE});

const rgblight_segment_t PROGMEM my_ctrl_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({17, 7, HSV_ORANGE}, {48, 7, HSV_ORANGE});

const rgblight_segment_t PROGMEM my_alt_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({20, 10, HSV_TEAL}, {51, 10, HSV_TEAL});

const rgblight_segment_t PROGMEM my_gui_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({25, 8, HSV_YELLOW}, {56, 8, HSV_YELLOW});

const rgblight_segment_t PROGMEM my_capsword_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({15, 18, HSV_RED}, {46, 18, HSV_RED});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_qwerty_layer,
#ifdef ENABLE_DVORAK
    my_dvorak_layer,
#endif
#ifdef ENABLE_COLEMAK
    my_colemak_layer,
#endif
    my_nav_layer, my_symbols_layer, my_fn_layer, my_adjust_layer,
    my_capslock_layer, my_shift_layer, my_ctrl_layer, my_alt_layer,
    my_gui_layer, my_capsword_layer);

void housekeeping_task_keymap(void) {}

void caps_word_set_user(bool active) {
  // will enable/disable rgb layer 7 based on whether caps word is active
  rgblight_set_layer_state(10 + LAYER_OFFSET, active);
}
#endif

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(HSV_BLUE);
  keyboard_post_init_rgb();
#ifdef RGBLIGHT_LAYERS
  rgblight_layers = my_rgb_layers;
#else
  rgblight_sethsv_noeeprom(HSV_BLUE);
#endif
  /*debug_enable=true;*/
  /*debug_matrix=true;*/
}

// todo
// https://github.com/qmk/qmk_firmware/blob/debdc6379c7a72815df1f53e3406479381d243af/keyboards/crkbd/keymaps/soundmonster/keymap.c
// RGBRST

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
  int j = 1;
#ifdef ENABLE_DVORAK
  j++;
#endif
#ifdef ENABLE_COLEMAK
  j++;
#endif
  for (int i = j; i < __LAST; i++) {
    rgblight_set_layer_state(i, layer_state_cmp(state, i));
  }
#endif
  return state;
}

#ifdef RGBLIGHT_LAYERS
bool led_update_user(led_t led_state) {
  rgblight_set_layer_state(7, led_state.caps_lock);
  return true;
}
#endif

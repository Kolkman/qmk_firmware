
/* Copyright Olaf Kolkan (github handle: kolkman)

   Contains codefragments from qmk_firmware/users/gourdo1 that
are
   Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
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

#include "rgblight.h"
#include QMK_KEYBOARD_H
#include "kolkman.h"
void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_STARTUP_ANIMATION)
  uint16_t old_hue = 170;
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  for (uint16_t i = 255; i > 0; i--) {
    rgblight_sethsv_noeeprom((i + old_hue) % 255, 255, 255);
    matrix_scan();
    wait_ms(10);
  }
  rgblight_reload_from_eeprom();
#endif
}

__attribute__((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
#ifdef RGBLIGHT_ENABLE
  uint8_t mods = mod_config(get_mods());
  rgblight_set_layer_state(6 + LAYER_OFFSET, mods & MOD_MASK_SHIFT);
  rgblight_set_layer_state(7 + LAYER_OFFSET, mods & MOD_MASK_CTRL);
  rgblight_set_layer_state(8 + LAYER_OFFSET, mods & MOD_MASK_ALT);
  rgblight_set_layer_state(9 + LAYER_OFFSET, mods & MOD_MASK_GUI);
#endif

  housekeeping_task_keymap();
}

#ifdef ENCODER_ENABLE
    #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
        #define DYNAMIC_KEYMAP_LAYER_COUNT   //default in case this is not already defined elsewhere
    #endif
    #ifndef ENCODER_DEFAULTACTIONS_INDEX
        #define ENCODER_DEFAULTACTIONS_INDEX 0  // can select encoder index if there are multiple encoders
    #endif
static uint16_t key_timer;

void encoder_action_volume(bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLU);
    if (timer_elapsed(key_timer) < 50) {
      tap_code(KC_VOLU); // if less than 50ms have passed, hit vol up again.
      key_timer = timer_read();
    } else {
      key_timer = timer_read();
      // do nothing if 50ms or more have passed
    }
  } else {
    tap_code(KC_VOLD);
    if (timer_elapsed(key_timer) < 100) {
      tap_code(KC_VOLD); // if less than 100ms have passed, hit vol down twice.
      tap_code(KC_VOLD);
      key_timer = timer_read();
    } else {
      key_timer = timer_read();
      // do nothing if 100ms or more have passed
    }
  }
}

void encoder_action_mediatrack(bool clockwise) {
  if (clockwise)
    tap_code(KC_MEDIA_NEXT_TRACK);
  else
    tap_code(KC_MEDIA_PREV_TRACK);
}

void encoder_action_navword(bool clockwise) {
  if (clockwise)
    tap_code16(LCTL(KC_RGHT));
  else
    tap_code16(LCTL(KC_LEFT));
}

void encoder_action_linenav(bool clockwise){
  if (clockwise) {
          tap_code(KC_MS_WH_UP);
        } else {
          tap_code(KC_MS_WH_DOWN);
        }
}

void encoder_action_navpage(bool clockwise) {
  if (clockwise)
      tap_code16(KC_PGDN);
  else
    tap_code16(KC_PGUP);
}

// LAYER HANDLING
uint8_t selected_layer = 0;

uint8_t get_selected_layer(void) { return selected_layer; }

void encoder_action_layerchange(bool clockwise) {
  if (clockwise) {
    if (selected_layer < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
      selected_layer++;
      layer_move(selected_layer);
    }
  } else {
    if (selected_layer > 0) {
      selected_layer--;
      layer_move(selected_layer);
    }
  }
}

#ifdef RGB_MATRIX_ENABLE
void encoder_action_rgb_speed(bool clockwise) {
  if (clockwise)
    rgb_matrix_increase_speed_noeeprom();
  else
    rgb_matrix_decrease_speed_noeeprom();
}
void encoder_action_rgb_hue(bool clockwise) {
  if (clockwise)
    rgb_matrix_increase_hue_noeeprom();
  else
    rgb_matrix_decrease_hue_noeeprom();
}
void encoder_action_rgb_saturation(bool clockwise) {
  if (clockwise)
    rgb_matrix_increase_sat_noeeprom();
  else
    rgb_matrix_decrease_sat_noeeprom();
}
void encoder_action_rgb_brightness(bool clockwise) {
  if (clockwise)
    rgb_matrix_increase_val_noeeprom();
  else
    rgb_matrix_decrease_val_noeeprom();
}
void encoder_action_rgb_mode(bool clockwise) {
  if (clockwise)
    rgb_matrix_step_noeeprom();
  else
    rgb_matrix_step_reverse_noeeprom();
}
#elif defined(RGBLIGHT_ENABLE)
void encoder_action_rgb_speed(bool clockwise) {
  if (clockwise)
    rgblight_increase_speed_noeeprom();
  else
    rgblight_decrease_speed_noeeprom();
}
void encoder_action_rgb_hue(bool clockwise) {
  if (clockwise)
    rgblight_increase_hue_noeeprom();
  else
    rgblight_decrease_hue_noeeprom();
}
void encoder_action_rgb_saturation(bool clockwise) {
  if (clockwise)
    rgblight_increase_sat_noeeprom();
  else
    rgblight_decrease_sat_noeeprom();
}

void encoder_action_rgb_brightness(bool clockwise) {
  if (clockwise)
    rgblight_increase_val_noeeprom();
  else
    rgblight_decrease_val_noeeprom();
}
void encoder_action_rgb_mode(bool clockwise) {
  if (clockwise)
    rgblight_step_noeeprom();
  else
    rgblight_step_reverse_noeeprom();
}
#endif // RGB_MATRIX_ENABLE || RGBLIGHT_ENABLE
#endif // ENCODER_ENABLE

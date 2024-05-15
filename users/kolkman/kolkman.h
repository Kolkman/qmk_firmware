
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
enum userspace_layers {
  _QWERTY = 0,
#ifdef ENABLE_DVORAK
  _DVORAK,
#endif
#ifdef ENABLE_COLEMAK
  _COLEMAK_DH,
#endif
  _NAV,
  _SYM,
  _FUNCTION,
  _ADJUST,
  __LAST
};

#define LAYER_OFFSET 0
#if defined(ENABLE_DVORAK) || defined(ENABLE_COLEMAK)
#if defined(ENABLE_DVORAK) && defined(ENABLE_COLEMAK)
#define LAYER_OFFSET 2
#else
#define LAYER_OFFSET 1
#endif
#else
#define LAYER_OFFSET 0
#endif

void keyboard_post_init_rgb(void);

// ENCODER ACTIONS
#ifdef ENCODER_ENABLE

void encoder_action_volume(bool clockwise);
void encoder_action_mediatrack(bool clockwise);
void encoder_action_navword(bool clockwise);
void encoder_action_navpage(bool clockwise);
void encoder_action_linenav(bool clockwise);

uint8_t get_selected_layer(void);
void encoder_action_layerchange(bool clockwise);

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void encoder_action_rgb_speed(bool clockwise);
void encoder_action_rgb_hue(bool clockwise);
void encoder_action_rgb_saturation(bool clockwise);
void encoder_action_rgb_brightness(bool clockwise);
void encoder_action_rgb_mode(bool clockwise);
#endif // RGB_MATRIX_ENABLE / RGBLIGHT_ENABLE

#endif // ENCODER_ENABLE

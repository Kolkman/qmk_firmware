/* Copyright 2022 splitkb.com <support@splitkb.com>
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

#pragma once

// power lights on caps lock
#define LED_CAPS_LOCK_PIN 24
#define LED_PIN_ON_STATE 0
#define RGBLIGHT_REDEFINE_LIMIT_VAL 100

// #define ENCODER_MAP_ENABLE
// `SPLIT_HAND_PIN` can currently be defined in `info.json`,
// but can't yet be given a value
#define SPLIT_HAND_PIN B5

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define TABBING_TIMER 150
#define ENCODER_RESOLUTION 2
// #define LED_CAPS_LOCK_PIN 24
// #define LED_PIN_ON_STATE 0

// Not yet available in `info.json`
#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X64
#define SPLIT_OLED_ENABLE
#endif

// Not yet available in `info.json`
#ifdef RGBLIGHT_ENABLE
#define RBGLIGHT_LED_MAP                                                       \
  { 9, 8, 6, 7, 5, 3, 2, 4, 1, 0, 10, 12, 13, 11, 14, 16, 17, 15, 18, 19 }
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#ifndef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 150
#endif
#ifdef RGBLIGHT_REDEFINE_LIMIT_VAL
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL RGBLIGHT_REDEFINE_LIMIT_VAL
#endif
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 16
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#endif

#ifndef USERSPACE
#define USERSPACE
#pragma once
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

void my_custom_function(void);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

#define __QWERT_L1__   KC_TAB   , KC_Q        , KC_W     , KC_E      , KC_R     , KC_T
#define __QWERT_L2__   KC_LCTL  , KC_A        , KC_S     , KC_D      , KC_F     , KC_G
#define __QWERT_L3__   KC_LSFT  , KC_Z        , KC_X     , KC_C      , KC_V     , KC_B
#define __QWERT_R1__   KC_Y     , KC_U        , KC_I     , KC_O      , KC_P     , KC_BSPC
#define __QWERT_R2__   KC_H     , KC_J        , KC_K     , KC_L      , KC_SCLN  , KC_QUOT
#define __QWERT_R3__   KC_N     , KC_M        , KC_COMM  , KC_DOT    , KC_SLSH  , KC_RSFT

#define __LOWER_L1__   _______  , MY_POINTER  , MY_END   , KC_GRAVE  , KC_TILD  , _______
#define __LOWER_L2__   _______  , KC_EXLM     , KC_AT    , KC_HASH   , KC_DLR   , KC_PERC
#define __LOWER_L3__   _______  , _______     , _______  , _______   , _______  , _______
#define __LOWER_R1__   _______  , KC_EQL      , KC_PIPE  , KC_MINS   , _______  , _______
#define __LOWER_R2__   KC_CIRC  , KC_AMPR     , KC_ASTR  , KC_UNDS   , KC_PLUS  , KC_BSLASH
#define __LOWER_R3__   _______  , _______     , _______  , _______   , _______  , _______

#define __RAISE_L1__   KC_F1    , KC_F2       , KC_F3    , KC_F4     , KC_F5    , KC_F6
#define __RAISE_L2__   _______  , KC_1        , KC_2     , KC_3      , KC_4     , KC_5
#define __RAISE_L3__   _______  , _______     , _______  , _______   , _______  , _______
#define __RAISE_R1__   KC_F7    , KC_F8       , KC_F9    , KC_F10    , KC_F11   , KC_F12
#define __RAISE_R2__   KC_6     , KC_7        , KC_8     , KC_9      , KC_0     , _______
#define __RAISE_R3__   _______  , _______     , _______  , _______   , _______  , _______

#define __ADJST_L1__   RESET    , _______      , _______  , _______   , _______  , _______
#define __ADJST_L2__   RGB_TOG  , RGB_HUI     , RGB_SAI  , RGB_VAI   , XXXXXXX  , XXXXXXX
#define __ADJST_L3__   RGB_MOD  , RGB_HUD     , RGB_SAD  , RGB_VAD   , XXXXXXX  , XXXXXXX
#define __ADJST_R1__   _______  , _______     , _______  , _______   , _______  , _______
#define __ADJST_R2__   _______  , _______     , _______  , _______   , _______  , _______
#define __ADJST_R3__   _______  , _______     , _______  , _______   , _______  , _______

#define ____CRKB____   KC_LGUI  , LOWER       , KC_SPC   , KC_ENT    , RAISE    , KC_RALT


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  MY_POINTER,
  MY_COUT,
  MY_CIN,
  MY_END
};


#endif

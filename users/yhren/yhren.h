#ifndef USERSPACE
#define USERSPACE

#pragma once
#include QMK_KEYBOARD_H

#include "version.h"
#include "eeprom.h"
#include "wrapper.h"
//#include "process_records.h"
#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif  // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE)
#    include "rgb_stuff.h"
#endif
#if defined(RGB_MATRIX_ENABLE)
#    include "rgb_matrix_stuff.h"
#endif
#if defined(OLED_DRIVER_ENABLE)
#    include "oled_stuff.h"
#endif

#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

void my_custom_function(void);
bool process_record_user(uint16_t keycode, keyrecord_t *record);


enum userspace_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

enum userspace_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  MY_POINTER,
  MY_COUT,
  MY_CIN,
  MY_END
};

typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    rgb_matrix_idle_anim :1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;


#endif

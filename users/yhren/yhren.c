#include "yhren.h"

userspace_config_t userspace_config;

enum combos {
  JK_RPRN,
  JL_RBRC,
  JSCLN_RCBR,
  FD_LPRN,
  FS_LBRC,
  FA_LCBR, /* symmetric parathentis*/
  KO_UP,
  KM_DN,
  KL_LF,
  LSCLN_RT,   /* arrows */
  JF_ESC
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jscln_combo[] = {KC_J, KC_SCLN, COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM fs_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM fa_combo[] = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM ko_combo[] = {KC_K, KC_O, COMBO_END};
const uint16_t PROGMEM km_combo[] = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM lscln_combo[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM jf_combo[] = {KC_J, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [JK_RPRN]    = COMBO(jk_combo, KC_RPRN),
  [JL_RBRC]    = COMBO(jl_combo, KC_RBRC),
  [JSCLN_RCBR] = COMBO(jscln_combo, KC_RCBR),
  [FD_LPRN]    = COMBO(fd_combo, KC_LPRN),
  [FS_LBRC]    = COMBO(fs_combo, KC_LBRC),
  [FA_LCBR]    = COMBO(fa_combo, KC_LCBR),
  [KO_UP]      = COMBO(ko_combo, KC_UP),
  [KM_DN]      = COMBO(km_combo, KC_DOWN),
  [KL_LF]      = COMBO(kl_combo, KC_LEFT),
  [LSCLN_RT]   = COMBO(lscln_combo, KC_RGHT),
  [JF_ESC]     = COMBO(jf_combo, KC_ESC)
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case MY_POINTER:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
      return false;
      break;
    case MY_COUT:
      if (record->event.pressed) {
        SEND_STRING("<< ");
      }
      return false;
      break;
    case MY_CIN:
      if (record->event.pressed) {
        SEND_STRING(">> ");
      }
      return false;
      break;
    case MY_END:
      if (record->event.pressed) {
        SEND_STRING("'"SS_TAP(X_BSLASH)"n'");
      }
      return false;
      break;
  }
  return true;
}


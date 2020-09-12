#include QMK_KEYBOARD_H

#define KC_RESET RESET
#define KC_RST   KC_RESET

#define __QWERT_L1__   KC_TAB    , KC_Q       , KC_W    , KC_E     , KC_R    , KC_T
#define __QWERT_L2__   KC_LCTL   , KC_A       , KC_S    , KC_D     , KC_F    , KC_G
#define __QWERT_L3__   KC_LSFT   , KC_Z       , KC_X    , KC_C     , KC_V    , KC_B
#define __QWERT_R1__   KC_Y      , KC_U       , KC_I    , KC_O     , KC_P    , KC_BSPC
#define __QWERT_R2__   KC_H      , KC_J       , KC_K    , KC_L     , KC_SCLN , KC_QUOT
#define __QWERT_R3__   KC_N      , KC_M       , KC_COMM , KC_DOT   , KC_SLSH , KC_RSFT

#define __LOWER_L1__   KC_NO   , MY_END  , MY_SELF , KC_GRAVE , KC_TILD    , MY_POINTER
#define __LOWER_L2__   KC_TRNS , KC_EXLM , KC_AT   , KC_HASH  , KC_DLR     , KC_PERC
#define __LOWER_L3__   KC_TRNS , MY_FLSE , MY_TRUE , KC_NO    , KC_MS_BTN1 , KC_MS_BTN2
#define __LOWER_R1__   MY_COUT , KC_EQL  , KC_PIPE , KC_MINS  , MY_RTRN    , KC_DEL
#define __LOWER_R2__   KC_CIRC , KC_AMPR , KC_ASTR , KC_UNDS  , KC_PLUS    , KC_BSLASH
#define __LOWER_R3__   MY_PARA , MY_SQAR , MY_BRKT , MY_CRLY  , KC_NO      , KC_TRNS

#define __RAISE_L1__   KC_F1     , KC_F2      , KC_F3   , KC_F4    , KC_F5   , KC_F6
#define __RAISE_L2__   KC_TRNS   , KC_1       , KC_2    , KC_3     , KC_4    , KC_5
#define __RAISE_L3__   KC_TRNS   , KC_NO      , KC_NO   , KC_NO    , KC_NO   , KC_NO
#define __RAISE_R1__   KC_F7     , KC_F8      , KC_F9   , KC_F10   , KC_F11  , KC_F12
#define __RAISE_R2__   KC_6      , KC_7       , KC_8    , KC_9     , KC_0    , KC_TRNS
#define __RAISE_R3__   KC_NO     , KC_NO      , KC_TRNS , KC_TRNS  , KC_TRNS , KC_TRNS

#define __ADJST_L1__   RESET     , RGBRST     , KC_NO   , KC_NO    , KC_NO   , KC_NO
#define __ADJST_L2__   RGB_TOG   , RGB_HUI    , RGB_SAI , RGB_VAI  , KC_NO   , KC_NO
#define __ADJST_L3__   RGB_MOD   , RGB_HUD    , RGB_SAD , RGB_VAD  , KC_NO   , KC_NO
#define __ADJST_R1__   MY_HIDRAW , KC_NO      , KC_NO   , KC_NO    , KC_NO   , KC_NO
#define __ADJST_R2__   KC_NO     , KC_NO      , KC_NO   , KC_NO    , KC_NO   , KC_NO
#define __ADJST_R3__   KC_NO     , KC_NO      , KC_NO   , KC_NO    , KC_NO   , KC_NO

#define ____CRKB____   KC_LGUI   , LOWER      , KC_SPC  , KC_ENT   , RAISE   , KC_RALT

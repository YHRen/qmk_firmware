#include "yhren.h"

#define LAYOUT_crkbd_base( \
    KL1, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, KR1,\
    KL2, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, KR2,\
    KL3, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, KR3 \
  ) \
  LAYOUT_wrapper( \
    KL1 , K01 , K02 , K03 , K04 , K05 ,                         K06 , K07 , K08 , K09 , K0A , KR1 , \
    KL2 , K11 , K12 , K13 , K14 , K15 ,                         K16 , K17 , K18 , K19 , K1A , KR2 , \
    KL3 , K21 , K22 , K23 , K24 , K25 ,                         K26 , K27 , K28 , K29 , K2A , KR3 , \
                   KC_LGUI  , LOWER , KC_SPC,               KC_ENT, RAISE, KC_RALT \
  )

#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_crkbd_base_wrapper( \
            __QWERT_L1__ , __QWERT_R1__ ,  \
            __QWERT_L2__ , __QWERT_R2__ ,  \
            __QWERT_L3__ , __QWERT_R3__
            ),

    [_LOWER] = LAYOUT_crkbd_base_wrapper(\
            __LOWER_L1__ , __LOWER_R1__ ,  \
            __LOWER_L2__ , __LOWER_R2__ ,  \
            __LOWER_L3__ , __LOWER_R3__
            ),

    [_RAISE] = LAYOUT_crkbd_base_wrapper(\
            __RAISE_L1__ , __RAISE_R1__ ,  \
            __RAISE_L2__ , __RAISE_R2__ ,  \
            __RAISE_L3__ , __RAISE_R3__
            ),

    [_ADJUST] = LAYOUT_crkbd_base_wrapper( \
            __ADJST_L1__ , __ADJST_R1__ ,  \
            __ADJST_L2__ , __ADJST_R2__ ,  \
            __ADJST_L3__ , __ADJST_R3__
            )
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


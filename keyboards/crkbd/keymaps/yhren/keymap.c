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





// Set Parameters
#define ONES(x) (fmax(fmin(x, 1.0), -1.0))
#define SIGN(x) ((x > 0) - (x < 0))
//int swPin = C4; // SW
const pin_t xPin = B5;
const pin_t yPin = B4;

float x_scale = 1024.0*8;
float y_scale = 1024.0*8;
uint16_t x_dead = 20;
uint16_t y_dead = 20;
int16_t xcen, ycen;

float maxCursorSpeed = 0.9;  // holding shift
float minCursorSpeed = 0.2;
float maxScrollSpeed = 0.3;  // holding shift
float minScrollSpeed = 0.05;

int8_t xPolarity = 1;
int8_t yPolarity = -1;

uint8_t cursorTimeout = 100;
uint16_t lastCursor = 0;

float prv_xmv = 0.0;
float prv_ymv = 0.0;

void rolling_avg_move(float * perc, float * prv_mv){
    *perc = 0.95**perc + 0.05**prv_mv;
    prv_mv = perc;
}

void pointing_device_task(void) {
    if (timer_elapsed(lastCursor) < cursorTimeout) return;
    lastCursor = timer_read();

    report_mouse_t report = pointing_device_get_report();
    int16_t x = analogReadPin(xPin);
    int16_t y = analogReadPin(yPin);
    int16_t xd = x-xcen;
    int16_t yd = y-ycen;
    if ( abs(xd) > x_dead || abs(yd) > y_dead ) {
        float xperc = SIGN(xd) * ONES( (float)xd*xd / x_scale);
        float yperc = SIGN(yd) * ONES( (float)yd*yd / y_scale);
        rolling_avg_move(&xperc, &prv_xmv);
        rolling_avg_move(&yperc, &prv_ymv);
        int8_t xmove = (int8_t)(xperc * 127.0);
        int8_t ymove = (int8_t)(yperc * 127.0);

        if (get_mods() & MOD_MASK_GUI) {
            float scroll_speed = (get_mods() & MOD_MASK_SHIFT) ? maxScrollSpeed : minScrollSpeed;
            report.h = xPolarity * xmove * scroll_speed;
            report.v = xPolarity * ymove * scroll_speed;
        }else{
            float cursor_speed = (get_mods() & MOD_MASK_SHIFT) ? maxCursorSpeed : minCursorSpeed;
            report.x = xPolarity * xmove * cursor_speed;
            report.y = yPolarity * ymove * cursor_speed;
        }
    }

// if ( timer_elapsed(mouse_btn_timer) < mouse_btn_timeout){
//    if ( IS_LAYER_ON(_LOWER) ){
//        report.buttons |= MOUSE_BTN1;
//        is_ms_btn_released = false;
//    } else {
//        is_ms_btn_released = true;
//        report.buttons &= ~MOUSE_BTN1;
//    }

    // mouse click
    // if (!readPin(E6)) {
    //     report.buttons |= MOUSE_BTN1;
    // } else {
    //     report.buttons &= ~MOUSE_BTN1;
    // }
    // OR:
    // if (digitalRead(swPin) == 1) {
    //   report.buttons |= MOUSE_BTN1;
    // }

    pointing_device_set_report(report);
    pointing_device_send();
}

// void matrix_init_keymap(void) {
void keyboard_post_init_user(void) {
    // init pin? Is needed?
    // setPinInputHigh(E6);
    // Account for drift
    xcen = analogReadPin(xPin);
    ycen = analogReadPin(yPin);
}

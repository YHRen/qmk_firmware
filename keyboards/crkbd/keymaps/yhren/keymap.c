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



// analogReference( ADC_REF_POWER );  // internal 2.56V

// Joystick
// Set Pins
// const pin_t xPin = 0x00; // VRx
// const pin_t yPin = 0x01; // VRy
//int swPin = C4; // SW

// Set Parameters
uint16_t minAxisValue = 0;
uint16_t maxAxisValue = 1023;

#define DEADZ 60
#define ONES(x) (fmax(fmin(x, 1.0), -1.0))
#define SIGN(x) ((x > 0) - (x < 0))

float maxCursorSpeed = 0.5;  // holding shift
float cursorSpeed = 0.2;

int8_t xPolarity = 1;
int8_t yPolarity = -1;

uint8_t cursorTimeout = 100;

int16_t xcen, ycen;

uint16_t lastCursor = 0;

const pin_t xPin = B4; //F0;
const pin_t yPin = B5; //F1;

int16_t axisCoordinate(pin_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

// int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
//     int coordinate = axisCoordinate(pin, origin);
//     if (coordinate == 0) {
//         return 0;
//     } else {
//         float percent = (float)coordinate / 100;
//         if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
//             return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator);
//         } else {
//             return percent * maxCursorSpeed * polarity * (abs(coordinate) / speedRegulator);
//         }
//     }
// }

void pointing_device_task(void) {
    if (timer_elapsed(lastCursor) < cursorTimeout) return;
    lastCursor = timer_read();

    report_mouse_t report = pointing_device_get_report();
    int16_t x = analogReadPin(xPin);
    int16_t y = analogReadPin(yPin);
    float xd = x-xcen;
    float yd = y-ycen;
    float dist = sqrt(powf(xd, 2) * powf(yd, 2));
    if (dist > DEADZ) {
        float xperc = ONES(xd/xcen * 2);
        float yperc = ONES(yd/ycen * 2);
        int8_t xmove = (int8_t)(ONES(xperc) * 127.0);
        int8_t ymove = (int8_t)(ONES(yperc) * 127.0);
        if (get_mods() & MOD_MASK_SHIFT){
            report.x = xPolarity * xmove * maxCursorSpeed;
            report.y = yPolarity * ymove * maxCursorSpeed;
        } else {
            report.x = xPolarity * xmove * cursorSpeed;
            report.y = yPolarity * ymove * cursorSpeed;
        }
        report.h = 0;
        report.v = 0;
        //scrolltimer = 0;
    }

    //report.x   = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
    //report.y   = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
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

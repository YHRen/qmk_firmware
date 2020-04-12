#include "yhren.h"
extern uint8_t is_master;
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


// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}



#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer                        = 0;
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
void add_keylog(uint16_t keycode);
#endif




#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
    oled_write_P(PSTR("Adjst"), layer_state_is(_ADJUST));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

void render_user_status(void) {
    oled_write_P(PSTR("USER:"), false);
    oled_write_P(PSTR("Yihui"), true);
    oled_write_P(PSTR("(Ray)"), true);
    oled_write_P(PSTR(">REN<"), true);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    //render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_layer_state();
    //render_bootmagic_status();
    render_mod_status(get_mods() | get_oneshot_mods());
    render_user_status();
    //render_keylogger_status();
}
void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());

    render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif
    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}
#endif

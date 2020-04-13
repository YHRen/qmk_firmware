#include "yhren.h"

extern uint8_t is_master;

static uint32_t oled_timer = 0;


bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    }
    return true;
}


void render_default_layer_state(void) {
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
            break;
    }
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state & (1 << USB_LED_NUM_LOCK));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state & (1 << USB_LED_CAPS_LOCK));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
#ifndef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
    oled_write_P(PSTR(OLED_RENDER_MODS_SFT), (modifiers & MOD_MASK_SHIFT));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_CTL), (modifiers & MOD_MASK_CTRL));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_ALT), (modifiers & MOD_MASK_ALT));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_GUI), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NAME), false);
#ifdef OLED_DISPLAY_128X64
    if (keymap_config.swap_lctl_lgui)
#else
    oled_write_P(PSTR(" "), false);
#endif
    {
        oled_write_P(logo[1][0], false);
#ifdef OLED_DISPLAY_128X64
    } else {
#endif
        oled_write_P(logo[0][0], false);
    }
    oled_write_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), !keymap_config.no_gui);
    oled_write_P(PSTR("Magic "), false);
    if (keymap_config.swap_lctl_lgui)
#endif
    {
        oled_write_P(logo[1][1], false);
#ifdef OLED_DISPLAY_128X64
    } else {
#endif
        oled_write_P(logo[0][1], false);
    }
    oled_write_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_GRV), keymap_config.swap_grave_esc);
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_CAPS), keymap_config.swap_control_capslock);
    oled_advance_page(true);
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
#endif
}

void render_user_status(void) {
    oled_write_P(PSTR(OLED_RENDER_USER_NAME), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("  RAY"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}
// clang-format on

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    //if (timer_elapsed32(oled_timer) > 30000) {
    if (false) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}


void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}


void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    if( is_master ){
        oled_write_P(PSTR(" Ray "), false);
    }else{
        oled_write_P(PSTR(" Ren "), false);
    }
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

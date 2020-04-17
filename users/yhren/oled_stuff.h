#pragma once

#include "quantum.h"
#include "oled_driver.h"
#include "raw_hid.h" // raw_hid_send(), raw_hid_receive()
//#define SCREEN_BUFFER_LEN RAW_EPSIZE
#define SCREEN_BUFFER_LEN 32

// credits go to "soundmonster"
void render_layer_state(void);
void render_logo(void);
void render_space(void);
void render_mod_status_ctrl_shift(uint8_t modifiers);
void render_mod_status_gui_alt(uint8_t modifiers);

// HID stuff
void render_hid_bf(void);
void hid_init(void);


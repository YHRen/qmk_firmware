# ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
# 	SRC += cool_rgb_stuff.c
# endif

SRC += yhren.c
COMBO_ENABLE = yes

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += oled_stuff.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_stuff.c
    ifeq ($(strip $(INDICATOR_LIGHTS)), yes)
        OPT_DEFS += -DINDICATOR_LIGHTS
    endif
    ifeq ($(strip $(RGBLIGHT_TWINKLE)), yes)
        OPT_DEFS += -DRGBLIGHT_TWINKLE
    endif
    ifeq ($(strip $(RGBLIGHT_NOEEPROM)), yes)
        OPT_DEFS += -DRGBLIGHT_NOEEPROM
    endif
    ifeq ($(strip $(RGBLIGHT_STARTUP_ANIMATION)), yes)
        OPT_DEFS += -DRGBLIGHT_STARTUP_ANIMATION
    endif
endif
RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += rgb_matrix_stuff.c
endif

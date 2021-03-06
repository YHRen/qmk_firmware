
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE           = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE            = yes  # Mouse keys(+4700)
LOCK_KEY_ENABLE            = no  # KC_LOCK
EXTRAKEY_ENABLE            = no  # Audio control and System control(+450)
CONSOLE_ENABLE             = no  # Console for debug(+400)
COMMAND_ENABLE             = no  # Commands for debug and configuration
NKRO_ENABLE                = yes # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE           = no  # Enable keyboard backlight functionality
MIDI_ENABLE                = no  # MIDI controls
AUDIO_ENABLE               = no  # Audio output on port C6
UNICODE_ENABLE             = no  # Unicode
BLUETOOTH_ENABLE           = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE            = no  # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE          = no  # Enable one-hand typing
RGB_MATRIX_ENABLE          = WS2812
RAW_ENABLE                 = yes
OLED_DRIVER_ENABLE         = yes
HAPTIC_ENABLE              = no  #SOLENOID
SLEEP_LED_ENABLE           = no  # Breathing sleep LED during USB suspend
JOYSTICK_ENABLE            = yes
BOOTLOADER = qmk-dfu
#BOOTLOADER = avrdude   # Micro Pro

Link_Time_Optimization = yes
EXTRAFLAGS += -flto

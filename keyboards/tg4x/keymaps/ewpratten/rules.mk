# Override the default bootloader since I am using a non-standard MCU
BOOTLOADER = qmk-dfu

# Enable bootloader keys
BOOTMAGIC_ENABLE = yes

# Enable Unicode
UNICODE_COMMON = yes
UNICODE_ENABLE = yes

# Enable RGB lighting
RGBLIGHT_ENABLE = yes

# Enable OS detection (used to swap Ctrl/GUI on macOS)
OS_DETECTION_ENABLE = yes

# Enable mousekeys (used for MOUSE layer hjkl navigation)
MOUSEKEY_ENABLE = yes

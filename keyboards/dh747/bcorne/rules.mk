BOARD = GENERIC_STM32_F401XC
KEYBOARD_SHARED_EP = yes

# The PlumBL bootloader takes UF2 images and is entered through bootloader_jump()
FIRMWARE_FORMAT = uf2
UF2_FAMILY = 0xabcdf401
MCU_LDSCRIPT = QF_STM32F401

SERIAL_DRIVER = usart

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
OPT_DEFS += -DQMK_MCU_STM32F401
# Places the emulated EEPROM in the last 16k page below the application
OPT_DEFS += -DBOOTLOADER_TINYUF2
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy

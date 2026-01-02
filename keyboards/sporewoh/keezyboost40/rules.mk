VIA_ENABLE = no

BOOTLOADER = rp2040

SRC += kicub.qgf.c
SRC += iosevka11.qff.c
SRC += robotomono20.qff.c

QUANTUM_PAINTER_DRIVERS += st7789_spi
QUANTUM_PAINTER_DISPLAY_TIMEOUT = 0

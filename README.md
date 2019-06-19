Quick and dirty configuration loader for an lboard2 https://github.com/electrodyssey/lboard2
Bitstream file is stored inside the microcontrollers flash.
STM32F401RET has enough memory to store both the MCU program and a bitstream.

Bitstream part is defined inside the linker script as following:
DATA (xrw)      : ORIGIN = 0x8020000, LENGTH = 384K

FPGA configuration is performed via a Slave-Serial protocol described in a Xilinx UG380 document.
This loader reads the bitstream from a DATA section at 0x8020000 and sends it bit-by-bit to an FPGA chip.

For now the bin image file is uploaded over a usb dfu protocol.
To upload the image, set the middle pin of JP1 (boot0) to +3.3v, cold boot the board and it will appear as a dfu device on the usb bus.
Creating the image from a bin file is described in dfuimg/README.txt. Set the boot0 jumper back to the ground once the firmware upload is finished.

CDCD913 clock configuration is hardcoded into the cdce913_i2c.c: CDCE913_CONFIG_INIT array.
CDCD913 config was created with a  TI Clock Pro 1.2.1 software and is transfered on a clock chip during the bootup over the i2c bus.

This loader is incomplete and lacks features, but it gets the FPGA configured.

You could upload this firmware into the MCU by using the dfu protocol as well, but use the address 0x8000000 instead.


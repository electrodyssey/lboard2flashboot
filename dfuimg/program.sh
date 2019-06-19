#!/bin/sh

# prepends the bitstream length  to the actual bitfile and then downloads the resulting image to mcu with dfu-util
#
#


dfuimg/dfuimg --input-file /home/xxx/prj/hw/xilinx_ise/myproj/myproj.bin --output-file myproj.img

dfu-util --device 0483:df11 --alt 0 --download myproj.img --dfuse-address 0x08020000


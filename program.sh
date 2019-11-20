#!/bin/sh


dfuimg/dfuimg --input-file /home/nazim/prj/hw/xilinx_ise/leolizer/leolizer.bin --output-file leolizer3.img

dfu-util --device 0483:df11 --alt 0 --download leolizer3.img --dfuse-address 0x08020000


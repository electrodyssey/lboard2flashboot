dfuimg is a quick utility which prepends the bitstream size in a low endian (4 bytes unsigned) to a bistream bin file and copies it to a new binary

resultin binary image structure:
XXXX | YYYYYYYYYYYYYYYYYYYY
0..3   5 ....


XXXX - (bytes 0..3) unsigned uint32_t low endian - size of the bitstream
YYYYYYYYYYYYYYYYYYYY - remaining bytes - bitstream binary


usage:
➜  lb2flashboot dfuimg/dfuimg --input-file gen.bin 
input file: 'gen.bin'
output file: 'gen.bin.img'
'gen.bin' size:340604 bytes
'gen.bin' size:5327C bytes
'gen.bin' little endian size:7C320500 

would generate a resulting binary image gen.bin.img which is ready to upload into the mcu's flash with a dfu-util at address 0x08020000:

dfu-util --device 0483:df11 --alt 0 --download gen.bin.img --dfuse-address 0x08020000 

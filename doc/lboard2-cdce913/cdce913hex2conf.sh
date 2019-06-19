#!/bin/bash

#script accepts a single argument - hex output from ti clock pro for cdce913

echo "static uint8_t CDCE913_CONFIG_INIT [] ="
echo "{"

cut -c 10- $1 | cut -c -2 | sed -e 's/$/,/'  -e 's/^/\t0x/' | head -32

echo "};"


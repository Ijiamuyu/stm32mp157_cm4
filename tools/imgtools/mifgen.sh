#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Help: mif generator for Verisilion ASIC. Not a standard MIF format"
    echo "usage: 'mifgen -[flash|rom] infile', output name is infile.mif for rom or infile.hex for flash"
    exit 0
fi

type=${1}
file=${2}

rm -rf bitdigits
if [ "x${type}" = x"-flash" ]; then
xxd -c1 -g1 -o 0x2000 $file > bitdigits
awk '{print $1,$2}' bitdigits > $file.mif
fi

if [ "x${type}" = x"-rom" ]; then
xxd -b -c 4 -g 1 $file > bitdigits
awk '{print $5 $4 $3 $2}' bitdigits > $file.mif
fi
rm -rf bitdigits


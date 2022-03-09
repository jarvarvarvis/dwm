#!/bin/bash
# Make dwm
make clean install

# Make dwmsb
cd dwmsb

# Check if a battery was found
DWMSB_MODULES="-DMODULE_DATE"

upower -e | grep 'BAT'
if [ $? -eq 0 ]; then
	echo "Battery was found"
	DWMSB_MODULES+=" -DMODULE_BATTERY"
else
	echo "No battery was found"
fi

echo "dwmsb Modules: ${DWMSB_MODULES}"

export DWMSB_MODULES; make clean install

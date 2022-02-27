#!/bin/sh
# Remove dmenu_dpath and dmenu_drun from bin folder
rm /usr/bin/dmenu_dpath
rm /usr/bin/dmenu_drun

# Make dwm
make clean uninstall

# Make dwmsb
cd dwmsb
make clean uninstall

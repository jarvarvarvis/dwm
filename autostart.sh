#!/bin/bash

# Start feh (desktop wallpaper)
feh --bg-scale ~/dwm/wallpaper.png

# Set X keyboard map to a German layout
setxkbmap de

# Start picom
picom --config ~/dwm/picom.conf &

# Start .desktop files in ~/.config/autostart/
# This code depends on the program dex - if you use Arch, just sudo pacman -S dex
for file in ~/.config/autostart/*; do
	dex $file &
done

# Kill previous instances of dwmsb and then start it again
killall dwmsb
./dwmsb/dwmsb &

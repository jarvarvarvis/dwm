#!/bin/sh

# Start feh (desktop wallpaper)
feh --bg-scale ~/dwm/wallpaper.png

# Set X keyboard map to a German layout
setxkbmap de

# Start picom
picom --config ~/dwm/picom.conf &

# Start dwmsb
./dwmsb/dwmsb &

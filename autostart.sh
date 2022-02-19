#!/bin/sh

# Start feh (desktop wallpaper)
feh --bg-scale ~/dwm/wallpaper.png

# Set X keyboard map to a German layout
setxkbmap de

# Start custom dwm status bar process with 5 second delay
./dwmsb -d 5 &

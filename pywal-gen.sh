#!/bin/sh
# Generate the colors-wal-dwm.h header file in .cache/wal from the supplied wallpaper
wal -i wallpaper.png -n
cp ~/.cache/wal/colors-wal-dwm.h .

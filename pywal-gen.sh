#!/bin/sh
# Generate the colors-wal-dwm.h header file in .cache/wal from the supplied wallpaper
wal --theme base16-tomorrow-night
cp ~/.cache/wal/colors-wal-dwm.h .

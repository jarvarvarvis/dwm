#!/bin/bash

# Start feh (desktop wallpaper)
feh --bg-scale ~/dwm/wallpaper.png

# Set X keyboard map to a German layout
setxkbmap de

# Start picom
picom --config ~/dwm/picom.conf &

# Start .desktop files in ~/.config/autostart/
# This code depends on the program dex - the package is called "dex" (on most distros)
if which dex &> /dev/null; then
	for file in ~/.config/autostart/*; do
		dex $file &
	done
fi

# Start the greenclip daemon, if it was found.
# This code depends on the program greenclip - the AUR package is called "rofi-greenclip"
# Alternatively, you can clone the Git repository https://github.com/erebe/greenclip
if which greenclip &> /dev/null; then
	killall greenclip
	greenclip daemon &
fi

# Start dunst, if it was found.
# This code depends on the program dunst - the package is called "dunst" (on most distros)
if which dunst &> /dev/null; then
	killall dunst
	dunst &
fi

# Start xss-lock
LOCK_COMMAND="env XSECURELOCK_PASSWORD_PROMPT=asterisks XSECURELOCK_COMPOSITE_OBSCURER=0 XSECURELOCK_SHOW_DATETIME=1 xsecurelock"
xss-lock $LOCK_COMMAND &

# Kill previous instances of dwmsb and then start it again
killall dwmsb
./dwmsb/dwmsb &

dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards, run the following command in your terminal if you want to use pywal:
```sh
sh pywal-gen.sh && sudo sh install.sh
```
If you don't want to use pywal, comment out `-DUSE_PYWAL_COLORS=1` in config.mk and
run the following command:
```sh
sudo sh install.sh
```
If you wish to uninstall dwm, run the uninstall.sh script.


Running dwm
-----------
A .desktop file is copied to /usr/share/xsessions when installing dwm.
This makes it available in your display manager.

If you don't use a display manager, add the following line to your 
.xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

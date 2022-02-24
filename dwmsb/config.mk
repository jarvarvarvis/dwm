# dwmsb version
VERSION = 0.1

# Customize below to fit your system

# Paths
PREFIX = /usr/local

# Flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${CPPFLAGS}
LDFLAGS  = 

# Compiler and Linker
CC = cc

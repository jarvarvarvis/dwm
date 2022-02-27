# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	chmod +x dmenu_drun
	chmod +x dmenu_dpath
	cp dmenu_dpath ${DESTDIR}${PREFIX}/bin/dmenu_dpath
	cp dmenu_drun ${DESTDIR}${PREFIX}/bin/dmenu_drun
	chmod +x autostart.sh
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	cp dwm.desktop /usr/share/xsessions/
	if [ ! -d /usr/share/dwm/ ]; then mkdir /usr/share/dwm/; fi
	cp help.md /usr/share/dwm/

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
	      ${DESTDIR}${PREFIX}/bin/dmenu_drun\
	      ${DESTDIR}${PREFIX}/bin/dmenu_dpath\
	      ${DESTDIR}${MANPREFIX}/man1/dwm.1\
	rm -rf /usr/share/dwm/
	rm /usr/share/xsessions/dwm.desktop

.PHONY: all options clean dist install uninstall

#!/bin/sh

if [ ! -f glib-2.22.5.tar.bz2 ] ; then
	echo Downloading GLib
	wget http://ftp.gnome.org/pub/gnome/sources/glib/2.22/glib-2.22.5.tar.bz2
fi

rm -rf build/glib
mkdir -p build/glib

echo Extracting GLib

tar xjf glib-2.22.5.tar.bz2  --strip-components=1 -C build/glib

cp -v glibconfig.h build/glib
cp -v config-js.h build/glib

cd build/glib && patch -p1 < ../../glib-2.22-emscripten.diff



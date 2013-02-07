#!/bin/sh

. ./00-build-vars.sh

if [ ! -f glib-2.22.5.tar.bz2 ] ; then
	echo Downloading GLib
	wget http://ftp.gnome.org/pub/gnome/sources/glib/2.22/glib-2.22.5.tar.bz2
fi

rm -rf $BUILD/glib
mkdir -p $BUILD/glib

echo Extracting GLib

tar xjf glib-2.22.5.tar.bz2  --strip-components=1 -C $BUILD/glib

cd $BUILD/glib
patch -p1 < ../../glib-2.22-emscripten.diff
cd ..
cd ..

if test "$NATIVE_BUILD" != "1" ; then
	cp -v glibconfig.h $BUILD/glib
	cp -v config-js.h $BUILD/glib
else
	cd $BUILD/glib && ./configure
fi



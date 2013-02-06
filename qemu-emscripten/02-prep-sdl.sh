#!/bin/sh

if [ ! -f SDL-1.2.15.tar.gz ] ; then
	echo Downloading libSDL
	wget http://www.libsdl.org/release/SDL-1.2.15.tar.gz
fi

rm -rf build/sdl
mkdir -p build/sdl

echo Extracting libSDL
tar xf SDL-1.2.15.tar.gz --strip-components=1 -C build/sdl
cp SDL_config.h build/sdl/include


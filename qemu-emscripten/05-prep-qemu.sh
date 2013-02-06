#!/bin/sh

cp -v glib.c build/
cp -v pixman*.c build/

mkdir -p build/pixman/pixman
cp -v pixman*.h build/pixman/pixman


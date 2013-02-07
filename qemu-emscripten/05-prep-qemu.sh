#!/bin/sh

. ./00-build-vars.sh

cp -v glib.c $BASEDIR
cp -v pixman*.c $BASEDIR

mkdir -p $BUILD/pixman/pixman
cp -v pixman*.h $BUILD/pixman/pixman


#!/bin/sh

cd .. && git submodule update --init pixman

cd pixman
./autogen.sh
make distclean


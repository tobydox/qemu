#!/bin/sh

. ./00-build-vars.sh

cd $BUILD

if test "$NATIVE_BUILD" != "1" ; then

	$BASEDIR/configure --cc=clang --extra-cflags="-DEMSCRIPTEN -DEMSCRIPTEN_JS -O2 -m32 -emit-llvm  -nostdinc -isystem $EMSCRIPTEN/system/include -isystem $EMSCRIPTEN//system/include/libc -isystem $EMSCRIPTEN/system/include/bsd -isystem $EMSCRIPTEN/system/include/net -isystem $EMSCRIPTEN/system/include/SDL -I$BUILD/glib -I$BUILD/glib/glib -I$BASEDIR/pixman -I$BASEDIR/pixman/pixman -I$BUILD/pixman/ -I$BUILD/pixman/pixman" --disable-zlib-test --target-list=$TARGET --enable-sdl --static --disable-vhost-net --disable-guest-agent --enable-system --audio-drv-list= --disable-kvm --disable-vnc --disable-slirp --disable-usb-redir --audio-card-list= --without-system-pixman --disable-guest-base --disable-nptl --disable-tools --disable-curses --disable-bluez --disable-xen --disable-fdt --disable-user --disable-linux-user --disable-pie --disable-uuid --disable-vde --disable-linux-aio --disable-cap-ng --disable-attr --disable-spice --disable-libiscsi --disable-smartcard-nss  --disable-usb-redir --disable-seccomp --enable-tcg-interpreter --cpu=emscripten --disable-werror

	cd pixman && $EMSCRIPTEN/emconfigure $BASEDIR/pixman/configure --disable-mmx --disable-sse2 --disable-vmx --disable-arm-simd --disable-arm-neon && cd ..

else

	$BASEDIR/configure --extra-cflags="-DEMSCRIPTEN -O2 -I/usr/include/SDL -I$BUILD/glib -I$BUILD/glib/glib -I$BASEDIR/pixman -I$BASEDIR/pixman/pixman -I$BUILD/pixman/ -I$BUILD/pixman/pixman" --disable-zlib-test --target-list=$TARGET --enable-sdl --static --disable-vhost-net --disable-guest-agent --enable-system --audio-drv-list= --disable-kvm --disable-vnc --disable-slirp --disable-usb-redir --audio-card-list= --without-system-pixman --disable-guest-base --disable-nptl --disable-tools --disable-curses --disable-bluez --disable-xen --disable-fdt --disable-user --disable-linux-user --disable-pie --disable-uuid --disable-vde --disable-linux-aio --disable-cap-ng --disable-attr --disable-spice --disable-libiscsi --disable-smartcard-nss  --disable-usb-redir --disable-seccomp --enable-tcg-interpreter --cpu=emscripten --disable-werror

	cd pixman && $BASEDIR/pixman/configure --disable-mmx --disable-sse2 --disable-vmx --disable-arm-simd --disable-arm-neon && cd ..
fi

make -j4 $TARGET
cd $TARGET
make config-target.h
cp config-target.h ..
cd ..



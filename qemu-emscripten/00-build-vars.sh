if test "$NATIVE_BUILD" = "1" ; then
	BUILD=$PWD/build-native
else
	BUILD=$PWD/build
fi


BASEDIR=$PWD/..
EMSCRIPTEN=$BASEDIR/emscripten
TARGET=i386-softmmu


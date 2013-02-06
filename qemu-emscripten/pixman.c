#define HAVE_CONFIG_H
#define PIXMAN_NO_TLS

#include <pixman/config.h>

#include "pixman/pixman-image.c"
#include "pixman/pixman-edge.c"
#undef READ

#include "pixman/pixman-access.c"

#include "pixman/pixman.c"
#include "pixman/pixman-matrix.c"
#include "pixman/pixman-cpu.c"
#include "pixman/pixman-utils.c"
#include "pixman/pixman-bits-image.c"
#include "pixman/pixman-implementation.c"
#include "pixman/pixman-general.c"
#include "pixman/pixman-region16.c"

#define repeat(x,y,z) repeat2(x,y,z)

#include "pixman/pixman-fast-path.c"



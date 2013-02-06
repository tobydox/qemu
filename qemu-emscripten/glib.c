#define G_LOG_DOMAIN "GLib"
#define G_DISABLE_CAST_CHECKS
#define GLIB_COMPILATION
#define PCRE_STATIC
#define G_DISABLE_SINGLE_INCLUDES
#define DISABLE_VISIBILITY
#define G_STDIO_NO_WRAP_ON_UNIX

#ifdef EMSCRIPTEN_JS
#include <glib/config-js.h>
#else
#include <glib/config.h>
#endif

#include "gmem.h"
#include "gmem.c"
#include "gqueue.c"
#include "ghash.c"
#include "gstrfuncs.c"
#include "gslice.c"
#include "gmessages.c"
#include "gutils.c"
#include "gstring.c"
#include "glist.c"
#include "gslist.c"
#include "gprintf.c"
#include "gthread.c"
#include "gatomic.c"
#include "gmain.c"
#include "gfileutils.c"
#include "gtimer.c"
#include "gerror.c"
#include "garray.c"
#include "gconvert.c"
#include "gutf8.c"
#include "gpoll.c"
#include "gdataset.c"
#include "grand.c"
#include "gstdio.c"
#include "gpattern.c"
#include "gqsort.c"
#include "gbase64.c"

//#include "gthread/gthread-impl.c"

#include "gtestutils.c"

#define LIBDIR "/"
#include "libcharset/localcharset.c"


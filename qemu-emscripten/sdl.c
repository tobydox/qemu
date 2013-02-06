#ifndef EMSCRIPTEN_JS

#include "sdl/include/SDL_config_emscripten.h"

#include "sdl/include/SDL_syswm.h"
#include "sdl/src/file/SDL_rwops.c"
#include "sdl/src/video/SDL_blit_0.c"
#include "sdl/src/video/SDL_blit_N.c"
#include "sdl/src/video/SDL_blit_1.c"
#include "sdl/src/video/SDL_blit_A.c"
#include "sdl/src/video/SDL_blit.c"

#undef BLEND16_50

#include "sdl/src/video/SDL_bmp.c"
#include "sdl/src/video/SDL_gamma.c"
#include "sdl/src/video/SDL_video.c"
#include "sdl/src/video/SDL_surface.c"
#include "sdl/src/video/SDL_cursor.c"
#include "sdl/src/video/SDL_RLEaccel.c"
#include "sdl/src/video/SDL_pixels.c"
#include "sdl/src/events/SDL_active.c"
#include "sdl/src/events/SDL_events.c"
#include "sdl/src/events/SDL_expose.c"
#include "sdl/src/events/SDL_mouse.c"
#include "sdl/src/events/SDL_keyboard.c"
#include "sdl/src/events/SDL_quit.c"
#include "sdl/src/events/SDL_resize.c"
#include "sdl/src/SDL.c"
#include "sdl/src/SDL_fatal.c"
#include "sdl/src/SDL_error.c"
#include "sdl/src/stdlib/SDL_string.c"
#include "sdl/src/stdlib/SDL_iconv.c"

#include "sdl/src/thread/SDL_thread.c"
#include "sdl/src/thread/pthread/SDL_sysmutex.c"
#include "sdl/src/thread/pthread/SDL_syssem.c"
#include "sdl/src/thread/pthread/SDL_systhread.c"

#include "sdl/src/timer/unix/SDL_systimer.c"
#include "sdl/src/timer/SDL_timer.c"

#define bootstrap audio_bootstrap
#include "sdl/src/audio/dummy/SDL_dummyaudio.c"
#undef _THIS

#include "sdl/src/video/x11/SDL_x11wm.c"
#include "sdl/src/video/x11/SDL_x11modes.c"
#include "sdl/src/video/x11/SDL_x11mouse.c"
#include "sdl/src/video/x11/SDL_x11events.c"
#include "sdl/src/video/x11/SDL_x11video.c"
#include "sdl/src/video/x11/SDL_x11dyn.c"
//#include "sdl/src/video/x11/SDL_x11dga.c"
#include "sdl/src/video/x11/SDL_x11image.c"
#include "sdl/src/video/x11/SDL_x11gamma.c"
#include "sdl/src/video/x11/SDL_x11gl.c"
//#include "sdl/src/video/Xext/Xxf86dga/XF86DGA.c"
//#include "sdl/src/video/Xext/Xxf86dga/XF86VMode.c"

//#include "sdl/src/video/dga/SDL_dgavideo.c"
#include "sdl/src/audio/SDL_audio.c"
#include "sdl/src/audio/SDL_audiocvt.c"

SDL_bool SDL_HasMMX(void)

{
	return 0;
}


#endif

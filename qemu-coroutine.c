/*
 * QEMU coroutines
 *
 * Copyright IBM, Corp. 2011
 *
 * Authors:
 *  Stefan Hajnoczi    <stefanha@linux.vnet.ibm.com>
 *  Kevin Wolf         <kwolf@redhat.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2 or later.
 * See the COPYING.LIB file in the top-level directory.
 *
 */

#include "trace.h"
#include "qemu-common.h"
#include "block/coroutine.h"
#include "block/coroutine_int.h"

static Coroutine* currentCORO = NULL;


Coroutine *qemu_coroutine_create(CoroutineEntry *entry)
{
	Coroutine* coro = malloc(sizeof(Coroutine));
    coro->entry = entry;

    return coro;
}

Coroutine *qemu_coroutine_self()
{
    return currentCORO;

}


void qemu_coroutine_enter(Coroutine *co, void *opaque)
{
	if( co && co->entry)
	{
		Coroutine* tmp = currentCORO;

		currentCORO = co;
		co->entry(opaque);

		free(co);

		currentCORO = tmp;
	}
}


bool qemu_in_coroutine(void)
{
	return currentCORO != NULL;
}

#ifndef qemu_coroutine_yield
void coroutine_fn qemu_coroutine_yield(void)
{
}
#endif


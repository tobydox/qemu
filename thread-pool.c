/*
 * QEMU block layer thread pool
 *
 * Copyright IBM, Corp. 2008
 * Copyright Red Hat, Inc. 2012
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *  Paolo Bonzini     <pbonzini@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Contributions after 2012-01-13 are licensed under the terms of the
 * GNU GPL, version 2 or (at your option) any later version.
 */
#include "qemu-common.h"
#include "qemu/queue.h"
#include "qemu/thread.h"
#include "qemu/osdep.h"
#include "block/coroutine.h"
#include "block/block_int.h"
#include "block/thread-pool.h"


typedef struct ThreadPoolElement ThreadPoolElement;

enum ThreadState {
    THREAD_QUEUED,
    THREAD_ACTIVE,
    THREAD_DONE,
    THREAD_CANCELED,
};

struct ThreadPoolElement {
    BlockDriverAIOCB common;
    ThreadPoolFunc *func;
    void *arg;

    /* Moving state out of THREAD_QUEUED is protected by lock.  After
     * that, only the worker thread can write to it.  Reads and writes
     * of state and ret are ordered with memory barriers.
     */
    enum ThreadState state;
    int ret;

    /* Access to this list is protected by lock.  */
    QTAILQ_ENTRY(ThreadPoolElement) reqs;

    /* Access to this list is protected by the global mutex.  */
    QLIST_ENTRY(ThreadPoolElement) all;
};

static EventNotifier notifier;

/* The following variables are protected by the global mutex.  */
static QLIST_HEAD(, ThreadPoolElement) head;

/* The following variables are protected by lock.  */
static QTAILQ_HEAD(, ThreadPoolElement) request_list;


static void event_notifier_ready(EventNotifier *notifier)
{
    ThreadPoolElement *elem, *next;

    event_notifier_test_and_clear(notifier);

restart:
    QLIST_FOREACH_SAFE(elem, &head, all, next)
	{
		QLIST_REMOVE(elem, all);
		qemu_aio_release(elem);
    }
}

static void thread_pool_cancel(BlockDriverAIOCB *acb)
{
fprintf(stderr, "thread_pool_cancel\n");
    ThreadPoolElement *elem = (ThreadPoolElement *)acb;

	QTAILQ_REMOVE(&request_list, elem, reqs);
	elem->state = THREAD_CANCELED;
	event_notifier_set(&notifier);
}

static const AIOCBInfo thread_pool_aiocb_info = {
    .aiocb_size         = sizeof(ThreadPoolElement),
    .cancel             = thread_pool_cancel,
};

static int thread_pool_active(EventNotifier *notifier)
{
    return true;
}


BlockDriverAIOCB *thread_pool_submit_aio(ThreadPoolFunc *func, void *arg,
        BlockDriverCompletionFunc *cb, void *opaque)
{
    ThreadPoolElement *req;

    req = qemu_aio_get(&thread_pool_aiocb_info, NULL, cb, opaque);
    req->func = func;
    req->arg = arg;

    req->ret = req->func(req->arg);

        if (req->common.cb) {
            /* Read state before ret.  */
            req->common.cb(req->common.opaque, req->ret);
		}

	req->state = THREAD_DONE;

    QLIST_INSERT_HEAD(&head, req, all);

    QTAILQ_INSERT_TAIL(&request_list, req, reqs);

	event_notifier_set(&notifier);

    return &req->common;
}


static void thread_pool_init(void)
{
    QLIST_INIT(&head);

    event_notifier_init(&notifier, false);

  qemu_aio_set_event_notifier(&notifier, event_notifier_ready,
                                thread_pool_active);

    QTAILQ_INIT(&request_list);
}


block_init(thread_pool_init)

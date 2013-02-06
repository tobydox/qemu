/*
 * Wrappers around mutex/cond/thread functions
 *
 * Copyright Red Hat, Inc. 2009
 *
 * Author:
 *  Marcelo Tosatti <mtosatti@redhat.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include "qemu/thread.h"

static void error_exit(int err, const char *msg)
{
    fprintf(stderr, "qemu: %s: %s\n", msg, strerror(err));
    abort();
}

void qemu_mutex_init(QemuMutex *mutex)
{
}

void qemu_mutex_destroy(QemuMutex *mutex)
{
}

void qemu_mutex_lock(QemuMutex *mutex)
{
}

int qemu_mutex_trylock(QemuMutex *mutex)
{
    return 0;
}

void qemu_mutex_unlock(QemuMutex *mutex)
{
}

void qemu_cond_init(QemuCond *cond)
{
}

void qemu_cond_destroy(QemuCond *cond)
{
}

void qemu_cond_signal(QemuCond *cond)
{
}

void qemu_cond_broadcast(QemuCond *cond)
{
}

void qemu_cond_wait(QemuCond *cond, QemuMutex *mutex)
{
}

void qemu_sem_init(QemuSemaphore *sem, int init)
{
}

void qemu_sem_destroy(QemuSemaphore *sem)
{
}

void qemu_sem_post(QemuSemaphore *sem)
{
}

static void compute_abs_deadline(struct timespec *ts, int ms)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts->tv_nsec = tv.tv_usec * 1000 + (ms % 1000) * 1000000;
    ts->tv_sec = tv.tv_sec + ms / 1000;
    if (ts->tv_nsec >= 1000000000) {
        ts->tv_sec++;
        ts->tv_nsec -= 1000000000;
    }
}

int qemu_sem_timedwait(QemuSemaphore *sem, int ms)
{
}

void qemu_sem_wait(QemuSemaphore *sem)
{
}

void qemu_thread_create(QemuThread *thread,
                       void *(*start_routine)(void*),
                       void *arg, int mode)
{
}

void qemu_thread_get_self(QemuThread *thread)
{
    thread->thread = pthread_self();
}

bool qemu_thread_is_self(QemuThread *thread)
{
   return true;
}

void qemu_thread_exit(void *retval)
{
}

void *qemu_thread_join(QemuThread *thread)
{
    return 0;
}

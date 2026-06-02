/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

/* macOS libc / kernel-API gaps. This header is force-included into every
 * translation unit on Darwin (see meson.build), so the shims below are
 * available everywhere without per-file includes. */

#ifdef __APPLE__

#include <limits.h>

/* Linux-only socket()/recvmsg() flags; emulated via fcntl() at the call site. */
#ifndef SOCK_CLOEXEC
#define SOCK_CLOEXEC 0
#endif
#ifndef SOCK_NONBLOCK
#define SOCK_NONBLOCK 0
#endif
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif
#ifndef MSG_CMSG_CLOEXEC
#define MSG_CMSG_CLOEXEC 0
#endif

/* errno values missing on macOS (ENODATA already exists there). */
#ifndef ENOMEDIUM
#define ENOMEDIUM       (INT_MAX - 1)
#endif
#ifndef ENOPKG
#define ENOPKG          (INT_MAX - 2)
#endif
#ifndef EUNATCH
#define EUNATCH         (INT_MAX - 3)
#endif
#ifndef ELNRNG
#define ELNRNG          (INT_MAX - 5)
#endif

/* memrchr() is a GNU extension not available on macOS. */
#include <string.h>
static inline void *memrchr(const void *m, int c, size_t n) {
        const unsigned char *s = (const unsigned char *) m;
        while (n-- > 0)
                if (s[n] == (unsigned char) c)
                        return (void *) (s + n);
        return NULL;
}

/* ppoll() is Linux/glibc; emulate via poll() (callers pass a NULL sigmask). */
#include <poll.h>
#include <signal.h>
#include <time.h>
static inline int ppoll(struct pollfd *fds, nfds_t nfds,
                        const struct timespec *timeout_ts, const sigset_t *sigmask) {
        (void) sigmask;
        int timeout_ms = -1;
        if (timeout_ts)
                timeout_ms = (int) (timeout_ts->tv_sec * 1000 + timeout_ts->tv_nsec / 1000000);
        return poll(fds, nfds, timeout_ms);
}

#endif /* __APPLE__ */

/* Copyright (c) 2013-2015, Drew Thoreson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_

#include <telos/types.h>

/*
 * What follows is a whole bunch of junk from newlib's <sys/types.h>, much of
 * which may not be required.
 */
#include <sys/_types.h>
#include <sys/_stdint.h>
#include <machine/types.h>

#ifndef _POSIX_SOURCE
#ifndef _BSD_TYPES_DEFINED
#ifndef __u_char_defined
typedef	unsigned char u_char;
#define __u_char_defined
#endif
#ifndef __u_short_defined
typedef	unsigned short u_short;
#define __u_short_defined
#endif
#ifndef __u_int_defined
typedef	unsigned int u_int;
#define __u_int_defined
#endif
#ifndef __u_long_defined
typedef	unsigned long u_long;
#define __u_long_defined
#endif
#define _BSD_TYPES_DEFINED
#endif

/* System V compatibility */
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

#ifndef __daddr_t_defined
typedef	long daddr_t;
#define __daddr_t_defined
#endif
#ifndef __caddr_t_defined
typedef	char *caddr_t;
#define __caddr_t_defined
#endif

/*
 * We don't define fd_set and friends if we are compiling POSIX source.
 */
#define _SYS_TYPES_FD_SET
#define	NBBY 8 /* number of bits in a byte */

/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#ifndef	FD_SETSIZE
#define	FD_SETSIZE 64
#endif

typedef	long fd_mask;
#define	NFDBITS	(sizeof (fd_mask) * NBBY) /* bits per mask */
#ifndef	howmany
#define	howmany(x,y) (((x)+((y)-1))/(y))
#endif

/* We use a macro for fd_set so that including Sockets.h afterwards
   can work.  */
typedef	struct _types_fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} _types_fd_set;

#define fd_set _types_fd_set

#define	FD_SET(n, p)   ((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#define	FD_CLR(n, p)   ((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#define	FD_ISSET(n, p) ((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#define	FD_ZERO(p)     (__extension__ (void)({ \
	size_t __i; \
	char *__tmp = (char *)p; \
	for (__i = 0; __i < sizeof (*(p)); ++__i) \
		*__tmp++ = 0; \
}))

# endif	/* !_POSIX_SOURCE */

typedef _USECONDS_T_TYPE useconds_t;

#ifndef _SUSECONDS_T_DECLARED
typedef __suseconds_t suseconds_t;
#define _SUSECONDS_T_DECLARED
#endif

typedef __int64_t sbintime_t;

#include <sys/features.h>

#endif /* _SYS_TYPES_H_ */

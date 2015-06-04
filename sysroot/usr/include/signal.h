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

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#define THIS_BETTER_BE_DEFINED 1

#include <sys/signal.h>

int kill(pid_t pid, int signal_number);
//int killpg(pid_t, int);
//void psiginfo(const siginfo_t *,const char *);
//void psignal(int, const char *);
//int pthread_kill(pthread_t, int);
//int pthread_sigmask(int, const sigset_t *restrict, sigset_t *restrict);
//int raise(int);
int sigaction(int sig, struct sigaction *__restrict act,
		struct sigaction *__restrict oact);
//int sigaltstack(const stack_t *restruct, stack_t *restrict);
//int sighold(int);
//int sigignore(int);
//int siginterrupt(int, int);
void(*signal(int sig, void(*func)(int)))(int);
//int sigpause(int);
//int sigpending(sigset_t *);
int sigprocmask(int how, sigset_t *set, sigset_t *oset);
int sigqueue(pid_t pid, int signal_number, const union sigval value);
//int sigrelse(int);
//void (*sigset(int, void (*)(int)))(int);
int sigsuspend(const sigset_t *sigmask);
//int sigtimedwait(const sigset_t *restrict, siginfo_t *restrict,
//		const struct timespec *restrict);
int sigwait(const sigset_t *__restrict set, int *__restrict sig);
//int sigwaitinfo(const sigset_t *restrict siginfo_t *restrict);

#endif

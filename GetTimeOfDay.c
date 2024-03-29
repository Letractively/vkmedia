* Copyright (C) 2008 mymtom (mymtom@hotmail.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: src/lib/libtrace/gettimeofday.c,v 1.1 2008/03/28 12:08:44 mymtom Exp $
 */
#include <time.h>
#ifdef WIN32
#   include <windows.h>
#else
#   include <sys/time.h>
#endif
#ifdef WIN32
int
gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year     = wtm.wYear - 1900;
    tm.tm_mon     = wtm.wMonth - 1;
    tm.tm_mday     = wtm.wDay;
    tm.tm_hour     = wtm.wHour;
    tm.tm_min     = wtm.wMinute;
    tm.tm_sec     = wtm.wSecond;
    tm. tm_isdst    = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#endif
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gettimewin.h"
#ifdef WIN32
#   include <windows.h>
#else
#   include <sys/time.h>
#endif
int     gettimeofday(struct timeval *tp, void *tzp);
#if defined(_MSC_VER) && !defined(snprintf)
#define  snprintf  _snprintf
#endif
int main(int argc, char *argv[])
{
    struct timeval     tv;
    char         buf[] = "1970-01-01 00:00:00.000";

        struct tm *newtime;
        char log_name[128];
        char log_time[128];
        time_t lt;
        time(&lt);
        newtime = localtime(&lt);
        strftime( log_name, 128, "%Y%m%d", newtime);
        strftime( log_time,128,"%Y-%m-%d %H:%M:%S",newtime);
 
  printf("%s\n", log_name);
  printf("%s\n", log_time);

    (void)gettimeofday(&tv, 0);   
 newtime = localtime(&(time_t(tv.tv_sec)));
    (void)strftime(buf, sizeof(buf) - 1, "%Y-%m-%d %H:%M:%S.000",
        (localtime(&tv.tv_sec)));
 
    (void)snprintf(buf + 20, 3, "%03d", (int)(tv.tv_usec / 1000));
    (void)printf("%s\n", buf);

    return (0);
}
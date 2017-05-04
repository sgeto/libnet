/*
 *  libnet
 *  libnet.h - Network routine library header file
 *  include/libnet.h.  Generated from libnet.h.in by configure.
 *
 *  Copyright (c) 1998 - 2004 Mike D. Schiffman <mike@infonexus.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
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
 */

#ifndef __LIBNET_H
#define __LIBNET_H

/**
 * @file libnet.h
 * @brief Top-level libnet header file
 * 
 * @details This section doesn't contain any details about libnet.h.
 *
 * If you're wondering why, then that's mostly because libnet.h isn't
 * where the action takes place. In fact, no action at all. Okay, maybe a
 * little. But definitely not enough worth a separate man page or a detailed
 * description. The real action goes down in some of the other files this file
 * includes.
 *
 * Which probably makes you wonder why, of all libnet*.h headers this file
 * includes, only libnet-functions.h and libnet-macros.h are documented.
 * My friend, you're not alone in your marveling.
 *
 * You see, the guy who wrote them (Mike D. Schiffman) is gone, and the guy
 * after him (Sam Roberts) didn't had much time left at the end of the day
 * after bug fixing the living hell out of the source.
 *
 * And if you're wondering why the rest of libnet's documentation is either
 * full of holes or nonexistent, then (a) good question; and (b) see the 
 * previous paragraph.
 *
 * Is this a sinking ship? Well, I can't answer that right now. What I can say
 * is that it's just us now. So, "Lets (try to) make libnet great again"!
 *
 * Sincerely,
 *
 * Ali Abdulkadir
 */

#ifdef __cplusplus
extern "C" {
#endif

 /*
 * TODO move the stuff we ALWAYS need out of the DOXYGEN ifndef block
 * and minimize their redundancies (see doc/TODO)
 */
#ifndef DOXYGEN_SHOULD_SKIP_THIS // mess
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#if !defined(_WIN32)
#include <arpa/inet.h>
#else /* _WIN32 */
#if (__CYGWIN__)
#include <sys/socket.h>
#else
#include <pcap/pcap.h>
#define WPCAP 1 /* FIXME deprecated? */
#include <Packet32.h>
#endif
#if (_MSC_VER)
/* libnet-config - MSVC Edition */
#pragma comment (lib,"ws2_32")      /* Winsock 2 */
//#pragma comment (lib,"wsock_trace") /* Gisle Vanem's excellent Winsock Tracing Library */
#pragma comment (lib,"iphlpapi")    /* IP Helper */
#pragma comment (lib,"wpcap")       /* Winpcap   */
#pragma comment (lib,"packet")     /* Packet    */
#endif /* _MSC_VER */
#include <stdint.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#endif /* _WIN32 */

#define LIBNET_VERSION  "1.2-rc3"

/* Hard-coded for MSVC. Hope that doesn't backfire... */
#if (_MSC_VER)
#define LIBNET_LIL_ENDIAN 1
#else
#define LIBNET_LIL_ENDIAN 1
#endif

#ifndef LIBNET_API
#define LIBNET_API
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "./libnet/libnet-types.h" /* ??? */
#include "./libnet/libnet-macros.h"
#include "./libnet/libnet-headers.h"
#include "./libnet/libnet-structures.h"
#include "./libnet/libnet-asn1.h"
#include "./libnet/libnet-functions.h"

#ifdef __cplusplus
}
#endif

#endif  /* __LIBNET_H */

/* EOF */

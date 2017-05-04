/*
 *  common.h - common headers
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

#if (_WIN32) && !defined (WIN32)
/*
* For pcap.h. Apparently some compilers don't feel the need to define WIN32.
* This has been already taken care of in newer versions of libpcap/Npcap,
* but it hasn't reached many wpcap user yet...
*/
#define WIN32
#endif

/*
* You maybe thinking: The order is weird. Can't the Windows stuff all be
* under one huge #ifdef? Well, no. Unfortunately this is how it needs to
* happen since MinGW and Cygwin should build libnet with a "real" config.h
* and not with the static "winconfig.h".
* MSVC not only insists that "winconfig.h" must be included first, libnet.h
* must also immediately follow. This is most likely related to the pcap thingy
* mentioned above. Until the switch to Npcap, I'll let him/her have this one.
* Feel free to correct me.
*/
#if (_MSC_VER)
#include "../include/winconfig.h"
#define strdup _strdup /* found in libnet_if_addr.c, libnet_init.c and libnet_port_list.c */
#define close _close /* found in libnet_init.c */
#ifdef SHUT_UP_WINDOZE
#pragma warning(disable: 4996) /* _CRT_SECURE_NO_WARNINGS & _WINSOCK_DEPRECATED_NO_WARNINGS */
#endif /* SHUT_UP_WINDOZE */
#pragma comment (lib,"Advapi32") /* needed by libnet_prand.c */
#else
#include "../include/config.h"
#endif /* _MSC_VER */

#include "../include/libnet.h"

#include <fcntl.h> /* libnet_if_addr.c libnet_init.c libnet_raw.c libnet_resolve.c libnet_link_linux.c */
#include <ctype.h> /* libnet_if_addr.c libnet_port_list.c libnet_resolve.c */

#if (_WIN32) || (__CYGWIN__)
#include <malloc.h>    /* alloca() */
#include <Ntddndis.h>
#else

#include <assert.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <sys/ioctl.h> /* libnet_if_addr.c libnet_resolve.c libnet_link_linux.c */
#include <net/if.h> /* libnet_if_addr.c libnet_resolve.c */
#include <arpa/inet.h> /* libnet_resolve.c */
#include <netdb.h>  /* libnet_resolve.c */

#if defined(HAVE_SYS_SOCKIO_H) && !defined(SIOCGIFADDR)
#include <sys/sockio.h>
#endif

#if (HAVE_NET_ETHERNET_H)
#include <net/ethernet.h>
#endif  /* HAVE_NET_ETHERNET_H */

#endif

/* IPPROTO_ and sockaddr_ definitions are here. They are often
 * implicitly pulled in, but some systems need them explicitly
 * included.
 */
#ifndef IPPROTO_MH
#define IPPROTO_MH		135	/* IPv6 mobility header		*/
#endif
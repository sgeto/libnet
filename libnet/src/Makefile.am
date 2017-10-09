#
# Libnet automake information file
# Copyright (c) 1998 - 2004 Mike D. Schiffman <mike@infonexus.com>
# All rights reserved.
#
# Process this file with automake to produce a Makefile.in script.

EXTRA_DIST = libnet_dll.c common.h

lib_LTLIBRARIES = libnet.la

libnet_la_SOURCES = libnet_asn1.c \
			libnet_build_802.1q.c \
			libnet_build_802.1x.c \
			libnet_build_802.2.c \
			libnet_build_802.3.c \
			libnet_build_arp.c \
			libnet_build_bgp.c \
			libnet_build_cdp.c \
			libnet_build_data.c \
			libnet_build_dhcp.c \
			libnet_build_dns.c \
			libnet_build_ethernet.c \
			libnet_build_fddi.c \
			libnet_build_gre.c \
			libnet_build_hsrp.c \
			libnet_build_icmp.c \
			libnet_build_igmp.c \
			libnet_build_ip.c \
			libnet_build_ipsec.c \
			libnet_build_isl.c \
			libnet_build_link.c \
			libnet_build_mpls.c \
			libnet_build_ntp.c \
			libnet_build_ospf.c \
			libnet_build_rip.c \
			libnet_build_rpc.c \
			libnet_build_sebek.c \
			libnet_build_snmp.c \
			libnet_build_stp.c \
			libnet_build_tcp.c \
			libnet_build_token_ring.c \
			libnet_build_udp.c \
			libnet_build_vrrp.c \
			libnet_advanced.c \
			libnet_checksum.c \
			libnet_cq.c \
			libnet_crc.c \
			libnet_error.c \
			libnet_if_addr.c \
			libnet_init.c \
			libnet_internal.c \
			libnet_pblock.c \
			libnet_port_list.c \
			libnet_prand.c \
			libnet_raw.c \
			libnet_resolve.c \
			libnet_version.c \
			libnet_write.c

libnet_la_LIBADD = @LTLIBOBJS@

libnet_la_LDFLAGS = -version-info $(LT_VERSION)

## Windows stuff

if WIN32
libnet_la_LDFLAGS += -no-undefined
# don't do any of this if we're not building shared libnet
if COND_SHARED
libnet_la_SOURCES += libnet_dll_info.rc
libnet_la_LDFLAGS += -Wl,--output-def, -Wl,libnet-9.def
endif
if USE_DEBUG
.rc.lo:
			$(AM_V_GEN)$(LIBTOOL) --mode=compile --silent $(WINDRES) -D_DEBUG -I../include $< -o $@
else
.rc.lo:
			$(AM_V_GEN)$(LIBTOOL) --mode=compile --silent $(WINDRES) -I../include $< -o $@
endif
endif
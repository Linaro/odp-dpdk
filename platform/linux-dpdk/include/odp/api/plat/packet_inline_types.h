/* Copyright (c) 2018, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file
 *
 * ODP packet descriptor
 */

#ifndef ODP_PACKET_INLINE_TYPES_H_
#define ODP_PACKET_INLINE_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @cond _ODP_HIDE_FROM_DOXYGEN_ */

/* Packet field accessor */
#define _odp_pkt_get(pkt, cast, field) \
	(*(cast *)(uintptr_t)((uint8_t *)pkt + _odp_packet_inline.field))

/* Packet header field offsets for inline functions */
typedef struct _odp_packet_inline_offset_t {
	uint16_t mb;
	uint16_t pool;
	uint16_t input;
	uint16_t user_ptr;
	uint16_t l2_offset;
	uint16_t l3_offset;
	uint16_t l4_offset;
	uint16_t timestamp;
	uint16_t input_flags;
	uint16_t buf_addr;
	uint16_t data;
	uint16_t pkt_len;
	uint16_t seg_len;
	uint16_t nb_segs;
	uint16_t udata;
	uint16_t rss;
	uint16_t ol_flags;
	uint64_t rss_flag;

} _odp_packet_inline_offset_t;

/* Packet input & protocol flags */
typedef union {
	/* All input flags */
	uint64_t all;

	/* Individual input flags */
	struct {
		uint64_t dst_queue:1; /* Dst queue present */

		uint64_t timestamp:1; /* Timestamp present */

		uint64_t l2:1;        /* known L2 protocol present */
		uint64_t l3:1;        /* known L3 protocol present */
		uint64_t l4:1;        /* known L4 protocol present */

		uint64_t eth:1;       /* Ethernet */
		uint64_t eth_bcast:1; /* Ethernet broadcast */
		uint64_t eth_mcast:1; /* Ethernet multicast */
		uint64_t jumbo:1;     /* Jumbo frame */
		uint64_t vlan:1;      /* VLAN hdr found */
		uint64_t vlan_qinq:1; /* Stacked VLAN found, QinQ */

		uint64_t snap:1;      /* SNAP */
		uint64_t arp:1;       /* ARP */

		uint64_t ipv4:1;      /* IPv4 */
		uint64_t ipv6:1;      /* IPv6 */
		uint64_t ip_bcast:1;  /* IP broadcast */
		uint64_t ip_mcast:1;  /* IP multicast */
		uint64_t ipfrag:1;    /* IP fragment */
		uint64_t ipopt:1;     /* IP optional headers */

		uint64_t ipsec:1;     /* IPSec packet. Required by the
					 odp_packet_has_ipsec_set() func. */
		uint64_t ipsec_ah:1;  /* IPSec authentication header */
		uint64_t ipsec_esp:1; /* IPSec encapsulating security
					 payload */
		uint64_t udp:1;       /* UDP */
		uint64_t tcp:1;       /* TCP */
		uint64_t sctp:1;      /* SCTP */
		uint64_t icmp:1;      /* ICMP */

		uint64_t color:2;     /* Packet color for traffic mgmt */
		uint64_t nodrop:1;    /* Drop eligibility status */

		uint64_t l3_chksum_done:1; /* L3 checksum validation done */
		uint64_t l4_chksum_done:1; /* L4 checksum validation done */
		uint64_t ipsec_udp:1; /* UDP-encapsulated IPsec packet */
	};
} _odp_packet_input_flags_t;

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif

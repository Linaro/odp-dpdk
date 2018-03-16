/* Copyright (c) 2017-2018, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file
 *
 * Packet flag inline functions
 */

#ifndef _ODP_PLAT_PACKET_FLAG_INLINES_H_
#define _ODP_PLAT_PACKET_FLAG_INLINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <odp/api/abi/packet.h>
#include <odp/api/plat/packet_inlines.h>

/** @internal Inline function offsets */
extern const _odp_packet_inline_offset_t _odp_packet_inline;

/** @internal Inline function @param pkt @return */
static inline uint64_t _odp_packet_input_flags(odp_packet_t pkt)
{
	return _odp_pkt_get(pkt, uint64_t, input_flags);
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_l2(odp_packet_t pkt)
{
	_odp_packet_input_flags_t flags;

	flags.all = _odp_packet_input_flags(pkt);
	return flags.l2;
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_eth(odp_packet_t pkt)
{
	_odp_packet_input_flags_t flags;

	flags.all = _odp_packet_input_flags(pkt);
	return flags.eth;
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_jumbo(odp_packet_t pkt)
{
	_odp_packet_input_flags_t flags;

	flags.all = _odp_packet_input_flags(pkt);
	return flags.jumbo;
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_flow_hash(odp_packet_t pkt)
{
	return _odp_pkt_get(pkt, uint64_t, ol_flags) &
			_odp_packet_inline.rss_flag;
}

/** @internal Inline function @param pkt */
static inline void _odp_packet_has_flow_hash_clr(odp_packet_t pkt)
{
	uint64_t *ol_flags = &_odp_pkt_get(pkt, uint64_t, ol_flags);

	*ol_flags &= ~_odp_packet_inline.rss_flag;
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_ts(odp_packet_t pkt)
{
	_odp_packet_input_flags_t flags;

	flags.all = _odp_packet_input_flags(pkt);
	return flags.timestamp;
}

/** @internal Inline function @param pkt @return */
static inline int _odp_packet_has_ipsec(odp_packet_t pkt)
{
	_odp_packet_input_flags_t flags;

	flags.all = _odp_packet_input_flags(pkt);
	return flags.ipsec;
}

#ifdef __cplusplus
}
#endif

#endif

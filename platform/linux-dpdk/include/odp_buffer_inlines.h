/* Copyright (c) 2014-2018, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

/**
 * @file
 *
 * Inline functions for ODP buffer mgmt routines - implementation internal
 */

#ifndef ODP_BUFFER_INLINES_H_
#define ODP_BUFFER_INLINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <odp_buffer_internal.h>

static inline odp_buffer_t buf_from_buf_hdr(odp_buffer_hdr_t *hdr)
{
	return (odp_buffer_t)hdr;
}

static inline odp_buffer_hdr_t *buf_hdl_to_hdr(odp_buffer_t buf)
{
	return (odp_buffer_hdr_t *)(uintptr_t)buf;
}

static inline odp_event_type_t _odp_buffer_event_type(odp_buffer_t buf)
{
	return buf_hdl_to_hdr(buf)->event_type;
}

static inline void _odp_buffer_event_type_set(odp_buffer_t buf, int ev)
{
	buf_hdl_to_hdr(buf)->event_type = ev;
}

static inline odp_event_t event_from_buf_hdr(odp_buffer_hdr_t *hdr)
{
	return (odp_event_t)hdr;
}

#ifdef __cplusplus
}
#endif

#endif

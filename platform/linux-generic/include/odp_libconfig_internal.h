/* Copyright (c) 2018, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

/**
 * @file
 *
 * Common libconfig functions
 */

#ifndef ODP_LIBCONFIG_INTERNAL_H_
#define ODP_LIBCONFIG_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

int _odp_libconfig_init_global(void);
int _odp_libconfig_term_global(void);

int _odp_libconfig_lookup_int(const char *path, int *value);

#ifdef __cplusplus
}
#endif

#endif

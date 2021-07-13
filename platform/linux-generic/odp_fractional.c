/* Copyright (c) 2021, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp/api/std_types.h>

double odp_fract_u64_to_dbl(const odp_fract_u64_t *fract)
{
	double fraction;

	if (fract->numer == 0)
		fraction = 0.0;
	else
		fraction = (double)fract->numer / fract->denom;

	return fract->integer + fraction;
}

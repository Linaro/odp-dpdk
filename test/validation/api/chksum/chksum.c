/* Copyright (c) 2017-2018, Linaro Limited
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <odp_api.h>
#include <odp_cunit_common.h>

#define NUM_IP_HDR   5
#define IP_HDR_LEN   20

#define NUM_UDP      4
#define MAX_UDP_LEN  128

static uint8_t ODP_ALIGNED(4) ip_hdr_test_vect[NUM_IP_HDR][IP_HDR_LEN] = {
	{	0x45, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11,
		0xAB, 0x33, 0xC0, 0xA8, 0x2C, 0xA2, 0xC0, 0xA8, 0x21, 0x99
	},
	{	0x45, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11,
		0xAB, 0xCA, 0xC0, 0xA8, 0x2C, 0x5E, 0xC0, 0xA8, 0x21, 0x46
	},
	{	0x45, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11,
		0xAB, 0x64, 0xC0, 0xA8, 0x2C, 0x20, 0xC0, 0xA8, 0x21, 0xEA
	},
	{       0x45, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11,
		0xAB, 0x59, 0xC0, 0xA8, 0x2C, 0xD2, 0xC0, 0xA8, 0x21, 0x43
	},
	{	0x45, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x40, 0x11,
		0xAC, 0x06, 0xC0, 0xA8, 0x2C, 0x5C, 0xC0, 0xA8, 0x21, 0x0C
	}
};

struct udp_test_vect_s {
	uint32_t len;

	uint8_t data[MAX_UDP_LEN];
};

static struct udp_test_vect_s ODP_ALIGNED(4) udp_test_vect[NUM_UDP] = {
	{.len = 38,
	.data = { 0x00, 0x11, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x1A, 0xFF, 0x3C,
		  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		  0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xC7, 0xBF
	} },

	{.len = 39,
	.data = { 0x00, 0x11, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x20, 0x40, 0x09, 0x35, 0x00, 0x1B, 0xD6, 0x43,
		  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		  0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0xBF, 0xB7
	} },

	{.len = 59,
	.data = { 0x00, 0x11, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x32, 0x5F, 0x01, 0x71, 0x00, 0x2F, 0xCB, 0xC0,
		  0x09, 0x8B, 0x61, 0x3E, 0x3A, 0x7F, 0x30, 0x0F, 0x4D, 0xEE,
		  0x2D, 0x7D, 0x11, 0xBB, 0xBB, 0x34, 0x0E, 0x9E, 0xC5, 0x3D,
		  0xBB, 0x81, 0x9A, 0x7F, 0xF2, 0x2A, 0xFC, 0x85, 0xA0, 0x1B,
		  0x73, 0x81, 0xC1, 0xB6, 0xE8, 0x91, 0x8C, 0xD8, 0x7F
	} },

	{.len = 109,
	.data = { 0x00, 0x11, 0x00, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x32, 0x5F, 0x01, 0x71, 0x00, 0x61, 0xCB, 0x5C,
		  0x61, 0xAD, 0xFD, 0xE7, 0x4E, 0x98, 0x69, 0x59, 0x12, 0x3F,
		  0xDF, 0xF6, 0x79, 0x8B, 0xB3, 0x94, 0x94, 0x9F, 0x8C, 0x0B,
		  0x67, 0xBA, 0xBA, 0x3C, 0xE2, 0x5F, 0xCA, 0x52, 0x13, 0xB4,
		  0x57, 0x48, 0x99, 0x29, 0x23, 0xAC, 0x5C, 0x59, 0x66, 0xA2,
		  0x7B, 0x35, 0x65, 0x2B, 0x86, 0x5F, 0x47, 0xA7, 0xEE, 0xD4,
		  0x24, 0x99, 0xB9, 0xCE, 0x60, 0xAB, 0x7A, 0xE9, 0x37, 0xF2,
		  0x81, 0x84, 0x98, 0x72, 0x4F, 0x6A, 0x37, 0xE5, 0x4D, 0xB2,
		  0xDE, 0xB8, 0xBD, 0xE3, 0x03, 0x57, 0xF0, 0x5C, 0xA0, 0xAA,
		  0xB9, 0xF3, 0x3F, 0xDF, 0x23, 0xDD, 0x54, 0x2F, 0xCE
	} }
};

/* Correct checksum in network byte order is 0xF3, 0x96 */
#define UDP_LONG_CHKSUM odp_be_to_cpu_16(0xF396)

/* Number of padding bytes in the end of the array */
#define UDP_LONG_PADDING 11

/* Long UDP packet with pseudo header. Checksum field is set to zero.
 * The array contains padding, so that a possible overrun is more likely
 * detected (overrun bytes are not all zeros). */
static uint8_t ODP_ALIGNED(4) udp_test_vect_long[] = {
	0x00, 0x11, 0x05, 0xED, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x00, 0x3F, 0x05, 0xED, 0x00, 0x00,
	0x0B, 0x2C, 0x9C, 0x06, 0x07, 0xF3, 0x51, 0x05, 0xF7, 0xA7,
	0xF4, 0x24, 0xBB, 0x2F, 0x19, 0xBB, 0x23, 0xB4, 0x99, 0x50,
	0x69, 0x10, 0x34, 0xAD, 0xFF, 0x83, 0x7B, 0x36, 0x8B, 0xA8,
	0xEE, 0x7A, 0x31, 0xA8, 0x61, 0x08, 0x10, 0xAE, 0xA4, 0x84,
	0x0F, 0x9B, 0x62, 0xFA, 0xD9, 0xFA, 0x4A, 0x71, 0x26, 0x36,
	0x6D, 0xC4, 0x3D, 0x0A, 0xE7, 0xAD, 0xB6, 0x3A, 0xC2, 0x23,
	0x85, 0x81, 0x17, 0xE6, 0x34, 0xCA, 0x76, 0x58, 0x70, 0xA3,
	0x88, 0x8E, 0xC7, 0xEE, 0xF3, 0xA7, 0xB0, 0xD9, 0x7E, 0x5C,
	0xCC, 0x11, 0x76, 0xD9, 0x6B, 0x33, 0x50, 0xCB, 0x52, 0x84,
	0x8F, 0xBB, 0xBC, 0xE1, 0xE9, 0x9A, 0x9E, 0xF9, 0xA5, 0x9D,
	0x2F, 0xB9, 0x47, 0x4B, 0xA8, 0x08, 0x6F, 0xD4, 0x48, 0xB5,
	0xFF, 0xA4, 0x9C, 0xAD, 0x7C, 0x38, 0xFD, 0x72, 0xB7, 0x30,
	0x5A, 0xC8, 0xAC, 0xA6, 0x38, 0xB2, 0xAA, 0xBF, 0xF6, 0x9C,
	0xB4, 0x7F, 0x56, 0xDA, 0x28, 0xE2, 0x39, 0x51, 0x9E, 0x28,
	0xAA, 0x74, 0x13, 0x70, 0x1E, 0x73, 0x47, 0x88, 0xFA, 0xAE,
	0x63, 0x04, 0x56, 0x70, 0xDF, 0x8D, 0x01, 0xDA, 0xA3, 0x7C,
	0xC5, 0x1D, 0x6C, 0xA8, 0xEC, 0xED, 0x72, 0x7B, 0x02, 0x32,
	0x48, 0x4C, 0xDD, 0x00, 0x03, 0xE8, 0xDB, 0xC9, 0x9E, 0x72,
	0x6B, 0xD1, 0x9D, 0x6E, 0xCF, 0xE3, 0xF1, 0x18, 0x20, 0x43,
	0x1C, 0xFA, 0x92, 0xE3, 0x95, 0xBD, 0xF9, 0xD9, 0x6E, 0x40,
	0x8C, 0x11, 0x34, 0xE7, 0xE9, 0x3F, 0x17, 0x36, 0x5A, 0x18,
	0x4A, 0x9E, 0x57, 0xC2, 0xAD, 0x96, 0x4C, 0x89, 0xAA, 0xEE,
	0x9C, 0xD3, 0x5C, 0x60, 0xE5, 0x56, 0xF7, 0x69, 0x86, 0x88,
	0x64, 0x57, 0x5E, 0x57, 0x2B, 0xA2, 0xD7, 0x1B, 0x96, 0x7F,
	0x23, 0xC9, 0x14, 0xB3, 0xC6, 0x69, 0xDB, 0xA5, 0x55, 0xCA,
	0xD1, 0xB8, 0x7D, 0x74, 0xAD, 0xD7, 0x46, 0xDE, 0x59, 0x52,
	0x99, 0xE1, 0x9B, 0xE8, 0x01, 0x6D, 0xF5, 0x25, 0xAE, 0x7B,
	0xCA, 0xEE, 0xBF, 0x42, 0xC1, 0x5A, 0xC1, 0xAE, 0x6F, 0xC3,
	0x72, 0x0E, 0x30, 0x1D, 0xCB, 0x0D, 0x55, 0x87, 0x3E, 0xE3,
	0x85, 0x20, 0x3D, 0xCC, 0x5D, 0x1C, 0xFB, 0xB9, 0x5A, 0x17,
	0x76, 0x46, 0xF9, 0xA8, 0xB5, 0xED, 0x1C, 0x3A, 0x4E, 0x79,
	0xB0, 0x17, 0x2C, 0xBD, 0x8D, 0xC6, 0x8F, 0x85, 0x9D, 0x97,
	0x54, 0xCD, 0x41, 0x7C, 0x77, 0x31, 0xF0, 0x1A, 0xD6, 0xA5,
	0x22, 0x20, 0x38, 0x66, 0x6C, 0xD8, 0x8D, 0x31, 0xEC, 0xFC,
	0x78, 0xB2, 0xE7, 0xCA, 0x0A, 0x3F, 0xB1, 0x5A, 0xD1, 0xC6,
	0xCD, 0x30, 0x11, 0x04, 0x56, 0x0E, 0x51, 0xF8, 0x9D, 0x0B,
	0x19, 0x98, 0x14, 0xE9, 0xFB, 0xC2, 0x6B, 0xA4, 0xD0, 0x75,
	0xF8, 0x47, 0x44, 0x41, 0x5C, 0x03, 0x95, 0xFC, 0x64, 0x82,
	0x97, 0xB7, 0x2D, 0x79, 0xFC, 0xF0, 0x8C, 0x7D, 0xD2, 0x0A,
	0xAC, 0x17, 0x4D, 0xFA, 0xF9, 0x1A, 0xC7, 0x42, 0x3D, 0x34,
	0x05, 0x23, 0x09, 0xC4, 0xBC, 0x0E, 0x57, 0xEB, 0x53, 0x5D,
	0x6D, 0xE6, 0xEB, 0x40, 0x05, 0x9B, 0x9D, 0xFA, 0xAA, 0x71,
	0x02, 0x4D, 0x65, 0x65, 0xF9, 0x32, 0x99, 0x5B, 0xA4, 0xCE,
	0x2C, 0xB1, 0xB4, 0xA2, 0xE7, 0x1A, 0xE7, 0x02, 0x20, 0xAA,
	0xCE, 0xC8, 0x96, 0x2D, 0xD4, 0x49, 0x9C, 0xBD, 0x7C, 0x88,
	0x7A, 0x94, 0xEA, 0xAA, 0x10, 0x1E, 0xA5, 0xAA, 0xBC, 0x52,
	0x9B, 0x4E, 0x7E, 0x43, 0x66, 0x5A, 0x5A, 0xF2, 0xCD, 0x03,
	0xFE, 0x67, 0x8E, 0xA6, 0xA5, 0x00, 0x5B, 0xBA, 0x3B, 0x08,
	0x22, 0x04, 0xC2, 0x8B, 0x91, 0x09, 0xF4, 0x69, 0xDA, 0xC9,
	0x2A, 0xAA, 0xB3, 0xAA, 0x7C, 0x11, 0xA1, 0xB3, 0x2A, 0xF4,
	0x77, 0xFA, 0x3B, 0x4B, 0x19, 0x60, 0x63, 0x06, 0x86, 0x7B,
	0x2A, 0xA4, 0x16, 0xD4, 0x4B, 0x01, 0x00, 0x53, 0x5A, 0x6F,
	0x1E, 0xF7, 0xAA, 0x09, 0xF5, 0xCA, 0x6E, 0x44, 0xF0, 0x15,
	0x1E, 0xC7, 0xEC, 0xD0, 0x1D, 0x7D, 0xF9, 0x5C, 0x98, 0xE8,
	0x5F, 0x75, 0xB1, 0xB8, 0xE0, 0x62, 0xDD, 0x9C, 0x3D, 0x6E,
	0x8A, 0x58, 0xFC, 0x9C, 0x06, 0x18, 0x67, 0x97, 0x9C, 0x03,
	0xD8, 0xE8, 0x00, 0x14, 0x34, 0x6B, 0xED, 0x25, 0xB6, 0x04,
	0x0C, 0x4D, 0xEE, 0x8E, 0x18, 0x6C, 0x09, 0x14, 0x40, 0x04,
	0x52, 0x44, 0xCC, 0x4B, 0xF9, 0x20, 0x04, 0x7E, 0x13, 0xF7,
	0x4D, 0x77, 0xE3, 0x94, 0x96, 0x82, 0x58, 0xB5, 0xF2, 0x6D,
	0xD6, 0xBF, 0x86, 0xDE, 0x3A, 0xAF, 0xA6, 0xE9, 0x18, 0x54,
	0x3B, 0xE2, 0x46, 0xBC, 0x68, 0x70, 0x9F, 0xEC, 0x6D, 0xE3,
	0x01, 0xD3, 0xCB, 0xC8, 0x98, 0x81, 0xA9, 0xBA, 0x5F, 0x95,
	0x76, 0x7B, 0xE3, 0xF4, 0xD0, 0x43, 0x4B, 0xC1, 0xA4, 0x57,
	0x95, 0x89, 0x97, 0xDE, 0x22, 0xBD, 0xA5, 0xF0, 0x75, 0x66,
	0x08, 0xF1, 0x38, 0x14, 0x5C, 0x1D, 0x7F, 0x17, 0x00, 0x63,
	0x51, 0xF2, 0xBF, 0x77, 0x65, 0x0D, 0xB0, 0x23, 0x29, 0xAA,
	0x5A, 0xDE, 0x08, 0x1A, 0x1C, 0x9F, 0xED, 0x31, 0xCD, 0xF3,
	0x03, 0xF7, 0x9F, 0x4E, 0xC0, 0xA0, 0x49, 0x9E, 0x21, 0xBF,
	0x65, 0x26, 0x37, 0xB6, 0x16, 0x8A, 0xE2, 0x71, 0xEF, 0x26,
	0xDD, 0x54, 0x10, 0xA4, 0xFA, 0x71, 0x92, 0xCE, 0xAF, 0xFF,
	0x26, 0xA0, 0xD2, 0x07, 0xF8, 0xA2, 0xA1, 0x61, 0xDA, 0x75,
	0x05, 0xDF, 0x9E, 0xAB, 0x18, 0xC8, 0xC3, 0xDC, 0xE4, 0x88,
	0x55, 0xF5, 0x6E, 0xA5, 0x0E, 0xD4, 0xF3, 0xF5, 0xC1, 0x12,
	0x71, 0x0F, 0xF9, 0x20, 0x69, 0xFF, 0xDD, 0x96, 0xE3, 0x3E,
	0x56, 0xC7, 0xB4, 0xE1, 0x74, 0x99, 0xFC, 0x10, 0x0E, 0x94,
	0xF2, 0xBA, 0xA9, 0x38, 0xE4, 0x87, 0x9B, 0x94, 0x79, 0x0E,
	0x71, 0x14, 0x3A, 0x49, 0x8D, 0x9B, 0x50, 0x45, 0x14, 0xD1,
	0x8F, 0x1E, 0x07, 0xBF, 0xB4, 0x2B, 0xAF, 0x99, 0xEB, 0x76,
	0x3F, 0xDA, 0x95, 0x6F, 0xB5, 0x96, 0x47, 0xE1, 0x01, 0x0C,
	0x16, 0x24, 0x69, 0x7C, 0x12, 0x95, 0x2C, 0x38, 0x10, 0x43,
	0x65, 0xFC, 0xAD, 0xEB, 0x33, 0x82, 0x8F, 0x27, 0x17, 0x52,
	0xEE, 0xE2, 0x9D, 0xD8, 0x53, 0x0F, 0x3F, 0xB8, 0xA0, 0x9A,
	0x86, 0x66, 0x51, 0x9F, 0x72, 0xF1, 0x01, 0xDB, 0x1C, 0x1F,
	0x30, 0x60, 0x9A, 0xBF, 0x43, 0x8C, 0x23, 0x3B, 0xCC, 0x3B,
	0x73, 0x6D, 0x0C, 0x3C, 0x71, 0xB3, 0xB7, 0x02, 0x10, 0x46,
	0xF6, 0x9C, 0x73, 0xC7, 0xB2, 0xE8, 0x54, 0x1B, 0x10, 0x03,
	0xA6, 0x79, 0x38, 0x03, 0x79, 0xC1, 0x5B, 0xE9, 0x1F, 0x10,
	0xF4, 0xD1, 0x8D, 0x91, 0x4E, 0x6C, 0x03, 0x96, 0x46, 0xB0,
	0xF0, 0xE7, 0x52, 0xCE, 0x10, 0x59, 0xC2, 0x65, 0xD7, 0xA3,
	0x46, 0xF5, 0x12, 0x6E, 0xB1, 0x96, 0xCC, 0xAB, 0xFC, 0xEA,
	0x6E, 0x29, 0x8E, 0x50, 0x2B, 0x67, 0xBA, 0x5A, 0x9B, 0xA7,
	0x8A, 0x82, 0xA6, 0x43, 0xBB, 0x18, 0xA4, 0x44, 0x08, 0x7F,
	0xC2, 0x31, 0xAC, 0x99, 0xA8, 0x25, 0x22, 0x80, 0x59, 0x24,
	0x2F, 0x77, 0x5A, 0xAF, 0x22, 0x20, 0x16, 0x96, 0x5B, 0xEF,
	0x81, 0x0E, 0x0A, 0xDE, 0xFC, 0x03, 0x39, 0x62, 0x79, 0xB0,
	0x0D, 0x9E, 0xDF, 0x6C, 0x48, 0xD7, 0xB0, 0xC7, 0x13, 0x29,
	0xE9, 0xD5, 0xFB, 0x78, 0x29, 0xCA, 0x39, 0xA9, 0x16, 0xC7,
	0x36, 0x11, 0xFC, 0xF4, 0x4E, 0x2D, 0xB8, 0xCF, 0xD4, 0x94,
	0xD5, 0xC4, 0x57, 0x2B, 0xF4, 0xFD, 0x24, 0x98, 0x71, 0x7B,
	0x0C, 0xF9, 0x43, 0x66, 0x68, 0xD5, 0x24, 0xA1, 0x5A, 0x52,
	0xF3, 0xA2, 0x55, 0xA9, 0x56, 0x81, 0xDF, 0xD8, 0xA3, 0x4E,
	0x95, 0x97, 0x01, 0xA8, 0x70, 0x8C, 0xCA, 0x8B, 0x48, 0xC2,
	0x34, 0x6A, 0x96, 0x58, 0x31, 0x7E, 0x7E, 0x76, 0x93, 0x5D,
	0x0D, 0x85, 0x74, 0xCE, 0xBF, 0xA0, 0xD5, 0xDC, 0x44, 0x45,
	0x85, 0x29, 0x83, 0x51, 0x45, 0x85, 0xE0, 0x2B, 0x29, 0xBF,
	0xBA, 0x3F, 0x41, 0xBB, 0x38, 0xAE, 0x79, 0xC5, 0x46, 0x43,
	0xBE, 0x25, 0xDA, 0xAA, 0x62, 0xF4, 0x7C, 0xDC, 0xC2, 0x2E,
	0x05, 0xDE, 0x26, 0x08, 0xA7, 0xAB, 0xE8, 0x83, 0x2D, 0x6F,
	0xD9, 0x41, 0x84, 0xF5, 0xE0, 0x97, 0x7B, 0x63, 0xE4, 0xE5,
	0xC7, 0x25, 0xEC, 0x22, 0x4A, 0x27, 0x85, 0xBB, 0x95, 0x47,
	0x65, 0x9E, 0xAB, 0x0A, 0x4D, 0x91, 0x07, 0x8D, 0x34, 0xC9,
	0xE1, 0xBF, 0xA1, 0xB8, 0xAE, 0xCE, 0x59, 0x26, 0xE6, 0xDF,
	0x3A, 0x83, 0x09, 0x02, 0x67, 0x7C, 0xE4, 0x65, 0xA5, 0xCC,
	0x11, 0xC8, 0x05, 0x55, 0xBD, 0x30, 0xC4, 0x6F, 0xAD, 0xE0,
	0x6F, 0x80, 0x83, 0x85, 0x4A, 0xCD, 0x3E, 0xB1, 0xF3, 0x8F,
	0x01, 0x8A, 0x43, 0x4A, 0x15, 0xC4, 0x75, 0x5A, 0x30, 0xCC,
	0x8A, 0xCE, 0xF8, 0x46, 0xEB, 0x7A, 0xC3, 0xBA, 0x51, 0x48,
	0xA1, 0x8A, 0xE2, 0xCF, 0x9C, 0x28, 0x9D, 0x27, 0x3E, 0x85,
	0xF7, 0xFB, 0x54, 0xCD, 0xC6, 0xDF, 0xF2, 0x51, 0x5F, 0xE4,
	0xB7, 0xC5, 0xFB, 0x6A, 0x52, 0xAB, 0x60, 0x36, 0x45, 0x0F,
	0xBD, 0xC5, 0xE9, 0x75, 0xD5, 0xDF, 0xB3, 0x10, 0x5F, 0x6F,
	0xB5, 0x34, 0xAD, 0x91, 0x68, 0x0E, 0x8D, 0xED, 0xA8, 0x93,
	0x6D, 0x44, 0x00, 0xB6, 0xC2, 0x48, 0x28, 0xDE, 0xAA, 0xB1,
	0xCC, 0x97, 0xCF, 0x8D, 0x8F, 0x87, 0x8F, 0xD7, 0x50, 0xA5,
	0x5B, 0x4C, 0xAC, 0xA5, 0x5D, 0x7A, 0xC4, 0xB6, 0x5E, 0x1A,
	0x40, 0x70, 0xE6, 0x9F, 0x94, 0x08, 0xA5, 0x0F, 0x81, 0xC7,
	0x11, 0x12, 0xDF, 0xBA, 0x51, 0x49, 0x9B, 0xAA, 0x5A, 0xE0,
	0xFC, 0x4E, 0x58, 0x67, 0x2A, 0xC0, 0x4F, 0xDD, 0xF0, 0x2E,
	0x02, 0x0E, 0xC1, 0xD2, 0x14, 0x20, 0xF9, 0x24, 0x6D, 0x68,
	0x66, 0x4E, 0xDF, 0x82, 0x07, 0xE0, 0x09, 0xA0, 0x13, 0xC5,
	0x7C, 0x22, 0x3D, 0x76, 0x1D, 0x67, 0x37, 0x6D, 0xCB, 0xE3,
	0x75, 0xDD, 0x41, 0x72, 0x33, 0xA0, 0x3D, 0xEC, 0xB9, 0x70,
	0xE2, 0xFA, 0xDE, 0x5B, 0x5A, 0x28, 0xCB, 0x71, 0xC1, 0x3B,
	0x01, 0xC0, 0x3E, 0xC4, 0x9E, 0x82, 0x73, 0xF5, 0xDB, 0x94,
	0x18, 0xB4, 0xDA, 0x2A, 0xE2, 0xEE, 0x9F, 0xC2, 0xAA, 0x2E,
	0x5C, 0x56, 0xCB, 0x6E, 0xF1, 0xD6, 0xCC, 0x2D, 0xB3, 0xD5,
	0x3F, 0xC1, 0x6C, 0x83, 0xE8, 0xEF, 0xA4, 0xDB, 0x22, 0xB9,
	0x1F, 0x1D, 0x7F, 0x77, 0xA7, 0x7F, 0xAF, 0x29, 0x0C, 0x1F,
	0xA3, 0x0C, 0x68, 0x3D, 0xF1, 0x6B, 0xA7, 0xA7, 0x7B, 0xB8,
	0x47, 0x74, 0x4C, 0xDB, 0x5D, 0xF5, 0xC2, 0xCA, 0xD9, 0xE9,
	0xF2, 0x5A, 0x0A, 0xF0, 0x48, 0x55, 0x65, 0x43, 0x6E, 0xCC,
	0x82, 0xA1, 0x6F, 0xAE, 0x67, 0x8D, 0x1D, 0x9A, 0x09, 0xB6,
	0xB0, 0xF2, 0x10, 0xB7, 0xAF, 0x31, 0xDB, 0x00, 0x14, 0x7E,
	0xC4, 0x14, 0xAB, 0x81, 0xA5, 0xF6, 0xBB, 0x75, 0x9B, 0xDD,
	0xE8, 0x7E, 0x09, 0x2F, 0x58, 0x3D, 0xE0, 0xAD, 0x15, 0xA2,
	0x1E, 0xEB, 0xB2, 0x02, 0x95, 0x04, 0x32, 0x6A, 0xEE, 0x8B,
	0x25, 0x32, 0xED, 0xC5, 0x14, 0xD5, 0xF7, 0x15, 0x1F, 0x00,
	0xD1, 0xB7, 0xE5, 0xE8, 0xAA, 0xB1, 0xA4, 0xE1, 0x5C, 0x07,
	0xA1, 0x2D, 0xEF, 0x2F, 0xCB, 0x11, 0x5E, 0xC4, 0x9B, 0x2E,
	0x9E, 0x7F, 0x3E, 0x0F, 0xDD, 0x62, 0xF6, 0xB3, 0xE2, 0xEE,
	0xDE, 0xAD, 0xBE, 0xEF, 0xEE, 0xEE, 0xDE, 0xAD, 0xBE, 0xEF
};

/* Test ones complement sum with IPv4 headers */
static void chksum_ones_complement_ip(void)
{
	int i;
	uint16_t sum, res;

	for (i = 0; i < NUM_IP_HDR; i++) {
		sum = odp_chksum_ones_comp16(ip_hdr_test_vect[i], IP_HDR_LEN);
		res = ~sum;

		CU_ASSERT(res == 0);
	}
}

/* Test ones complement sum with various length pseudo UDP packets */
static void chksum_ones_complement_udp(void)
{
	int i;
	uint16_t sum, res;

	for (i = 0; i < NUM_UDP; i++) {
		sum = odp_chksum_ones_comp16(udp_test_vect[i].data,
					     udp_test_vect[i].len);
		res = ~sum;

		CU_ASSERT(res == 0);
	}
}

/* Test ones complement sum with a long pseudo UDP packet */
static void chksum_ones_complement_udp_long(void)
{
	int i;
	uint16_t sum, res;
	uint32_t offset, frag_sum;
	uint32_t len = sizeof(udp_test_vect_long) - UDP_LONG_PADDING;
	int num_frag = 7;
	uint32_t frag_len = len / num_frag;

	/* Checksum all data */
	sum = odp_chksum_ones_comp16(udp_test_vect_long, len);
	res = ~sum;

	CU_ASSERT(res == UDP_LONG_CHKSUM);

	/* Checksum data in fragments */
	frag_sum = 0;
	offset = 0;

	for (i = 0; i < num_frag; i++) {
		if (i == num_frag - 1)
			frag_len = len - offset;

		/* Check that test passes 16 bit aligned addresses */
		CU_ASSERT_FATAL((offset % 2) == 0);

		frag_sum += odp_chksum_ones_comp16(&udp_test_vect_long[offset],
						   frag_len);

		offset += frag_len;
	}

	/* Fold 32-bit sum to 16 bits */
	while (frag_sum >> 16)
		frag_sum = (frag_sum & 0xffff) + (frag_sum >> 16);

	res = ~frag_sum;

	CU_ASSERT(res == UDP_LONG_CHKSUM);
}

odp_testinfo_t chksum_suite[] = {
	ODP_TEST_INFO(chksum_ones_complement_ip),
	ODP_TEST_INFO(chksum_ones_complement_udp),
	ODP_TEST_INFO(chksum_ones_complement_udp_long),
	ODP_TEST_INFO_NULL,
};

odp_suiteinfo_t chksum_suites[] = {
	{"Checksum", NULL, NULL, chksum_suite},
	ODP_SUITE_INFO_NULL
};

int main(int argc, char *argv[])
{
	int ret;

	/* parse common options: */
	if (odp_cunit_parse_options(argc, argv))
		return -1;

	ret = odp_cunit_register(chksum_suites);

	if (ret == 0)
		ret = odp_cunit_run();

	return ret;
}

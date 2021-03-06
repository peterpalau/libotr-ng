/*
 *  This file is part of the Off-the-Record Next Generation Messaging
 *  library (libotr-ng).
 *
 *  Copyright (C) 2016-2018, the libotr-ng contributors.
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <string.h>

#define OTRNG_DAKE_PRIVATE

#include "test_helpers.h"

#include "test_fixtures.h"

#include "auth.h"
#include "dake.h"
#include "serialize.h"

static void test_build_interactive_rsign_tag() {
  // Wow. 1KB
  uint8_t expected_t1[1083] = {
      0x01, 0x9d, 0x4c, 0x99, 0x80, 0x7b, 0x0c, 0xf7, 0xaa, 0x4d, 0x1e, 0xdd,
      0x52, 0x05, 0xfa, 0x61, 0x54, 0x66, 0x7c, 0x28, 0x99, 0x51, 0x37, 0x09,
      0xb4, 0xe6, 0xb9, 0x84, 0x00, 0x0b, 0x91, 0x23, 0x61, 0xb6, 0xcd, 0x72,
      0x6e, 0x9e, 0x96, 0x55, 0xce, 0x9e, 0xae, 0x8f, 0xf9, 0xfa, 0x56, 0x1c,
      0xc6, 0x25, 0xab, 0x33, 0x85, 0x6f, 0xfc, 0xd1, 0xe7, 0x41, 0x25, 0xf1,
      0x34, 0xb2, 0x43, 0xbc, 0x41, 0x26, 0x1b, 0xb2, 0xaa, 0xad, 0x20, 0x9f,
      0x90, 0xe6, 0xc9, 0xa8, 0x2b, 0x0d, 0x65, 0xc4, 0xdb, 0x6e, 0x24, 0xb9,
      0x4e, 0x8c, 0x43, 0x76, 0x92, 0xfa, 0xd2, 0x7c, 0x97, 0xd5, 0x59, 0xd4,
      0x67, 0xbc, 0x50, 0x84, 0x3b, 0x35, 0xd0, 0x05, 0x64, 0x33, 0x41, 0x92,
      0xa4, 0x7a, 0x40, 0x40, 0x69, 0xad, 0xfa, 0xa8, 0x78, 0x1c, 0x3a, 0x9b,
      0x3f, 0xf5, 0x45, 0x1a, 0xa1, 0xab, 0x4c, 0x28, 0xfe, 0x73, 0x58, 0x9d,
      0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c, 0xf8, 0xcf, 0xb4,
      0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b, 0xef, 0xea, 0xba,
      0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6, 0x76, 0x7c, 0x4b,
      0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4, 0x43, 0xce, 0x4b,
      0x51, 0x51, 0x6a, 0x46, 0x90, 0x00, 0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24,
      0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0, 0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5,
      0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3, 0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe,
      0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44, 0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d,
      0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b, 0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c,
      0xfa, 0xbf, 0x80, 0x00, 0x00, 0x01, 0x80, 0x77, 0x98, 0xd0, 0x39, 0x9f,
      0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f, 0xb2, 0x62, 0x8f, 0x5a, 0x9c,
      0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b, 0x70, 0xcc, 0xeb, 0xdc, 0x81,
      0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8, 0x4d, 0x84, 0xa7, 0x55, 0xb9,
      0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29, 0xd5, 0x9b, 0x86, 0x11, 0xe7,
      0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d, 0xfb, 0x4a, 0x57, 0x91, 0x11,
      0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58, 0x50, 0xc9, 0x29, 0xce, 0x9b,
      0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92, 0x5b, 0xa3, 0x04, 0x9d, 0xf7,
      0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb, 0xd6, 0x23, 0xaf, 0xb9, 0x96,
      0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1, 0x28, 0xb3, 0x8b, 0x2b, 0xb4,
      0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9, 0x64, 0x90, 0x13, 0x9e, 0xa8,
      0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51, 0x3f, 0x10, 0x91, 0xd6, 0x9b,
      0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e, 0x9e, 0x63, 0x5a, 0x64, 0x22,
      0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5, 0x14, 0x42, 0x8e, 0x8d, 0x25,
      0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f, 0xef, 0x5b, 0x26, 0x09, 0xe6,
      0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea, 0xa8, 0x7b, 0x94, 0xfc, 0x78,
      0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b, 0xc7, 0xdd, 0xec, 0x75, 0xcc,
      0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77, 0x7b, 0x4a, 0xce, 0xcb, 0xd7,
      0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00, 0x1c, 0x32, 0xdd, 0xc1, 0x40,
      0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8, 0xaf, 0xdb, 0x24, 0xfb, 0xa9,
      0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a, 0xbc, 0x00, 0x3e, 0xc8, 0x66,
      0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52, 0x08, 0x92, 0x88, 0xe9, 0x5b,
      0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57, 0x21, 0xe8, 0x40, 0x73, 0x89,
      0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa, 0xd7, 0xf1, 0x58, 0x10, 0xb0,
      0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f, 0x57, 0xf6, 0x35, 0x87, 0x87,
      0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd, 0x27, 0xac, 0x99, 0x30, 0x86,
      0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6, 0x1a, 0x54, 0x89, 0x09, 0x15,
      0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e, 0x67, 0x84, 0x8a, 0x83, 0xf2,
      0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2, 0x13, 0xf0, 0x3c, 0xcd, 0x1e,
      0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd, 0xf4, 0xd6, 0x23, 0x48, 0xf9,
      0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d, 0x76, 0x77, 0x63, 0xd7, 0xab,
      0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80, 0x23, 0x53, 0xe5, 0x4c, 0xa6,
      0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d, 0x00, 0x00, 0x01, 0x80, 0xc3,
      0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38, 0xab,
      0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e, 0xba,
      0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86, 0x71,
      0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d, 0xaf,
      0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f, 0xcb,
      0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52, 0xf2,
      0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34, 0xd5,
      0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18, 0xbb,
      0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91, 0x66,
      0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83, 0xa4,
      0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e, 0x9a,
      0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61, 0x28,
      0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08, 0xa8,
      0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9, 0x81,
      0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b, 0x2d,
      0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82, 0xaa,
      0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff, 0x6f,
      0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49, 0x65,
      0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f, 0xb0,
      0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64, 0x10,
      0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57, 0xb1,
      0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0, 0x97,
      0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda, 0xa5,
      0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3, 0x52,
      0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee, 0x1f,
      0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22, 0xbf,
      0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58, 0xcb,
      0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65, 0xf3,
      0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36, 0x34,
      0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91, 0xdd,
      0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30, 0x1e,
      0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9, 0xf6,
      0xbe, 0xd3, 0x50, 0xa8, 0xac, 0xc1, 0x48, 0x21, 0xca, 0xe8, 0x7d, 0x9b,
      0xea, 0x5c, 0x99, 0x1a, 0xf6, 0x7a, 0x7b, 0x7c, 0x61, 0x43, 0xac, 0x50,
      0x99, 0x99, 0x18, 0x89, 0xb7, 0x23, 0x70, 0xea, 0x0f, 0x91, 0x40, 0x71,
      0xc3, 0x32, 0xe5, 0x6c, 0x8b, 0x60, 0x21, 0x9a, 0xc5, 0x86, 0x4b, 0x6a,
      0xca, 0x1b, 0xd9, 0xd7, 0x9d, 0xa7, 0x03, 0x53, 0xd6, 0x9a, 0xca, 0xd7,
      0x21, 0xe0, 0xa2,
  };

  uint8_t expected_t2[1083] = {
      0x00, 0xf6, 0x98, 0xf0, 0xbd, 0x95, 0x48, 0x69, 0x56, 0xff, 0xc0, 0xba,
      0x0d, 0x83, 0x8a, 0xf3, 0x12, 0x53, 0xea, 0x5c, 0x0d, 0x7f, 0x45, 0x92,
      0xf3, 0x40, 0x5b, 0x08, 0x53, 0xb9, 0x31, 0x71, 0x09, 0xc0, 0x77, 0xa0,
      0x06, 0xfd, 0x73, 0x79, 0x1d, 0x60, 0x91, 0xd2, 0x9c, 0x4f, 0x7c, 0x3e,
      0x44, 0x2e, 0x05, 0x3c, 0xe7, 0x52, 0x5e, 0xcf, 0xf6, 0x8b, 0x8b, 0x1a,
      0x23, 0xba, 0x96, 0x81, 0xee, 0x1e, 0xfb, 0x0e, 0xf3, 0x5a, 0x83, 0xa3,
      0x48, 0x61, 0xe5, 0xcc, 0xd1, 0xb4, 0x35, 0xf8, 0xf7, 0x7c, 0xed, 0x09,
      0x87, 0x76, 0xc3, 0x28, 0x3b, 0xcf, 0xd6, 0x19, 0x75, 0x0e, 0xf3, 0x8d,
      0x9e, 0x69, 0xd6, 0xd1, 0x4c, 0x1a, 0xb2, 0x09, 0xef, 0x64, 0x9a, 0x74,
      0x87, 0xc4, 0x67, 0xbb, 0xaa, 0xac, 0x0c, 0x65, 0xfc, 0xff, 0x94, 0xc3,
      0x7d, 0xb1, 0x86, 0x07, 0x70, 0x9a, 0x9d, 0xd5, 0xc1, 0x73, 0x58, 0x9d,
      0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c, 0xf8, 0xcf, 0xb4,
      0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b, 0xef, 0xea, 0xba,
      0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6, 0x76, 0x7c, 0x4b,
      0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4, 0x43, 0xce, 0x4b,
      0x51, 0x51, 0x6a, 0x46, 0x90, 0x00, 0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24,
      0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0, 0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5,
      0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3, 0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe,
      0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44, 0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d,
      0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b, 0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c,
      0xfa, 0xbf, 0x80, 0x00, 0x00, 0x01, 0x80, 0x77, 0x98, 0xd0, 0x39, 0x9f,
      0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f, 0xb2, 0x62, 0x8f, 0x5a, 0x9c,
      0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b, 0x70, 0xcc, 0xeb, 0xdc, 0x81,
      0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8, 0x4d, 0x84, 0xa7, 0x55, 0xb9,
      0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29, 0xd5, 0x9b, 0x86, 0x11, 0xe7,
      0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d, 0xfb, 0x4a, 0x57, 0x91, 0x11,
      0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58, 0x50, 0xc9, 0x29, 0xce, 0x9b,
      0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92, 0x5b, 0xa3, 0x04, 0x9d, 0xf7,
      0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb, 0xd6, 0x23, 0xaf, 0xb9, 0x96,
      0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1, 0x28, 0xb3, 0x8b, 0x2b, 0xb4,
      0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9, 0x64, 0x90, 0x13, 0x9e, 0xa8,
      0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51, 0x3f, 0x10, 0x91, 0xd6, 0x9b,
      0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e, 0x9e, 0x63, 0x5a, 0x64, 0x22,
      0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5, 0x14, 0x42, 0x8e, 0x8d, 0x25,
      0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f, 0xef, 0x5b, 0x26, 0x09, 0xe6,
      0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea, 0xa8, 0x7b, 0x94, 0xfc, 0x78,
      0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b, 0xc7, 0xdd, 0xec, 0x75, 0xcc,
      0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77, 0x7b, 0x4a, 0xce, 0xcb, 0xd7,
      0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00, 0x1c, 0x32, 0xdd, 0xc1, 0x40,
      0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8, 0xaf, 0xdb, 0x24, 0xfb, 0xa9,
      0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a, 0xbc, 0x00, 0x3e, 0xc8, 0x66,
      0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52, 0x08, 0x92, 0x88, 0xe9, 0x5b,
      0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57, 0x21, 0xe8, 0x40, 0x73, 0x89,
      0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa, 0xd7, 0xf1, 0x58, 0x10, 0xb0,
      0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f, 0x57, 0xf6, 0x35, 0x87, 0x87,
      0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd, 0x27, 0xac, 0x99, 0x30, 0x86,
      0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6, 0x1a, 0x54, 0x89, 0x09, 0x15,
      0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e, 0x67, 0x84, 0x8a, 0x83, 0xf2,
      0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2, 0x13, 0xf0, 0x3c, 0xcd, 0x1e,
      0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd, 0xf4, 0xd6, 0x23, 0x48, 0xf9,
      0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d, 0x76, 0x77, 0x63, 0xd7, 0xab,
      0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80, 0x23, 0x53, 0xe5, 0x4c, 0xa6,
      0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d, 0x00, 0x00, 0x01, 0x80, 0xc3,
      0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38, 0xab,
      0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e, 0xba,
      0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86, 0x71,
      0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d, 0xaf,
      0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f, 0xcb,
      0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52, 0xf2,
      0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34, 0xd5,
      0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18, 0xbb,
      0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91, 0x66,
      0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83, 0xa4,
      0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e, 0x9a,
      0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61, 0x28,
      0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08, 0xa8,
      0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9, 0x81,
      0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b, 0x2d,
      0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82, 0xaa,
      0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff, 0x6f,
      0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49, 0x65,
      0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f, 0xb0,
      0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64, 0x10,
      0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57, 0xb1,
      0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0, 0x97,
      0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda, 0xa5,
      0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3, 0x52,
      0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee, 0x1f,
      0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22, 0xbf,
      0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58, 0xcb,
      0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65, 0xf3,
      0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36, 0x34,
      0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91, 0xdd,
      0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30, 0x1e,
      0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9, 0xe0,
      0xef, 0x56, 0x4e, 0x78, 0xe4, 0x41, 0x71, 0xca, 0xc9, 0xd3, 0x70, 0x31,
      0xe3, 0xd8, 0x30, 0x5d, 0xe5, 0xd1, 0x13, 0xda, 0xae, 0x2f, 0xc9, 0xb3,
      0x14, 0x85, 0xf1, 0x32, 0x45, 0x8f, 0xd5, 0xce, 0xe2, 0x46, 0x5b, 0x56,
      0x3e, 0x1d, 0xd5, 0xe6, 0xcf, 0x7d, 0xd8, 0x6b, 0xa0, 0xeb, 0xcd, 0xc5,
      0xd7, 0x2f, 0x5b, 0x07, 0xd4, 0x92, 0x75, 0x4e, 0x97, 0xd8, 0xdd, 0xf6,
      0x97, 0x93, 0xd6,
  };

  dh_mpi initiator_dh = NULL;
  uint8_t initiator_dh_s[DH3072_MOD_LEN_BYTES] = {
      0x77, 0x98, 0xd0, 0x39, 0x9f, 0xe3, 0x45, 0x5b, 0x2c, 0xb0, 0x62, 0x5f,
      0xb2, 0x62, 0x8f, 0x5a, 0x9c, 0x35, 0xa5, 0xd5, 0x19, 0xb0, 0xaf, 0x4b,
      0x70, 0xcc, 0xeb, 0xdc, 0x81, 0xc9, 0x24, 0xa3, 0x1b, 0xcb, 0xc1, 0xf8,
      0x4d, 0x84, 0xa7, 0x55, 0xb9, 0xd2, 0xba, 0x3c, 0x84, 0x6e, 0x62, 0x29,
      0xd5, 0x9b, 0x86, 0x11, 0xe7, 0xe9, 0x93, 0xd6, 0x41, 0x9e, 0xce, 0x9d,
      0xfb, 0x4a, 0x57, 0x91, 0x11, 0xdb, 0x5e, 0x4f, 0x4b, 0x99, 0x43, 0x58,
      0x50, 0xc9, 0x29, 0xce, 0x9b, 0x75, 0x4b, 0x56, 0x3a, 0xfc, 0xe5, 0x92,
      0x5b, 0xa3, 0x04, 0x9d, 0xf7, 0xf8, 0x1a, 0xed, 0x98, 0x86, 0x3a, 0xeb,
      0xd6, 0x23, 0xaf, 0xb9, 0x96, 0x73, 0xbd, 0x5a, 0x68, 0xb2, 0x99, 0xb1,
      0x28, 0xb3, 0x8b, 0x2b, 0xb4, 0x4b, 0x82, 0x23, 0x43, 0xee, 0xa0, 0xf9,
      0x64, 0x90, 0x13, 0x9e, 0xa8, 0x3d, 0x0f, 0x09, 0x36, 0xe3, 0x0a, 0x51,
      0x3f, 0x10, 0x91, 0xd6, 0x9b, 0x3b, 0x6d, 0x32, 0xf2, 0x08, 0xbc, 0x0e,
      0x9e, 0x63, 0x5a, 0x64, 0x22, 0x83, 0xe2, 0x9c, 0xfe, 0xf8, 0x68, 0xc5,
      0x14, 0x42, 0x8e, 0x8d, 0x25, 0x30, 0x69, 0x7b, 0x3c, 0x04, 0x25, 0x4f,
      0xef, 0x5b, 0x26, 0x09, 0xe6, 0xc3, 0xa7, 0x50, 0xeb, 0x25, 0x99, 0xea,
      0xa8, 0x7b, 0x94, 0xfc, 0x78, 0xce, 0x2c, 0x43, 0x0a, 0x2b, 0x0f, 0x1b,
      0xc7, 0xdd, 0xec, 0x75, 0xcc, 0x27, 0x86, 0x71, 0xc2, 0x1b, 0xcf, 0x77,
      0x7b, 0x4a, 0xce, 0xcb, 0xd7, 0xd9, 0xbf, 0x91, 0x6f, 0xe1, 0x3c, 0x00,
      0x1c, 0x32, 0xdd, 0xc1, 0x40, 0x91, 0xd6, 0xce, 0xca, 0x7d, 0x7c, 0xd8,
      0xaf, 0xdb, 0x24, 0xfb, 0xa9, 0xc6, 0x62, 0x19, 0x54, 0xf4, 0x2c, 0x7a,
      0xbc, 0x00, 0x3e, 0xc8, 0x66, 0xc1, 0xac, 0xd2, 0x03, 0x8b, 0x33, 0x52,
      0x08, 0x92, 0x88, 0xe9, 0x5b, 0x24, 0x12, 0x61, 0x0c, 0x54, 0x5e, 0x57,
      0x21, 0xe8, 0x40, 0x73, 0x89, 0x1c, 0x45, 0xf8, 0x99, 0x4f, 0xcc, 0xfa,
      0xd7, 0xf1, 0x58, 0x10, 0xb0, 0xeb, 0x53, 0x1a, 0x4c, 0xca, 0xb8, 0x0f,
      0x57, 0xf6, 0x35, 0x87, 0x87, 0x83, 0x1b, 0x66, 0x3b, 0x94, 0xfc, 0xcd,
      0x27, 0xac, 0x99, 0x30, 0x86, 0x46, 0x79, 0x23, 0xa5, 0xf8, 0x24, 0xe6,
      0x1a, 0x54, 0x89, 0x09, 0x15, 0x8f, 0x41, 0x81, 0x5e, 0x01, 0xbc, 0x7e,
      0x67, 0x84, 0x8a, 0x83, 0xf2, 0x6b, 0x99, 0x77, 0xd6, 0x20, 0x1e, 0xc2,
      0x13, 0xf0, 0x3c, 0xcd, 0x1e, 0xed, 0xcc, 0xed, 0x40, 0x8b, 0x73, 0xdd,
      0xf4, 0xd6, 0x23, 0x48, 0xf9, 0xbc, 0x94, 0x8c, 0x18, 0x88, 0x0d, 0x9d,
      0x76, 0x77, 0x63, 0xd7, 0xab, 0x4f, 0x7f, 0x25, 0x6d, 0xe2, 0xad, 0x80,
      0x23, 0x53, 0xe5, 0x4c, 0xa6, 0xbf, 0xc4, 0x2d, 0x3d, 0x88, 0x9d, 0x2d,
  };

  dh_mpi responder_dh = NULL;
  uint8_t responder_dh_s[DH3072_MOD_LEN_BYTES] = {
      0xc3, 0x65, 0xc1, 0x7f, 0x33, 0x1a, 0x11, 0xc6, 0x03, 0x51, 0x86, 0x38,
      0xab, 0x10, 0x0b, 0x80, 0x4d, 0x25, 0xdf, 0x0b, 0xb1, 0xeb, 0x09, 0x8e,
      0xba, 0x09, 0x62, 0x53, 0xdb, 0x05, 0x55, 0xf4, 0xd5, 0xaa, 0x02, 0x86,
      0x71, 0xd6, 0x0c, 0x17, 0x49, 0xe1, 0xa3, 0x55, 0x4c, 0x51, 0x2e, 0x1d,
      0xaf, 0xa4, 0x64, 0xd6, 0x64, 0xa2, 0xdb, 0x9e, 0x9a, 0x9d, 0x57, 0x3f,
      0xcb, 0x28, 0x34, 0x4e, 0x47, 0x1c, 0x45, 0x3f, 0x11, 0xf3, 0xb8, 0x52,
      0xf2, 0x15, 0x5b, 0x3e, 0xc5, 0xca, 0xa2, 0x1b, 0x7b, 0x2c, 0xc9, 0x34,
      0xd5, 0x9f, 0xfc, 0x06, 0x43, 0xd8, 0x6c, 0xce, 0xee, 0x3f, 0xc7, 0x18,
      0xbb, 0x37, 0x81, 0xea, 0x75, 0x76, 0xea, 0x4d, 0x5f, 0x9d, 0x90, 0x91,
      0x66, 0x35, 0x6e, 0xf3, 0x9b, 0xa9, 0xb4, 0x8f, 0x84, 0xbd, 0xf1, 0x83,
      0xa4, 0x09, 0x08, 0x3a, 0xc9, 0xd7, 0xb3, 0xfe, 0xa9, 0xd0, 0x72, 0x0e,
      0x9a, 0xc4, 0xfa, 0x8a, 0x6f, 0x0e, 0x65, 0x56, 0x7b, 0x0b, 0xd1, 0x61,
      0x28, 0xe9, 0xcd, 0xe1, 0xc1, 0x8a, 0xba, 0xce, 0x93, 0xe6, 0x29, 0x08,
      0xa8, 0xf7, 0xd4, 0xdb, 0x88, 0xee, 0xfd, 0xe5, 0x55, 0x1f, 0x17, 0xa9,
      0x81, 0x86, 0xc6, 0xdc, 0x5a, 0xcd, 0xa7, 0x37, 0x54, 0xfe, 0xe9, 0x6b,
      0x2d, 0x0e, 0xf2, 0x6d, 0x2f, 0x10, 0x97, 0x07, 0x46, 0x75, 0xf8, 0x82,
      0xaa, 0xe8, 0xfc, 0xd0, 0xd1, 0xa1, 0x39, 0x72, 0x1f, 0x43, 0xb5, 0xff,
      0x6f, 0xa1, 0x17, 0x91, 0x5f, 0x2c, 0x6a, 0x65, 0xd2, 0xd1, 0x8a, 0x49,
      0x65, 0x25, 0xd1, 0xfb, 0x00, 0x47, 0x93, 0x6b, 0xd4, 0x4e, 0x10, 0x4f,
      0xb0, 0xff, 0xe8, 0x5d, 0xef, 0xdf, 0xe4, 0x1c, 0xb8, 0x0d, 0xc5, 0x64,
      0x10, 0xfa, 0xb8, 0x4c, 0xb4, 0x47, 0x0e, 0x8d, 0x41, 0xc6, 0x7e, 0x57,
      0xb1, 0x64, 0x7e, 0xb6, 0x24, 0xd5, 0x95, 0xcf, 0xbc, 0xc4, 0x65, 0xf0,
      0x97, 0xe4, 0x07, 0x82, 0x14, 0x2c, 0xad, 0x61, 0x71, 0x0d, 0x66, 0xda,
      0xa5, 0x56, 0x36, 0x21, 0x2d, 0x69, 0xc4, 0xa1, 0x2a, 0x0b, 0xcb, 0xe3,
      0x52, 0x6a, 0xac, 0x8c, 0xfa, 0xef, 0x2b, 0x81, 0xe5, 0x70, 0x73, 0xee,
      0x1f, 0xfc, 0xb8, 0x7c, 0x6f, 0xe9, 0x93, 0x81, 0xef, 0x08, 0x66, 0x22,
      0xbf, 0x23, 0x34, 0xb9, 0x38, 0x0e, 0xc5, 0xf9, 0xe7, 0x2f, 0x02, 0x58,
      0xcb, 0x1c, 0x9f, 0x23, 0x14, 0xf6, 0x61, 0x33, 0x12, 0xc5, 0xf9, 0x65,
      0xf3, 0x83, 0x23, 0xf2, 0xd8, 0x4b, 0xcd, 0x27, 0xe7, 0x55, 0x3e, 0x36,
      0x34, 0xa3, 0xf2, 0x6e, 0x9d, 0xb3, 0xe6, 0x76, 0x4d, 0xd7, 0x51, 0x91,
      0xdd, 0x29, 0x34, 0xde, 0xaa, 0xed, 0xef, 0x22, 0x4c, 0xee, 0x32, 0x30,
      0x1e, 0xfc, 0xad, 0x23, 0xe9, 0xfa, 0xaf, 0x71, 0x63, 0x4b, 0xf6, 0xe9,
  };

  ec_point initiator_ecdh;
  uint8_t initiator_ecdh_s[ED448_POINT_BYTES] = {
      0x73, 0x58, 0x9d, 0x71, 0x77, 0xac, 0x23, 0x70, 0x07, 0xe4, 0xa4, 0x5c,
      0xf8, 0xcf, 0xb4, 0x96, 0x58, 0x18, 0x11, 0x8f, 0x9e, 0xc4, 0x00, 0x7b,
      0xef, 0xea, 0xba, 0x4f, 0x42, 0xd3, 0xfe, 0x16, 0x6f, 0xe0, 0xd5, 0xc6,
      0x76, 0x7c, 0x4b, 0x72, 0xc7, 0x74, 0xf1, 0x20, 0x7e, 0xf8, 0x00, 0xd4,
      0x43, 0xce, 0x4b, 0x51, 0x51, 0x6a, 0x46, 0x90, 0x00,
  };

  ec_point responder_ecdh;
  uint8_t responder_ecdh_s[ED448_POINT_BYTES] = {
      0xe1, 0x69, 0x32, 0xb4, 0x5d, 0x24, 0x54, 0xd2, 0x4a, 0xf1, 0x17, 0xa0,
      0x3c, 0xb5, 0xcf, 0x12, 0xbc, 0xc5, 0xeb, 0x41, 0x60, 0xe9, 0xdc, 0xb3,
      0xa4, 0xba, 0xaa, 0x46, 0xbb, 0xfe, 0xcd, 0x0d, 0x90, 0x9a, 0xd2, 0x44,
      0x01, 0xf1, 0x48, 0x58, 0x1c, 0x0d, 0xcd, 0xd3, 0xbf, 0x13, 0x17, 0x9b,
      0x1c, 0x6b, 0x13, 0x28, 0xb5, 0x3c, 0xfa, 0xbf, 0x80,
  };

  otrng_client_profile_s initiator_profile;
  uint8_t initiator_profile_s[310] = {
      0x00, 0x00, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02,
      0x00, 0x10, 0x05, 0x72, 0xC1, 0x4C, 0xB1, 0x30, 0x77, 0x44, 0xB9, 0x2F,
      0x38, 0x37, 0xF9, 0x96, 0x39, 0xAB, 0xBB, 0x20, 0xFF, 0xC4, 0x71, 0xD8,
      0x9D, 0x9D, 0x54, 0x53, 0x49, 0xDC, 0x70, 0x0E, 0x01, 0x27, 0x49, 0x1F,
      0x06, 0x13, 0x14, 0xFA, 0xF8, 0x9A, 0x85, 0xC7, 0x07, 0x60, 0xBD, 0x01,
      0x88, 0xA5, 0x66, 0x9D, 0x1A, 0x43, 0x93, 0xF0, 0x83, 0x4B, 0x80, 0x00,
      0x03, 0x00, 0x12, 0x98, 0x97, 0x31, 0xEE, 0xBB, 0x0A, 0x1B, 0xA5, 0xA6,
      0x90, 0x43, 0xC8, 0xC1, 0x25, 0x16, 0xB1, 0x68, 0xBE, 0xA1, 0x23, 0x74,
      0x65, 0x4B, 0x04, 0xE8, 0xB3, 0xD3, 0x85, 0x93, 0xBA, 0x37, 0x0B, 0x07,
      0x1A, 0x4C, 0xBE, 0x3F, 0x20, 0x8E, 0xE1, 0xE2, 0x0E, 0x97, 0x7D, 0x61,
      0xE5, 0x1F, 0xFC, 0xCA, 0x7F, 0x87, 0x15, 0x0C, 0x18, 0xA5, 0xFC, 0x00,
      0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x34, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x4C, 0x2B, 0x42, 0x40, 0x35,
      0xDF, 0x51, 0xC7, 0x0C, 0x6A, 0xA9, 0x3E, 0x99, 0x15, 0x63, 0x32, 0xBA,
      0xC3, 0x19, 0x22, 0x7B, 0x2E, 0x35, 0x54, 0x43, 0xFA, 0xDB, 0xBB, 0xEF,
      0x32, 0x26, 0xAD, 0xE5, 0xE4, 0xD2, 0x45, 0x3A, 0xB2, 0xFE, 0x61, 0x9F,
      0x76, 0x00, 0x02, 0x83, 0x53, 0xEA, 0x78, 0xDA, 0x79, 0x44, 0xDC, 0x6A,
      0x95, 0x1F, 0x80, 0xBC, 0x47, 0x3B, 0x23, 0xD7, 0x7B, 0xD5, 0x78, 0x89,
      0xCA, 0x4C, 0xDB, 0xFF, 0x0E, 0x34, 0xF8, 0x5F, 0x11, 0xD4, 0xF0, 0xFE,
      0xA9, 0x93, 0xDE, 0x5E, 0x3A, 0x25, 0xEE, 0x9D, 0x2C, 0x59, 0x25, 0x5F,
      0xAF, 0xE7, 0x75, 0xC7, 0x0F, 0x6C, 0x93, 0xA6, 0x8B, 0xD2, 0xB7, 0x6C,
      0xA4, 0x6D, 0xCD, 0xB7, 0x10, 0x5A, 0x00, 0x8A, 0x1D, 0x4A, 0x07, 0x00,
  };

  otrng_client_profile_s responder_profile;
  uint8_t responder_profile_s[310] = {
      0x00, 0x00, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x02,
      0x00, 0x10, 0x61, 0xFA, 0x1F, 0x15, 0x35, 0x82, 0xF5, 0xF6, 0x42, 0xF2,
      0x72, 0x02, 0xE9, 0xC2, 0x57, 0x06, 0x1A, 0x7C, 0xB8, 0xC4, 0x79, 0x91,
      0x74, 0xB3, 0xA9, 0xBD, 0x87, 0xA4, 0xF3, 0xB1, 0x87, 0x0F, 0x8C, 0xEE,
      0x9C, 0x09, 0xDC, 0x8E, 0x8B, 0x74, 0x31, 0x0E, 0x80, 0x55, 0x73, 0x9D,
      0x63, 0x43, 0x30, 0xDB, 0xB9, 0x72, 0x6D, 0x48, 0x4E, 0x27, 0x80, 0x00,
      0x03, 0x00, 0x12, 0x06, 0x55, 0x8D, 0xB0, 0x88, 0x77, 0x52, 0x43, 0x38,
      0x55, 0x6A, 0xFE, 0x98, 0x8A, 0x43, 0xFE, 0x9E, 0x12, 0xC2, 0x80, 0x53,
      0x19, 0x4F, 0xF4, 0x5A, 0x8A, 0xC9, 0xDB, 0xD1, 0x52, 0xB5, 0x5C, 0xA5,
      0x0C, 0xFC, 0x80, 0x58, 0xDC, 0x38, 0x92, 0x67, 0xB0, 0xD3, 0xBD, 0x82,
      0xB6, 0x8D, 0xCD, 0x5C, 0xF9, 0x0C, 0x0E, 0x6C, 0x37, 0x3F, 0x8B, 0x80,
      0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x34, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAB, 0xE9, 0xB2, 0x1F, 0x57, 0x3E,
      0x43, 0x65, 0xEB, 0x01, 0x63, 0x43, 0xBD, 0x48, 0x7A, 0x88, 0xB9, 0x9F,
      0x4C, 0xC8, 0x9D, 0x01, 0x1A, 0x61, 0x64, 0x1A, 0x1A, 0x3D, 0xA5, 0xCE,
      0xD7, 0x35, 0xC5, 0x42, 0x1F, 0x87, 0x86, 0x62, 0x84, 0x31, 0xAB, 0x73,
      0x75, 0x93, 0xFA, 0x8F, 0x71, 0xEC, 0x22, 0xFD, 0xD9, 0x51, 0xDE, 0x6E,
      0x63, 0xBE, 0x00, 0x24, 0xDF, 0x2E, 0x3A, 0x7F, 0x12, 0xD5, 0xB9, 0xAB,
      0xCD, 0xB8, 0x28, 0x35, 0x6F, 0x10, 0x17, 0xB0, 0x79, 0x09, 0x7A, 0x20,
      0xC5, 0x24, 0xAD, 0xE3, 0x4F, 0x77, 0xDE, 0x0E, 0x5D, 0x35, 0x19, 0x4C,
      0x69, 0xF5, 0x5E, 0xD5, 0x69, 0xD2, 0x21, 0x6A, 0xA3, 0xE2, 0x26, 0xB9,
      0xB1, 0x2B, 0x73, 0x55, 0x6E, 0x9D, 0xC6, 0x1F, 0x59, 0xE3, 0x1A, 0x00,
  };

  otrng_assert_is_success(otrng_dh_mpi_deserialize(
      &initiator_dh, initiator_dh_s, DH3072_MOD_LEN_BYTES, NULL));

  otrng_assert_is_success(otrng_dh_mpi_deserialize(
      &responder_dh, responder_dh_s, DH3072_MOD_LEN_BYTES, NULL));

  otrng_assert_is_success(
      otrng_ec_point_decode(initiator_ecdh, initiator_ecdh_s));

  otrng_assert_is_success(
      otrng_ec_point_decode(responder_ecdh, responder_ecdh_s));

  otrng_assert_is_success(
      otrng_client_profile_deserialize(&initiator_profile, initiator_profile_s,
                                       sizeof(initiator_profile_s), NULL));

  otrng_assert_is_success(
      otrng_client_profile_deserialize(&responder_profile, responder_profile_s,
                                       sizeof(responder_profile_s), NULL));

  uint8_t *dst = NULL;
  size_t dst_len = 0;
  uint8_t phi[3] = {0, 1, 2};

  const otrng_dake_participant_data_s initiator = {
      .client_profile = &initiator_profile,
      .exp_client_profile = NULL,
      .ecdh = *(initiator_ecdh),
      .dh = initiator_dh,
  };

  const otrng_dake_participant_data_s responder = {
      .client_profile = &responder_profile,
      .exp_client_profile = NULL,
      .ecdh = *(responder_ecdh),
      .dh = responder_dh,
  };

  otrng_assert_is_success(build_interactive_rsign_tag(
      &dst, &dst_len, 'i', &initiator, &responder, phi, sizeof(phi)));

  otrng_assert(dst_len == 1083);
  otrng_assert_cmpmem(dst, expected_t1, dst_len);

  otrng_free(dst);

  otrng_assert_is_success(build_interactive_rsign_tag(
      &dst, &dst_len, 'r', &initiator, &responder, phi, sizeof(phi)));

  otrng_assert(dst_len == 1083);
  otrng_assert_cmpmem(dst, expected_t2, dst_len);

  otrng_free(dst);

  otrng_dh_mpi_release(initiator_dh);
  otrng_dh_mpi_release(responder_dh);
  otrng_client_profile_destroy(&initiator_profile);
  otrng_client_profile_destroy(&responder_profile);
}

void units_dake_add_tests(void) {
  g_test_add_func("/dake/build_interactive_rsign_tag",
                  test_build_interactive_rsign_tag);
}

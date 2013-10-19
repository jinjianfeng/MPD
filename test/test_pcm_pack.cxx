/*
 * Copyright (C) 2003-2013 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "test_pcm_all.hxx"
#include "test_pcm_util.hxx"
#include "pcm/PcmPack.hxx"
#include "system/ByteOrder.hxx"

void
PcmPackTest::TestPack24()
{
	constexpr unsigned N = 256;
	const auto src = TestDataBuffer<int32_t, N>(RandomInt24());

	uint8_t dest[N * 3];
	pcm_pack_24(dest, src.begin(), src.end());

	for (unsigned i = 0; i < N; ++i) {
		int32_t d;
		if (IsBigEndian())
			d = (dest[i * 3] << 16) | (dest[i * 3 + 1] << 8)
				| dest[i * 3 + 2];
		else
			d = (dest[i * 3 + 2] << 16) | (dest[i * 3 + 1] << 8)
				| dest[i * 3];
		if (d & 0x800000)
			d |= 0xff000000;

		CPPUNIT_ASSERT_EQUAL(d, src[i]);
	}
}

void
PcmPackTest::TestUnpack24()
{
	constexpr unsigned N = 256;
	const auto src = TestDataBuffer<uint8_t, N * 3>();

	int32_t dest[N];
	pcm_unpack_24(dest, src.begin(), src.end());

	for (unsigned i = 0; i < N; ++i) {
		int32_t s;
		if (IsBigEndian())
			s = (src[i * 3] << 16) | (src[i * 3 + 1] << 8)
				| src[i * 3 + 2];
		else
			s = (src[i * 3 + 2] << 16) | (src[i * 3 + 1] << 8)
				| src[i * 3];
		if (s & 0x800000)
			s |= 0xff000000;

		CPPUNIT_ASSERT_EQUAL(s, dest[i]);
	}
}

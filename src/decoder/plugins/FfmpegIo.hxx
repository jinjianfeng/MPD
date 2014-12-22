/*
 * Copyright (C) 2003-2014 The Music Player Daemon Project
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

#ifndef MPD_FFMPEG_IO_HXX
#define MPD_FFMPEG_IO_HXX

#include "check.h"

extern "C" {
#include "libavformat/avio.h"
}

#include <stdint.h>

class InputStream;
struct Decoder;

struct AvioStream {
	Decoder *const decoder;
	InputStream &input;

	AVIOContext *io;

	uint8_t buffer[8192];

	AvioStream(Decoder *_decoder, InputStream &_input)
		:decoder(_decoder), input(_input), io(nullptr) {}

	~AvioStream();

	bool Open();
};

#endif
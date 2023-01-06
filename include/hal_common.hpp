/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef BITFIELDSET_HAL_COMMON_HPP
#define BITFIELDSET_HAL_COMMON_HPP

#include <cstdint>
#include <cstddef>

namespace hal {

template <typename T = uint32_t>
constexpr inline T bit(size_t pos)
{
	return static_cast<T>(1) << pos;
}

enum class AccessType {
	NONE		= 0,
	READ_ONLY	= bit(0),
	WRITE_ONLY	= bit(1),
	READ_WRITE	= READ_ONLY | WRITE_ONLY,
};

}

#endif /* BITFIELDSET_HAL_COMMON_HPP */

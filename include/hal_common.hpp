/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef BITFIELDSET_HAL_COMMON_HPP
#define BITFIELDSET_HAL_COMMON_HPP

#include <cstdint>
#include <cstddef>

namespace hal {

using MachineWordType = uint32_t;

template <typename T = MachineWordType>
constexpr inline T bit(size_t pos)
{
	return static_cast<T>(static_cast<T>(1) << pos);
}

enum class AccessType {
	NONE		= 0,
	READ_ONLY	= bit(0),
	WRITE_ONLY	= bit(1),
	READ_WRITE	= READ_ONLY | WRITE_ONLY,
};

consteval void consteval_assert(bool cond, [[maybe_unused]] const char *str)
{
	cond /= cond;	/* consteval assertion failed if error is here */
}

}

#endif /* BITFIELDSET_HAL_COMMON_HPP */

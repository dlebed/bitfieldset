/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef BITFIELDSET_HAL_COMMON_HPP
#define BITFIELDSET_HAL_COMMON_HPP

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace hal {

constexpr bool kDebugEnable = DEBUG_EN;

using MachineWordType = uint32_t;

template <typename T = MachineWordType>
constexpr T bit(size_t pos)
{
	return static_cast<T>(static_cast<T>(1) << pos);
}

enum class AccessType {
	NONE		= 0,
	READ_ONLY	= bit(0),
	WRITE_ONLY	= bit(1),
	READ_WRITE	= READ_ONLY | WRITE_ONLY,
};

template<typename... Ts>
constexpr void constexpr_assert(bool cond, [[maybe_unused]] const char *str, [[maybe_unused]] Ts...)
{
	if (std::is_constant_evaluated()) {
		cond /= cond;	/* assertion failed if you see divide by 0 error */
	} else if (kDebugEnable) {
		/* TODO: runtime assert */
	}
}

template <typename T = MachineWordType>
constexpr T bitMask(uint8_t lsb, uint8_t msb)
{
	constexpr size_t wordBits = std::numeric_limits<T>::digits;
	const size_t bitPos = msb - lsb;
	T mask;

	constexpr_assert(msb >= lsb, "invalid input: msb < lsb");
	constexpr_assert(msb < wordBits, "msb is out of bounds");

	mask = bit<T>(bitPos);
	mask |= mask - 1;

	mask = static_cast<T>(mask << lsb);

	return mask;
}

}

#endif /* BITFIELDSET_HAL_COMMON_HPP */

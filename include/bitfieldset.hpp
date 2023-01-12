/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

/**
 * Bit field set manipulation class
 *
 * Provides fast and portable bit field manipulation API useful in embedded development,
 * for example to access HW-defined structures in memory (descriptors, etc) or HW registers.
 * Class is designed to provide zero runtime cost abstraction layer and uses
 * compile time calculations to compute bitmasks and check for bit field definitions sanity
 */

#ifndef BITFIELDSET_BITFIELDSET_HPP
#define BITFIELDSET_BITFIELDSET_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <cassert>
#include <type_traits>

#include "hal_common.hpp"

namespace hal {

inline constexpr size_t BITFIELD_OFFSET_UNDEFINED = std::numeric_limits<size_t>::max();

/**
 * Bit field layout definition structure
 *
 * Main BitFieldSet class uses duck typing approach to identify the bit field set layout defined
 * as an array of BitField objects.
 * The only required field is #word (could be set though #byte_offset), other fields are optional
 * #TWord defines the size of machine word and defined the width of CPU memory access
 *
 * @tparam TWord underlying bit field type (word) that defines layout and CPU access
 */
template <typename TWord>
struct BitField {
	/* Layout */
	/** alternative to #word field definition - bit field word offset in bytes */
	size_t		byteOffset = BITFIELD_OFFSET_UNDEFINED;
	/** word index - required field, used to index HW words in accessors */
	size_t		word = byteOffset / sizeof(TWord);
	/** least significant bit */
	uint8_t		lsb;
	/** most significant bit, by default is set to maximum word width */
	uint8_t		msb = std::numeric_limits<TWord>::digits - 1;
	/** offset of the field in compound value */
	uint8_t		compoundOffset;

	/* Value range */
	/** default value (e.g. POR value for register) */
	TWord		def;
	/** minimum allowed value */
	TWord		min;
	/** maximum allowed value */
	TWord		max;

	/** access type allowed for bit field (RW/RO/WO) */
	AccessType	access = AccessType::READ_WRITE;
	/** bit field overlap with others (compile time check) */
	bool		mayOverlap = false;

	static_assert(std::is_unsigned<TWord>::value,
				  "Underlying bit field type should be unsigned");
};


template <typename TBitFieldDef>
class BitFieldSetUtil {
public:
	using TWord = typename TBitFieldDef::WordType;

	/* Define class as a singleton */
	BitFieldSetUtil() = default;
	~BitFieldSetUtil() = default;
	BitFieldSetUtil(const BitFieldSetUtil&) = delete;
	BitFieldSetUtil& operator=(const BitFieldSetUtil&) = delete;

	static consteval TWord bitMask(uint8_t lsb, uint8_t msb)
	{
		TWord mask = 0;

		consteval_assert(msb >= lsb, "invalid input: msb < lsb");
		consteval_assert(msb < wordBits, "msb is out of bounds");

		for (size_t i = lsb; i <= msb; i++) {
			mask |= bit<TWord>(i);
		}

		return mask;
	}

private:
	static constexpr size_t wordBits = std::numeric_limits<TWord>::digits;
};

}

#endif /* BITFIELDSET_BITFIELDSET_HPP */

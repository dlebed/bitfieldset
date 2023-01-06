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
	size_t		byte_offset = BITFIELD_OFFSET_UNDEFINED;
	/** word index - required field, used to index HW words in accessors */
	size_t		word = byte_offset / sizeof(TWord);
	/** least significant bit */
	uint8_t		lsb;
	/** most significant bit, by default is set to maximum word width */
	uint8_t		msb = std::numeric_limits<TWord>::digits - 1;
	/** offset of the field in compound value */
	uint8_t		compound_offset;

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
	bool		may_overlap = false;
};



}

#endif /* BITFIELDSET_BITFIELDSET_HPP */

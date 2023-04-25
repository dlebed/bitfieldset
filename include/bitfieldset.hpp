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
#include <algorithm>

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

private:
	static constexpr size_t wordBits = std::numeric_limits<TWord>::digits;
};

template <typename TBitFieldDef>
class BitFieldSet : public TBitFieldDef {
public:
	using TWord = typename TBitFieldDef::WordType;

	template <typename TBitFieldDef::FIELDS field>
	constexpr void set(TWord value)
	{
		const size_t idx = wordIdx(field);
		const auto &entry = TBitFieldDef::layout[field];
		const TWord mask = bitMask<TWord>(entry.lsb, entry.msb);
		TWord &word = raw[idx];

		static_assert(entry.access != AccessType::READ_ONLY, "writing to RO field");

		word &= ~mask;
		word |= (value << entry.lsb) & mask;
	}

	template <typename TBitFieldDef::FIELDS field>
	constexpr void set(TWord value) volatile
	{
		const size_t idx = wordIdx(field);
		const auto &entry = TBitFieldDef::layout[field];
		const TWord mask = bitMask<TWord>(entry.lsb, entry.msb);
		volatile TWord &word = raw[idx];

		static_assert(entry.access != AccessType::READ_ONLY, "writing to RO field");

		word &= ~mask;
		word |= (value << entry.lsb) & mask;
	}

	template <typename TBitFieldDef::FIELDS field>
	constexpr TWord get() const
	{
		const size_t idx = wordIdx(field);
		const auto &entry = TBitFieldDef::layout[field];
		const TWord mask = bitMask<TWord>(entry.lsb, entry.msb);
		const TWord &word = raw[idx];

		static_assert(entry.access != AccessType::WRITE_ONLY, "reading from WO field");

		return (word & mask) >> entry.lsb;
	}

	template <typename TBitFieldDef::FIELDS field>
	constexpr TWord get() const volatile
	{
		const size_t idx = wordIdx(field);
		const auto &entry = TBitFieldDef::layout[field];
		const TWord mask = bitMask<TWord>(entry.lsb, entry.msb);
		const volatile TWord &word = raw[idx];

		static_assert(entry.access != AccessType::WRITE_ONLY, "reading from WO field");

		return (word & mask) >> entry.lsb;
	}

	constexpr void resetAll()
	{
		std::fill_n(raw, TBitFieldDef::wordCount, 0);
	}

	constexpr void resetAll() volatile
	{
		std::fill_n(raw, TBitFieldDef::wordCount, 0);
	}

private:
	using Util = BitFieldSetUtil<TBitFieldDef>;

	static constexpr size_t wordIdx(typename TBitFieldDef::FIELDS field)
	{
		return TBitFieldDef::layout[static_cast<size_t>(field)].word;
	}

	TWord raw[TBitFieldDef::wordCount];
};

}

#endif /* BITFIELDSET_BITFIELDSET_HPP */

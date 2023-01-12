/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <gtest/gtest.h>

#include <bitfieldset.hpp>

using namespace hal;

template <typename TWord>
struct TestBitFieldFlexDef {
	/* bits helper defined only to make class generic for testing */
	static constexpr size_t bits = std::numeric_limits<TWord>::digits;

	enum FIELDS {
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,

		/* keep last */
		FIELD_COUNT
	};

	using WordType = TWord;

	static constexpr size_t fieldCount = FIELD_COUNT;
	static constexpr size_t wordCount = 5;

	__extension__
	static constexpr struct BitField<WordType> layout[fieldCount] =
	{
		[F1]	= { .word = 0,	.lsb = 0,				.msb = 2	},
		[F2]	= { .word = 0,	.lsb = 3,				.msb = 4	},
		[F3]	= { .word = 0,	.lsb = 4,				.msb = bits - 1	},
		[F4]	= { .word = 1,	.lsb = 0,				.msb = bits / 2	},
		[F5]	= { .word = 1,	.lsb = bits / 2 + 1,	.msb = bits - 1	},
		[F6]	= { .word = 2,	.lsb = 0,				.msb = bits - 1	},
	};
};

template <typename T>
void utilBitMaskTest()
{
	using TWord = typename T::WordType;
	constexpr size_t bits = std::numeric_limits<TWord>::digits;

	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 0), 0x01);
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(bits - 1, bits - 1), bit<TWord>(bits - 1));
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, bits - 1), static_cast<TWord>(-1));
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 7), 0xFF);
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 3), 0xF);
}

TEST(BitFieldSetTest, UtilBitMaskTest)
{
	utilBitMaskTest<TestBitFieldFlexDef<uint8_t>>();
	utilBitMaskTest<TestBitFieldFlexDef<uint16_t>>();
	utilBitMaskTest<TestBitFieldFlexDef<uint32_t>>();
	utilBitMaskTest<TestBitFieldFlexDef<uint64_t>>();
}

TEST(BitFieldSetTest, BasicTest)
{
	EXPECT_EQ(2 * 2, 4);
}
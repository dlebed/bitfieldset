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
		[F1]	= { .word = 0,	.lsb = 0,				.msb = 2		},
		[F2]	= { .word = 0,	.lsb = 3,				.msb = 4		},
		[F3]	= { .word = 0,	.lsb = 5,				.msb = bits - 1	},
		[F4]	= { .word = 1,	.lsb = 0,				.msb = bits / 2	},
		[F5]	= { .word = 1,	.lsb = bits / 2 + 1,	.msb = bits - 1	},
		[F6]	= { .word = 2,	.lsb = 0,				.msb = bits - 1	},
	};
};

class TBF : public BitFieldSet<TestBitFieldFlexDef<uint32_t>> { };

static_assert(std::is_trivial<TBF>::value, "BitFieldSet is not a trivial class");
static_assert(std::is_standard_layout<TBF>::value, "BitFieldSet is not a standard layout class");

template <typename T>
void utilBitMaskTestConst()
{
	using TWord = typename T::WordType;
	constexpr size_t bits = std::numeric_limits<TWord>::digits;

	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 0), 0x01);
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(bits - 1, bits - 1), bit<TWord>(bits - 1));
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, bits - 1), static_cast<TWord>(-1));
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 7), 0xFF);
	EXPECT_EQ(BitFieldSetUtil<T>::bitMask(0, 3), 0xF);
}

template <typename T>
T bitMaskNaive(size_t lsb, size_t msb)
{
	T mask = 0;

	for (size_t i = lsb; i <= msb; i++) {
		mask |= bit<T>(i);
	}

	return mask;
}

template <typename T>
void utilBitMaskTestRuntime()
{
	using TWord = typename T::WordType;
	constexpr size_t bits = std::numeric_limits<TWord>::digits;

	for (uint8_t lsb = 0; lsb < bits; lsb++) {
		for (uint8_t msb = lsb; msb < bits; msb++) {
			EXPECT_EQ(BitFieldSetUtil<T>::bitMask(lsb, msb),
					  bitMaskNaive<TWord>(lsb, msb));
		}
	}
}

TEST(BitFieldSetTest, UtilBitMaskTestConst)
{
	utilBitMaskTestConst<TestBitFieldFlexDef<uint8_t>>();
	utilBitMaskTestConst<TestBitFieldFlexDef<uint16_t>>();
	utilBitMaskTestConst<TestBitFieldFlexDef<uint32_t>>();
	utilBitMaskTestConst<TestBitFieldFlexDef<uint64_t>>();
}

TEST(BitFieldSetTest, UtilBitMaskTestRuntime)
{
	utilBitMaskTestRuntime<TestBitFieldFlexDef<uint8_t>>();
	utilBitMaskTestRuntime<TestBitFieldFlexDef<uint16_t>>();
	utilBitMaskTestRuntime<TestBitFieldFlexDef<uint32_t>>();
	utilBitMaskTestRuntime<TestBitFieldFlexDef<uint64_t>>();
}

consteval uint32_t testConstexpr()
{
	TBF tb;

	tb.resetAll();

	tb.set<TBF::F1>(2);
	tb.set<TBF::F2>(3);

	return tb.get<TBF::F1>() + tb.get<TBF::F2>();
}

TEST(BitFieldSetTest, BasicConstexprTest)
{
	EXPECT_EQ(testConstexpr(), 5);
}

TEST(BitFieldSetTest, BasicTest)
{
	TBF tb;

	tb.resetAll();

	tb.set<TBF::F1>(3);
	tb.set<TBF::F2>(2);

	EXPECT_EQ(tb.get<TBF::F1>(), 3);
	EXPECT_EQ(tb.get<TBF::F2>(), 2);
}

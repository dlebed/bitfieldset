/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef BITFIELDSET_ARCH_CSR_H
#define BITFIELDSET_ARCH_CSR_H

#include <cstdint>
#include <cstddef>
#include <utility>
#include <array>
#include "rv_types.hpp"

namespace rv {

enum class csr : uint16_t {
	/* User mode restricted view of mstatus */
	ustatus                         = 0x000,
	/* Floating-Point Accrued Exceptions */
	fflags                          = 0x001,
	/* Floating-Point Dynamic Rounding Mode */
	frm                             = 0x002,
	/* Floating-Point Control and Status */
	fcsr                            = 0x003,
	/* User Interrupt Enable */
	uie                             = 0x004,
	/* User Trap Vector Base Address */
	utvec                           = 0x005,
	utvt                            = 0x007,
	vstart                          = 0x008,
	vxsat                           = 0x009,
	vxrm                            = 0x00a,
	/* User Mode Scratch Register */
	uscratch                        = 0x040,
	/* User Exception Program Counter */
	uepc                            = 0x041,
	/* User Exception Cause */
	ucause                          = 0x042,
	/* User Trap Value */
	utval                           = 0x043,
	/* User Interrupt Pending */
	uip                             = 0x044,
	unxti                           = 0x045,
	uintstatus                      = 0x046,
	uscratchcsw                     = 0x048,
	uscratchcswl                    = 0x049,
	/* Supervisor Status */
	sstatus                         = 0x100,
	/* Supervisor Exception Delegation */
	sedeleg                         = 0x102,
	/* Supervisor Interrupt Delegation */
	sideleg                         = 0x103,
	/* Supervisor Interrupt Enable */
	sie                             = 0x104,
	/* Supervisor Trap Vector Base Address */
	stvec                           = 0x105,
	/* Counter Enable */
	scounteren                      = 0x106,
	stvt                            = 0x107,
	/* Supervisor environment configuration register */
	senvcfg                         = 0x10a,
	/* Supervisor Mode Scratch Register */
	sscratch                        = 0x140,
	/* Supervisor Exception Program Counter */
	sepc                            = 0x141,
	/* Supervisor Exception Cause */
	scause                          = 0x142,
	/* Supervisor bad address or instruction */
	stval                           = 0x143,
	/* Supervisor Interrupt Pending */
	sip                             = 0x144,
	snxti                           = 0x145,
	sintstatus                      = 0x146,
	sscratchcsw                     = 0x148,
	sscratchcswl                    = 0x149,
	/* Supervisor address translation and protection */
	satp                            = 0x180,
	bsstatus                        = 0x200,
	bsie                            = 0x204,
	bstvec                          = 0x205,
	bsscratch                       = 0x240,
	bsepc                           = 0x241,
	bscause                         = 0x242,
	bstval                          = 0x243,
	bsip                            = 0x244,
	bsatp                           = 0x280,
	/* Machine Status */
	mstatus                         = 0x300,
	/* Machine ISA */
	misa                            = 0x301,
	/* Machine Exception Delegation */
	medeleg                         = 0x302,
	/* Machine Interrupt Delegation */
	mideleg                         = 0x303,
	/* Machine Interrupt Enable */
	mie                             = 0x304,
	/* Machine Trap Vector Base Address */
	mtvec                           = 0x305,
	/* Counter Enable */
	mcounteren                      = 0x306,
	mtvt                            = 0x307,
	/* Machine environment configuration register */
	menvcfg                         = 0x30a,
	/* Additional machine status register, RV32 only */
	mstatush                        = 0x310,
	/* Additional machine env. conf. register, RV32 only */
	menvcfgh                        = 0x31a,
	/* Machine Counter Inhibit */
	mcountinhibit                   = 0x320,
	/* Event Counter Event Select */
	mhpmevent3                      = 0x323,
	/* Machine performance-monitoring event selector */
	mhpmevent4                      = 0x324,
	mhpmevent5                      = 0x325,
	mhpmevent6                      = 0x326,
	mhpmevent7                      = 0x327,
	mhpmevent8                      = 0x328,
	mhpmevent9                      = 0x329,
	mhpmevent10                     = 0x32a,
	mhpmevent11                     = 0x32b,
	mhpmevent12                     = 0x32c,
	mhpmevent13                     = 0x32d,
	mhpmevent14                     = 0x32e,
	mhpmevent15                     = 0x32f,
	mhpmevent16                     = 0x330,
	mhpmevent17                     = 0x331,
	mhpmevent18                     = 0x332,
	mhpmevent19                     = 0x333,
	mhpmevent20                     = 0x334,
	mhpmevent21                     = 0x335,
	mhpmevent22                     = 0x336,
	mhpmevent23                     = 0x337,
	mhpmevent24                     = 0x338,
	mhpmevent25                     = 0x339,
	mhpmevent26                     = 0x33a,
	mhpmevent27                     = 0x33b,
	mhpmevent28                     = 0x33c,
	mhpmevent29                     = 0x33d,
	mhpmevent30                     = 0x33e,
	/* Machine performance-monitoring event selector */
	mhpmevent31                     = 0x33f,
	/* Machine Mode Scratch Register */
	mscratch                        = 0x340,
	/* Machine Exception Program Counter */
	mepc                            = 0x341,
	/* Machine Exception Cause */
	mcause                          = 0x342,
	/* Machine Trap Value */
	mtval                           = 0x343,
	/* Machine Interrupt Pending */
	mip                             = 0x344,
	mnxti                           = 0x345,
	mintstatus                      = 0x346,
	mscratchcsw                     = 0x348,
	mscratchcswl                    = 0x349,
	/* Machine trap instruction (transformed) */
	mtinst                          = 0x34a,
	/* Machine bad guest physical address */
	mtval2                          = 0x34b,
	/* Base register */
	mbase                           = 0x380,
	/* Bound register */
	mbound                          = 0x381,
	/* Instruction base register */
	mibase                          = 0x382,
	/* Instruction bound register */
	mibound                         = 0x383,
	/* Data base register */
	mdbase                          = 0x384,
	/* Data bound register */
	mdbound                         = 0x385,
	/* Physical memory protection configuration */
	pmpcfg0                         = 0x3a0,
	/* Physical memory protection configuration, RV32 only */
	pmpcfg1                         = 0x3a1,
	/* Physical memory protection configuration */
	pmpcfg2                         = 0x3a2,
	/* Physical memory protection configuration, RV32 only */
	pmpcfg3                         = 0x3a3,
	/* Physical memory protection configuration */
	pmpcfg14                        = 0x3ae,
	/* Physical memory protection configuration, RV32 only */
	pmpcfg15                        = 0x3af,
	/* Physical memory protection address register */
	pmpaddr0                        = 0x3b0,
	/* Physical memory protection address register */
	pmpaddr1                        = 0x3b1,
	pmpaddr2                        = 0x3b2,
	pmpaddr3                        = 0x3b3,
	pmpaddr4                        = 0x3b4,
	pmpaddr5                        = 0x3b5,
	pmpaddr6                        = 0x3b6,
	pmpaddr7                        = 0x3b7,
	pmpaddr8                        = 0x3b8,
	pmpaddr9                        = 0x3b9,
	pmpaddr10                       = 0x3ba,
	pmpaddr11                       = 0x3bb,
	pmpaddr12                       = 0x3bc,
	pmpaddr13                       = 0x3bd,
	pmpaddr14                       = 0x3be,
	/* Physical memory protection address register */
	pmpaddr15                       = 0x3bf,
	/* Physical memory protection address register */
	pmpaddr63                       = 0x3ef,
	/* Supervisor-mode context register */
	scontext                        = 0x5a8,
	/* Hypervisor status register */
	hstatus                         = 0x600,
	/* Hypervisor exception delegation register */
	hedeleg                         = 0x602,
	/* Hypervisor interrupt delegation register */
	hideleg                         = 0x603,
	/* Hypervisor interrupt-enable register */
	hie                             = 0x604,
	/* Delta for VS/VU-mode timer */
	htimedelta                      = 0x605,
	/* Hypervisor counter enable */
	hcounteren                      = 0x606,
	/* Hypervisor guest external interrupt-enable register */
	hgeie                           = 0x607,
	/* Hypervisor environment configuration register */
	henvcfg                         = 0x60a,
	/* Upper 32 bits of  htimedelta, RV32I only */
	htimedeltah                     = 0x615,
	/* Additional hypervisor env. conf. register, RV32 only */
	henvcfgh                        = 0x61a,
	/* Hypervisor bad guest physical address */
	htval                           = 0x643,
	/* Hypervisor interrupt pending */
	hip                             = 0x644,
	/* Hypervisor virtual interrupt pending */
	hvip                            = 0x645,
	/* Hypervisor trap instruction (transformed) */
	htinst                          = 0x64a,
	/* Hypervisor guest address translation and protection */
	hgatp                           = 0x680,
	/* Hypervisor-mode context register */
	hcontext                        = 0x6a8,
	/* Machine security configuration register */
	mseccfg                         = 0x747,
	/* Additional machine security conf. register, RV32 only */
	mseccfgh                        = 0x757,
	/* Debug/Trace trigger register select */
	tselect                         = 0x7a0,
	/* First Debug/Trace trigger data register */
	tdata1                          = 0x7a1,
	/* Second Debug/Trace trigger data register */
	tdata2                          = 0x7a2,
	/* Third Debug/Trace trigger data register */
	tdata3                          = 0x7a3,
	/* Machine-mode context register */
	mcontext                        = 0x7a8,
	/* Debug control and status register */
	dcsr                            = 0x7b0,
	/* Debug PC */
	dpc                             = 0x7b1,
	dscratch                        = 0x7b2,
	/* Debug scratch register 1 */
	dscratch1                       = 0x7b3,
	/* Clock Cycles Executed Counter */
	mcycle                          = 0xb00,
	/* Number of Instructions Retired Counter */
	minstret                        = 0xb02,
	/* Event Counters */
	mhpmcounter3                    = 0xb03,
	/* Machine performance-monitoring counter */
	mhpmcounter4                    = 0xb04,
	mhpmcounter5                    = 0xb05,
	mhpmcounter6                    = 0xb06,
	mhpmcounter7                    = 0xb07,
	mhpmcounter8                    = 0xb08,
	mhpmcounter9                    = 0xb09,
	mhpmcounter10                   = 0xb0a,
	mhpmcounter11                   = 0xb0b,
	mhpmcounter12                   = 0xb0c,
	mhpmcounter13                   = 0xb0d,
	mhpmcounter14                   = 0xb0e,
	mhpmcounter15                   = 0xb0f,
	mhpmcounter16                   = 0xb10,
	mhpmcounter17                   = 0xb11,
	mhpmcounter18                   = 0xb12,
	mhpmcounter19                   = 0xb13,
	mhpmcounter20                   = 0xb14,
	mhpmcounter21                   = 0xb15,
	mhpmcounter22                   = 0xb16,
	mhpmcounter23                   = 0xb17,
	mhpmcounter24                   = 0xb18,
	mhpmcounter25                   = 0xb19,
	mhpmcounter26                   = 0xb1a,
	mhpmcounter27                   = 0xb1b,
	mhpmcounter28                   = 0xb1c,
	mhpmcounter29                   = 0xb1d,
	mhpmcounter30                   = 0xb1e,
	/* Machine performance-monitoring counter */
	mhpmcounter31                   = 0xb1f,
	/* Upper 32 bits of  mcycle, RV32I only */
	mcycleh                         = 0xb80,
	/* Upper 32 bits of  minstret, RV32I only */
	minstreth                       = 0xb82,
	/* Upper 32 bits of  mhpmcounter3, RV32I only */
	mhpmcounter3h                   = 0xb83,
	/* Upper 32 bits of  mhpmcounter4, RV32I only */
	mhpmcounter4h                   = 0xb84,
	mhpmcounter5h                   = 0xb85,
	mhpmcounter6h                   = 0xb86,
	mhpmcounter7h                   = 0xb87,
	mhpmcounter8h                   = 0xb88,
	mhpmcounter9h                   = 0xb89,
	mhpmcounter10h                  = 0xb8a,
	mhpmcounter11h                  = 0xb8b,
	mhpmcounter12h                  = 0xb8c,
	mhpmcounter13h                  = 0xb8d,
	mhpmcounter14h                  = 0xb8e,
	mhpmcounter15h                  = 0xb8f,
	mhpmcounter16h                  = 0xb90,
	mhpmcounter17h                  = 0xb91,
	mhpmcounter18h                  = 0xb92,
	mhpmcounter19h                  = 0xb93,
	mhpmcounter20h                  = 0xb94,
	mhpmcounter21h                  = 0xb95,
	mhpmcounter22h                  = 0xb96,
	mhpmcounter23h                  = 0xb97,
	mhpmcounter24h                  = 0xb98,
	mhpmcounter25h                  = 0xb99,
	mhpmcounter26h                  = 0xb9a,
	mhpmcounter27h                  = 0xb9b,
	mhpmcounter28h                  = 0xb9c,
	mhpmcounter29h                  = 0xb9d,
	mhpmcounter30h                  = 0xb9e,
	/* Upper 32 bits of  mhpmcounter31, RV32I only */
	mhpmcounter31h                  = 0xb9f,
	/* Cycle counter for RDCYCLE instruction */
	cycle                           = 0xc00,
	/* Timer for RDTIME instruction */
	time                            = 0xc01,
	/* Instructions-retired counter for RDINSTRET instruction */
	instret                         = 0xc02,
	/* Performance-monitoring counter */
	hpmcounter3                     = 0xc03,
	/* Performance-monitoring counter */
	hpmcounter4                     = 0xc04,
	hpmcounter5                     = 0xc05,
	hpmcounter6                     = 0xc06,
	hpmcounter7                     = 0xc07,
	hpmcounter8                     = 0xc08,
	hpmcounter9                     = 0xc09,
	hpmcounter10                    = 0xc0a,
	hpmcounter11                    = 0xc0b,
	hpmcounter12                    = 0xc0c,
	hpmcounter13                    = 0xc0d,
	hpmcounter14                    = 0xc0e,
	hpmcounter15                    = 0xc0f,
	hpmcounter16                    = 0xc10,
	hpmcounter17                    = 0xc11,
	hpmcounter18                    = 0xc12,
	hpmcounter19                    = 0xc13,
	hpmcounter20                    = 0xc14,
	hpmcounter21                    = 0xc15,
	hpmcounter22                    = 0xc16,
	hpmcounter23                    = 0xc17,
	hpmcounter24                    = 0xc18,
	hpmcounter25                    = 0xc19,
	hpmcounter26                    = 0xc1a,
	hpmcounter27                    = 0xc1b,
	hpmcounter28                    = 0xc1c,
	hpmcounter29                    = 0xc1d,
	hpmcounter30                    = 0xc1e,
	/* Performance-monitoring counter */
	hpmcounter31                    = 0xc1f,
	vl                              = 0xc20,
	vtype                           = 0xc21,
	/* Upper 32 bits of  cycle, RV32I only */
	cycleh                          = 0xc80,
	/* Upper 32 bits of  time, RV32I only */
	timeh                           = 0xc81,
	/* Upper 32 bits of  instret, RV32I only */
	instreth                        = 0xc82,
	/* Upper 32 bits of  hpmcounter3, RV32I only */
	hpmcounter3h                    = 0xc83,
	/* Upper 32 bits of  hpmcounter4, RV32I only */
	hpmcounter4h                    = 0xc84,
	hpmcounter5h                    = 0xc85,
	hpmcounter6h                    = 0xc86,
	hpmcounter7h                    = 0xc87,
	hpmcounter8h                    = 0xc88,
	hpmcounter9h                    = 0xc89,
	hpmcounter10h                   = 0xc8a,
	hpmcounter11h                   = 0xc8b,
	hpmcounter12h                   = 0xc8c,
	hpmcounter13h                   = 0xc8d,
	hpmcounter14h                   = 0xc8e,
	hpmcounter15h                   = 0xc8f,
	hpmcounter16h                   = 0xc90,
	hpmcounter17h                   = 0xc91,
	hpmcounter18h                   = 0xc92,
	hpmcounter19h                   = 0xc93,
	hpmcounter20h                   = 0xc94,
	hpmcounter21h                   = 0xc95,
	hpmcounter22h                   = 0xc96,
	hpmcounter23h                   = 0xc97,
	hpmcounter24h                   = 0xc98,
	hpmcounter25h                   = 0xc99,
	hpmcounter26h                   = 0xc9a,
	hpmcounter27h                   = 0xc9b,
	hpmcounter28h                   = 0xc9c,
	hpmcounter29h                   = 0xc9d,
	hpmcounter30h                   = 0xc9e,
	/* Upper 32 bits of  hpmcounter31, RV32I only */
	hpmcounter31h                   = 0xc9f,
	/* Hypervisor guest external interrupt pending */
	hgeip                           = 0xe12,
	/* Machine Vendor ID */
	mvendorid                       = 0xf11,
	/* Machine Architecture ID */
	marchid                         = 0xf12,
	/* Machine Implementation ID */
	mimpid                          = 0xf13,
	/* Hardware Thread ID */
	mhartid                         = 0xf14,
	/* Pointer to configuration data structure */
	mconfigptr                      = 0xf15,
};

template <csr reg>
inline uxlen_t csr_read()
{
	constexpr size_t idx = static_cast<size_t>(reg);
	uxlen_t res;

	asm volatile("csrr %[res], %[idx]"
				: [res] "=r" (res)		/* output */
				: [idx] "i" (idx)		/* input */
				:						/* clobbers: none */);

	return res;
}

template <csr reg>
inline void csr_write(uxlen_t value)
{
	constexpr size_t idx = static_cast<size_t>(reg);

	asm volatile("csrw %[idx], %[val]"
				: 						/* output */
				: [val] "r" (value),
				  [idx] "i" (idx)		/* input */
				:						/* clobbers: none */);
}

namespace helpers {

#ifdef CONFIG_RV_CSR_INDEXED_ASM

#define CSR_INDEXED_ASM(STMT) \
	"lla %[jmp_dst], 1						\n"	\
	"add %[jmp_dst], %[jmp_dst], %[index]	\n"	\
	"jr %[jmp_dst]							\n"	\
	".option push							\n"	\
	".option norvc							\n"	\
	"1:;									\n"	\
	".set i, 0								\n"	\
	".rept %[csr_count]						\n"	\
	".set reg_idx, (%[start] + i)			\n"	\
	STMT 								   "\n"	\
	"j 2f									\n"	\
	".set i, i + 1							\n"	\
	".endr									\n"	\
	".option pop							\n"	\
	"2:;									\n"

template <csr start, csr end>
uxlen_t csr_read_indexed(size_t idx)
{
	constexpr size_t start_idx = static_cast<size_t>(start);
	constexpr size_t end_idx = static_cast<size_t>(end);
	constexpr size_t csr_count = end_idx - start_idx + 1;
	constexpr size_t jump_entry_size = 4 * 2; /* 2 x 4-byte instructions */
	uintptr_t tmp;
	uxlen_t res = 0;

	static_assert(end_idx >= start_idx, "Invalid range");

	asm volatile(CSR_INDEXED_ASM("csrr %[res], (reg_idx)")
				: [res] "=r" (res),
				  [jmp_dst] "=&r" (tmp)					/* output */
				: [csr_count] "i" (csr_count),
				  [start] "i" (start_idx),
				  [index] "r" (idx * jump_entry_size)	/* input */
				:										/* clobbers: none */);

	return res;
}

template <csr start, csr end>
void csr_write_indexed(size_t idx, uxlen_t value)
{
	constexpr size_t start_idx = static_cast<size_t>(start);
	constexpr size_t end_idx = static_cast<size_t>(end);
	constexpr size_t csr_count = end_idx - start_idx + 1;
	constexpr size_t jump_entry_size = 4 * 2; /* 2 x 4-byte instructions */
	uintptr_t tmp;

	static_assert(end_idx >= start_idx, "Invalid range");

	asm volatile(CSR_INDEXED_ASM("csrw (reg_idx), %[val]")
				: [val] "=r" (value),
				  [jmp_dst] "=&r" (tmp)					/* output */
				: [csr_count] "i" (csr_count),
				  [start] "i" (start_idx),
				  [index] "r" (idx * jump_entry_size)	/* input */
				:										/* clobbers: none */);
}

#else

template<csr start, size_t... indices>
constexpr auto csr_write_func_table_gen(std::index_sequence<indices...>) {
	constexpr size_t start_idx = static_cast<size_t>(start);

	return std::array<void (*)(uxlen_t), sizeof...(indices)>
			{&csr_write<static_cast<csr>(start_idx + indices)>...};
}

template<csr start, size_t... indices>
constexpr auto csr_read_func_table_gen(std::index_sequence<indices...>) {
	constexpr size_t start_idx = static_cast<size_t>(start);

	return std::array<uxlen_t (*)(), sizeof...(indices)>
			{&csr_read<static_cast<csr>(start_idx + indices)>...};
}

template<csr start, csr end>
void csr_write_indexed(size_t idx, uxlen_t value) {
	static_assert(end >= start, "Invalid CSR range, end < start");

	constexpr size_t csr_count = static_cast<size_t>(end) - static_cast<size_t>(start) + 1;
	using csr_idx_seq = std::make_index_sequence<csr_count>;
	static constexpr auto func_tbl = csr_write_func_table_gen<start>(csr_idx_seq{});

	if (idx < csr_count)
		func_tbl[idx](value);
}

template<csr start, csr end>
uxlen_t csr_read_indexed(size_t idx) {
	static_assert(end >= start, "Invalid CSR range, end < start");

	constexpr size_t csr_count = static_cast<size_t>(end) - static_cast<size_t>(start) + 1;
	using csr_idx_seq = std::make_index_sequence<csr_count>;
	static constexpr auto func_tbl = csr_read_func_table_gen<start>(csr_idx_seq{});
	uxlen_t res = 0;

	if (idx < csr_count)
		res = func_tbl[idx]();

	return res;
}

#endif

} /* namespace helpers */

void csr_write_pmpaddr(size_t idx, uxlen_t value)
{
	return helpers::csr_write_indexed<csr::pmpaddr0, csr::pmpaddr15>(idx, value);
}

uxlen_t csr_read_pmpaddr(size_t idx)
{
	return helpers::csr_read_indexed<csr::pmpaddr0, csr::pmpaddr15>(idx);
}

} /* namespace rv */

#endif /* BITFIELDSET_ARCH_CSR_H */

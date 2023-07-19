/*
 * SPDX-FileCopyrightText: 2023 Dmitrii Lebed <lebed.dmitry@gmail.com>
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef BITFIELDSET_ARCH_RV_TYPES_H
#define BITFIELDSET_ARCH_RV_TYPES_H

#include <stdint.h>

#ifndef __riscv
#error "Including RISC-V header on non-RISC-V platform"
#endif

namespace rv {

#if __riscv_xlen == 32
using uxlen_t = uint32_t;
using xlen_t = int32_t;
#elif __riscv_xlen == 64
using uxlen_t = uint64_t;
using xlen_t = int64_t;
#else
#error "Unsupported XLEN configuration"
#endif

}

#endif /* BITFIELDSET_ARCH_RV_TYPES_H */

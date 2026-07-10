/*
 * 86Box    A hypervisor and IBM PC system emulator that specializes in
 *          running old operating systems and software designed for IBM
 *          PC systems and compatibles from 1981 through fairly recent
 *          system designs based on the PCI bus.
 *
 *          This file is part of the 86Box distribution.
 *
 *          "Bentium 5" fictional high-IPC 686-class CPU timing model.
 *
 *          Every instruction costs exactly 1 cycle with no pairing
 *          logic, no AGI stalls, and no decode delays. This removes
 *          all artificial CPU speed throttling while keeping the
 *          guest's timer/scheduler accurate (the emulated clock still
 *          ticks at the configured MHz, every instruction just
 *          completes in one tick instead of many).
 *
 *          Designed for Socket 370 / Slot 1 boards when you want the
 *          guest to run at the maximum speed the host can sustain.
 *
 * Authors: (Fictional CPU, local patch)
 *
 *          Copyright 2024 86Box contributors.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <86box/86box.h>
#include "cpu.h"
#include <86box/mem.h>
#include <86box/plat_unused.h>

#include "x86.h"
#include "x86_ops.h"
#include "x87_sf.h"
#include "x87.h"
#include "codegen.h"
#include "codegen_timing_common.h"

static void
codegen_timing_bentium5_block_start(void)
{
    /* Nothing to initialise per block */
}

static void
codegen_timing_bentium5_start(void)
{
    /* Nothing to initialise per instruction */
}

static void
codegen_timing_bentium5_prefix(UNUSED(uint8_t prefix), UNUSED(uint32_t fetchdat))
{
    /* All prefixes are free – no decode delay */
}

static void
codegen_timing_bentium5_opcode(UNUSED(uint8_t opcode), UNUSED(uint32_t fetchdat),
                               UNUSED(int op_32), UNUSED(uint32_t op_pc))
{
    /*
     * Every instruction costs exactly 1 cycle.
     * No pairing, no stalls, no per-instruction look-up tables.
     * The guest OS still sees correct elapsed time because the
     * configured clock speed determines how many real-time
     * nanoseconds each cycle represents; we just remove the
     * artificial extra stalls that accurate timing would add.
     */
    codegen_block_cycles++;
}

static void
codegen_timing_bentium5_block_end(void)
{
    /* Nothing to flush at block end */
}

codegen_timing_t codegen_timing_bentium5 = {
    codegen_timing_bentium5_start,
    codegen_timing_bentium5_prefix,
    codegen_timing_bentium5_opcode,
    codegen_timing_bentium5_block_start,
    codegen_timing_bentium5_block_end,
    NULL
};

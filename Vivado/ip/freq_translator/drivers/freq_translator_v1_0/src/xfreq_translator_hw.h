// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of bypass
//        bit 0  - bypass[0] (Read/Write)
//        others - reserved
// 0x14 : reserved
// 0x18 : Data signal of phase_inc_rad
//        bit 31~0 - phase_inc_rad[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[31:0] (Read/Write)
// 0x24 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[63:32] (Read/Write)
// 0x28 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[95:64] (Read/Write)
// 0x2c : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[127:96] (Read/Write)
// 0x30 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[159:128] (Read/Write)
// 0x34 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[191:160] (Read/Write)
// 0x38 : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[223:192] (Read/Write)
// 0x3c : Data signal of nco_phase_accum
//        bit 31~0 - nco_phase_accum[255:224] (Read/Write)
// 0x40 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XFREQ_TRANSLATOR_CONTROL_ADDR_BYPASS_DATA          0x10
#define XFREQ_TRANSLATOR_CONTROL_BITS_BYPASS_DATA          1
#define XFREQ_TRANSLATOR_CONTROL_ADDR_PHASE_INC_RAD_DATA   0x18
#define XFREQ_TRANSLATOR_CONTROL_BITS_PHASE_INC_RAD_DATA   32
#define XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA 0x20
#define XFREQ_TRANSLATOR_CONTROL_BITS_NCO_PHASE_ACCUM_DATA 256


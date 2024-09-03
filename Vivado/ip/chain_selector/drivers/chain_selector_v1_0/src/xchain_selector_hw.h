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
// 0x10 : Data signal of s0
//        bit 0  - s0[0] (Read/Write)
//        others - reserved
// 0x14 : reserved
// 0x18 : Data signal of s1
//        bit 0  - s1[0] (Read/Write)
//        others - reserved
// 0x1c : reserved
// 0x20 : Data signal of s2
//        bit 0  - s2[0] (Read/Write)
//        others - reserved
// 0x24 : reserved
// 0x28 : Data signal of s3
//        bit 0  - s3[0] (Read/Write)
//        others - reserved
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCHAIN_SELECTOR_CONTROL_ADDR_S0_DATA 0x10
#define XCHAIN_SELECTOR_CONTROL_BITS_S0_DATA 1
#define XCHAIN_SELECTOR_CONTROL_ADDR_S1_DATA 0x18
#define XCHAIN_SELECTOR_CONTROL_BITS_S1_DATA 1
#define XCHAIN_SELECTOR_CONTROL_ADDR_S2_DATA 0x20
#define XCHAIN_SELECTOR_CONTROL_BITS_S2_DATA 1
#define XCHAIN_SELECTOR_CONTROL_ADDR_S3_DATA 0x28
#define XCHAIN_SELECTOR_CONTROL_BITS_S3_DATA 1


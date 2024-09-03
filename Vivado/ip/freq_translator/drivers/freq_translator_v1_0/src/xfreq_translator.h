// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XFREQ_TRANSLATOR_H
#define XFREQ_TRANSLATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfreq_translator_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XFreq_translator_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XFreq_translator;

typedef u32 word_type;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
} XFreq_translator_Nco_phase_accum;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFreq_translator_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFreq_translator_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFreq_translator_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFreq_translator_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFreq_translator_Initialize(XFreq_translator *InstancePtr, u16 DeviceId);
XFreq_translator_Config* XFreq_translator_LookupConfig(u16 DeviceId);
int XFreq_translator_CfgInitialize(XFreq_translator *InstancePtr, XFreq_translator_Config *ConfigPtr);
#else
int XFreq_translator_Initialize(XFreq_translator *InstancePtr, const char* InstanceName);
int XFreq_translator_Release(XFreq_translator *InstancePtr);
#endif


void XFreq_translator_Set_bypass(XFreq_translator *InstancePtr, u32 Data);
u32 XFreq_translator_Get_bypass(XFreq_translator *InstancePtr);
void XFreq_translator_Set_phase_inc_rad(XFreq_translator *InstancePtr, u32 Data);
u32 XFreq_translator_Get_phase_inc_rad(XFreq_translator *InstancePtr);
void XFreq_translator_Set_nco_phase_accum(XFreq_translator *InstancePtr, XFreq_translator_Nco_phase_accum Data);
XFreq_translator_Nco_phase_accum XFreq_translator_Get_nco_phase_accum(XFreq_translator *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

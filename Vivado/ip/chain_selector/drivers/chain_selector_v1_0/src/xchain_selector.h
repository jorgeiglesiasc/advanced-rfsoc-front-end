// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCHAIN_SELECTOR_H
#define XCHAIN_SELECTOR_H

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
#include "xchain_selector_hw.h"

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
} XChain_selector_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XChain_selector;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XChain_selector_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XChain_selector_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XChain_selector_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XChain_selector_ReadReg(BaseAddress, RegOffset) \
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
int XChain_selector_Initialize(XChain_selector *InstancePtr, u16 DeviceId);
XChain_selector_Config* XChain_selector_LookupConfig(u16 DeviceId);
int XChain_selector_CfgInitialize(XChain_selector *InstancePtr, XChain_selector_Config *ConfigPtr);
#else
int XChain_selector_Initialize(XChain_selector *InstancePtr, const char* InstanceName);
int XChain_selector_Release(XChain_selector *InstancePtr);
#endif


void XChain_selector_Set_s0(XChain_selector *InstancePtr, u32 Data);
u32 XChain_selector_Get_s0(XChain_selector *InstancePtr);
void XChain_selector_Set_s1(XChain_selector *InstancePtr, u32 Data);
u32 XChain_selector_Get_s1(XChain_selector *InstancePtr);
void XChain_selector_Set_s2(XChain_selector *InstancePtr, u32 Data);
u32 XChain_selector_Get_s2(XChain_selector *InstancePtr);
void XChain_selector_Set_s3(XChain_selector *InstancePtr, u32 Data);
u32 XChain_selector_Get_s3(XChain_selector *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

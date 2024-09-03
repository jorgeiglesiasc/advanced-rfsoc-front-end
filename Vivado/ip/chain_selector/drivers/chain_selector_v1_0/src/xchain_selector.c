// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xchain_selector.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XChain_selector_CfgInitialize(XChain_selector *InstancePtr, XChain_selector_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XChain_selector_Set_s0(XChain_selector *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XChain_selector_WriteReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S0_DATA, Data);
}

u32 XChain_selector_Get_s0(XChain_selector *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XChain_selector_ReadReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S0_DATA);
    return Data;
}

void XChain_selector_Set_s1(XChain_selector *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XChain_selector_WriteReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S1_DATA, Data);
}

u32 XChain_selector_Get_s1(XChain_selector *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XChain_selector_ReadReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S1_DATA);
    return Data;
}

void XChain_selector_Set_s2(XChain_selector *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XChain_selector_WriteReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S2_DATA, Data);
}

u32 XChain_selector_Get_s2(XChain_selector *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XChain_selector_ReadReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S2_DATA);
    return Data;
}

void XChain_selector_Set_s3(XChain_selector *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XChain_selector_WriteReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S3_DATA, Data);
}

u32 XChain_selector_Get_s3(XChain_selector *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XChain_selector_ReadReg(InstancePtr->Control_BaseAddress, XCHAIN_SELECTOR_CONTROL_ADDR_S3_DATA);
    return Data;
}


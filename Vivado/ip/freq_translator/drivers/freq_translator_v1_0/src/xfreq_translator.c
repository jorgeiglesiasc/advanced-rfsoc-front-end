// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfreq_translator.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFreq_translator_CfgInitialize(XFreq_translator *InstancePtr, XFreq_translator_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFreq_translator_Set_bypass(XFreq_translator *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_BYPASS_DATA, Data);
}

u32 XFreq_translator_Get_bypass(XFreq_translator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_BYPASS_DATA);
    return Data;
}

void XFreq_translator_Set_phase_inc_rad(XFreq_translator *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_PHASE_INC_RAD_DATA, Data);
}

u32 XFreq_translator_Get_phase_inc_rad(XFreq_translator *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_PHASE_INC_RAD_DATA);
    return Data;
}

void XFreq_translator_Set_nco_phase_accum(XFreq_translator *InstancePtr, XFreq_translator_Nco_phase_accum Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 0, Data.word_0);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 4, Data.word_1);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 8, Data.word_2);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 12, Data.word_3);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 16, Data.word_4);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 20, Data.word_5);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 24, Data.word_6);
    XFreq_translator_WriteReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 28, Data.word_7);
}

XFreq_translator_Nco_phase_accum XFreq_translator_Get_nco_phase_accum(XFreq_translator *InstancePtr) {
    XFreq_translator_Nco_phase_accum Data;

    Data.word_0 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 0);
    Data.word_1 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 4);
    Data.word_2 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 8);
    Data.word_3 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 12);
    Data.word_4 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 16);
    Data.word_5 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 20);
    Data.word_6 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 24);
    Data.word_7 = XFreq_translator_ReadReg(InstancePtr->Control_BaseAddress, XFREQ_TRANSLATOR_CONTROL_ADDR_NCO_PHASE_ACCUM_DATA + 28);
    return Data;
}


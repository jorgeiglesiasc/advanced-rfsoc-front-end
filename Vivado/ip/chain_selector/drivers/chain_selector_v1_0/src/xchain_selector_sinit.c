// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xchain_selector.h"

extern XChain_selector_Config XChain_selector_ConfigTable[];

XChain_selector_Config *XChain_selector_LookupConfig(u16 DeviceId) {
	XChain_selector_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCHAIN_SELECTOR_NUM_INSTANCES; Index++) {
		if (XChain_selector_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XChain_selector_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XChain_selector_Initialize(XChain_selector *InstancePtr, u16 DeviceId) {
	XChain_selector_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XChain_selector_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XChain_selector_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif


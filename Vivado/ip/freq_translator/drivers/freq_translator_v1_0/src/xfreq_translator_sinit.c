// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xfreq_translator.h"

extern XFreq_translator_Config XFreq_translator_ConfigTable[];

XFreq_translator_Config *XFreq_translator_LookupConfig(u16 DeviceId) {
	XFreq_translator_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFREQ_TRANSLATOR_NUM_INSTANCES; Index++) {
		if (XFreq_translator_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFreq_translator_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFreq_translator_Initialize(XFreq_translator *InstancePtr, u16 DeviceId) {
	XFreq_translator_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFreq_translator_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFreq_translator_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif


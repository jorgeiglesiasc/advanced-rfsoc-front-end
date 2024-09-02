//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: data_types.h
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: Define the data types of freq_translator.cc
//--
//----------------------------------------------------------------------------------
//--
//-- Advanced-RFSoC-front-end is an Advanced multi-band GNSS SDR front-end
//                                  implementation in an RFSoC integrated circuit
//-- This file is part of Advanced-RFSoC-front-end
//--
//-- Copyright (C) 2024 (see AUTHORS file for a list of contributors)
//-- SPDX-License-Identifier: GPL-3.0-or-later
//--
//----------------------------------------------------------------------------------
#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include </tools/Xilinx/Vitis_HLS/2022.1/include/gmp.h>

#include <stdint.h>
#include <hls_stream.h>
#include <ap_int.h>

#include <complex>

#define SSR 8 //Super Sampling Rate value
#define TWO_PI 6.2831853071795865

typedef ap_fixed<16,1> adc_sample; //The ADC of the RFSoC is 14bit
typedef ap_fixed<32,6> ap_fixed_nco_phase; //NCO phase type variable

//Structure for SSR signal data
typedef struct freq_trans {
	std::complex<adc_sample> sample[SSR];
} complex_fixed;

//Structure for SSR NCO phase
typedef struct nco_phase {
	ap_fixed_nco_phase mixer[SSR];
} nco_struct;

#endif

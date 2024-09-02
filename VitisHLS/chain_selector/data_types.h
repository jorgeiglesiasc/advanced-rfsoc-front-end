//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: data_types.h
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: Define the data types of chain_selector.cc
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

//typedef std::complex<ap_fixed<16,1>> sample_type; //For the simulation
typedef short sample_type; //For the Export RTL

#endif

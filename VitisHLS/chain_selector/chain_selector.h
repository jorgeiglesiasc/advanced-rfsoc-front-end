//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: chain_selector.h
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: chain_selector.cc header
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
#ifndef __CHAIN_SELECTOR_H__
#define __CHAIN_SELECTOR_H__

#include "data_types.h"

void chain_selector(hls::stream<sample_type>& data_in0,
		hls::stream<sample_type>& data_in1,
		hls::stream<sample_type>& data_in2,
		hls::stream<sample_type>& data_in3,
		bool s0,
		bool s1,
		bool s2,
		bool s3,
		hls::stream<sample_type>& data_out);

#endif

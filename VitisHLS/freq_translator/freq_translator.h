//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: freq_translator.h
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: freq_translator.cc header
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
#ifndef __FREQ_TRANS_H__
#define __FREQ_TRANS_H__

#include "data_types.h"

void freq_translator(hls::stream<freq_trans>& data_in,
		bool bypass,
		nco_struct &nco_phase_accum,
		ap_fixed_nco_phase &phase_inc_rad,
		hls::stream<freq_trans>& data_out);

#endif

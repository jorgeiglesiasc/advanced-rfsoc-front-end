//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: chain_selector.cc
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: By four booleans, the data flow from one of the four specific inputs
//                to the output is activated or deactivated. This module has been
//                created so that the user can choose which GNSS bands he wants to
//                transmit to the receiver
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
#include "chain_selector.h"

//----------------------------------------------------------------------------------
//-- Function name: chain_selector
//-- Variables:
//             data_in0,data_in1,data_in2,data_in3: The four input data chains
//             s0,s1,s2,s3: Booleans to control the data flow
//             data_out: The output chain
//----------------------------------------------------------------------------------
void chain_selector(hls::stream<sample_type>& data_in0,
		hls::stream<sample_type>& data_in1,
		hls::stream<sample_type>& data_in2,
		hls::stream<sample_type>& data_in3,
		bool s0,
		bool s1,
		bool s2,
		bool s3,
		hls::stream<sample_type>& data_out)
{
#pragma HLS INTERFACE mode=ap_ctrl_chain port=return //Block-Level Control Protocol as ap_ctrl_chain (ap_start, ap_continue, ap_idle, ap_ready and ap_done)

//Variables as axilite ports to control them from the PS
#pragma HLS INTERFACE mode=s_axilite port=s0 
#pragma HLS INTERFACE mode=s_axilite port=s1
#pragma HLS INTERFACE mode=s_axilite port=s2
#pragma HLS INTERFACE mode=s_axilite port=s3

	//If the first input chain is not empty, the chain_selector will write in the output variable the data of the chains
	//that the user choose by activating its corresponding boolean, if not, the data of the chain is read for remove it
	main_loop: while(data_in0.empty()==false)
	{
#pragma HLS UNROLL //The process is carried out in parallel

		if(s0){
			data_out.write(data_in0.read());
		} else {
			data_in0.read();
		}

		if(s1){
			data_out.write(data_in1.read());
		} else {
			data_in1.read();
		}

		if(s2){
			data_out.write(data_in2.read());
		} else {
			data_in2.read();
		}

		if(s3){
			data_out.write(data_in3.read());
		} else {
			data_in3.read();
		}
	}
}

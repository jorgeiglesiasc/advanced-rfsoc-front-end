//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: tb_chain_selector.cc
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: chain_selector.cc testbench
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

#define N_SAMPLES 1024

//----------------------------------------------------------------------------------
//-- Function name: main
//-- Return: Any value other than '0' means error
//----------------------------------------------------------------------------------
int main() {
	hls::stream<sample_type> data_in[4]; //The four input chains
	sample_type array_signal;

	//Load dummy data
	for (int i=0;i<N_SAMPLES;i++) {
		for(int j=0;j<4;j++){
			array_signal.real(0.1*j);
			array_signal.imag(0.1*j);
			data_in[j].write(array_signal);
			std::cout<<"data_in"<<j<<": "<<array_signal<<" \n";
		}
	}

	hls::stream<sample_type> data_out("data_out"); //The output chain

	//Function call
	chain_selector(data_in[0],
			data_in[1],
			data_in[2],
			data_in[3],
			true,
			false,
			true,
			false,
			data_out);

	sample_type sample_out;

	//Read the output data
	while (data_out.empty()==false) {
		sample_out = data_out.read();
		std::cout<<"data_out: "<<sample_out<<" \n";
	}

	return 0;
}

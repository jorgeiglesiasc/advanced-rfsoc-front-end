//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//-- Author: Javier Arribas, 2024. jarribas(at)cttc.es
//--
//-- File Name: freq_translator.cc
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: Changes the frequency of a signal that uses Super Sampling Rate
//                (SSR) by multiplying that signal with one generated by an NCO
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
#include "freq_translator.h"

#include <string.h>

//----------------------------------------------------------------------------------
//-- Function name: freq_translator
//-- Variables:
//             data_in: SSR input data array. Original signal
//             bypass: 0-> The frequency change. 1-> Not changed
//             nco_phase_accum: SSR NCO initialization values array
//             phase_inc_rad: To reduce the process execution time, it works with
//                            the nco phase increment
//             data_out: SSR output data array. Frequency change
//----------------------------------------------------------------------------------
void freq_translator(hls::stream<freq_trans>& data_in,
		bool bypass,
		nco_struct &nco_phase_accum,
		ap_fixed_nco_phase &phase_inc_rad,
		hls::stream<freq_trans>& data_out)
{
#pragma HLS INTERFACE mode=ap_ctrl_chain port=return //Block-Level Control Protocol as ap_ctrl_chain (ap_start, ap_continue, ap_idle, ap_ready and ap_done)

//Variables as axilite ports to control them from the PS
#pragma HLS INTERFACE mode=s_axilite port=bypass
#pragma HLS INTERFACE mode=s_axilite port=nco_phase_accum
#pragma HLS INTERFACE mode=s_axilite port=phase_inc_rad

	complex_fixed mix_data_in;
	complex_fixed mix_data_out;
	
	//These arrays are completely partitioned to be able to perform parallel processes using the UNROLL pragma as well
	#pragma HLS ARRAY_PARTITION variable=mix_data_in type=complete
	#pragma HLS ARRAY_PARTITION variable=mix_data_out type=complete

	//The loop is infinite to avoid any bottlenecks, since the block is constantly running
	main_loop: while (data_in.empty()==false) //For the simulation
	//main_loop: while (true) //For the Export RTL
	{
		#pragma HLS PIPELINE II=1 //Initiation interval pipeline to 1

		mix_data_in = data_in.read();

		if (!bypass) {
			mix_loop: for (int j = 0; j < SSR; j++) {
				#pragma HLS UNROLL //The process is carried out in parallel

				mix_data_out.sample[j] = mix_data_in.sample[j] * std::complex<adc_sample>(std::cos(static_cast<float>(nco_phase_accum.mixer[j])), -std::sin(static_cast<float>(nco_phase_accum.mixer[j]))); //Multiply each number in the original array by a value in the NCO array

				nco_phase_accum.mixer[j] += phase_inc_rad; //Update the NCO phase array
				//If this value is more than TWO_PI or is less than -TWO_PI it must be corrected, since we are working with phasors
				if (nco_phase_accum.mixer[j]>static_cast<ap_fixed_nco_phase>(TWO_PI)) nco_phase_accum.mixer[j]-=static_cast<ap_fixed_nco_phase>(TWO_PI);
				else if (nco_phase_accum.mixer[j]<static_cast<ap_fixed_nco_phase>(-TWO_PI)) nco_phase_accum.mixer[j]+=static_cast<ap_fixed_nco_phase>(TWO_PI);
			}
			data_out.write(mix_data_out);
		} else {
			data_out.write(mix_data_in);
		}
	}
}
//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//-- Author: Javier Arribas, 2024. jarribas(at)cttc.es
//--
//-- File Name: tb_freq_translator.cc
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Tool Versions: 2022.1
//-- Description: freq_translator.cc testbench
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

#include <cmath>
#include <fstream>

#define N_SAMPLES 1024*10

//----------------------------------------------------------------------------------
//-- Function name: main
//-- Return: Any value other than '0' means error
//----------------------------------------------------------------------------------
int main() {
	int block_samples = N_SAMPLES/SSR;
	float sample_re_in;
	float sample_im_in;
	hls::stream<freq_trans> data_in; //The input signal
	complex_fixed array_signal[block_samples];

	std::ofstream d_dump_file_in;
	std::ofstream d_dump_file_out;
	float file_data_float;
	int l = 0;

	//Creating files for analysis in MATLAB with plots
	d_dump_file_in.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try{
		d_dump_file_in.open("Freq_trans_in_samples.dat", std::ios::out | std::ios::binary);
	}
	catch (const std::ofstream::failure &e){
		std::cout << "Exception opening d_dump_file_in file " << e.what();
	}
	d_dump_file_out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try{
		d_dump_file_out.open("Freq_trans_out_samples.dat", std::ios::out | std::ios::binary);
	}
	catch (const std::ofstream::failure &e){
		std::cout << "Exception opening d_dump_file_out file " << e.what();
	}

    double f_s=1.024e6; //Frequency sampling
    double ts=1/f_s;
    double f_tone_hz=f_s/16.0; //Tone frequency
    double f_nco = f_s/32.0; // NCO frequency

    //Load dummy data
	for (int i = 0; i < block_samples; i++) {
		for (int j = 0; j < SSR;j++) {
			sample_re_in=0.1*std::cos(TWO_PI*f_tone_hz*ts*static_cast<double>(j+i*SSR));
			sample_im_in=0.1*std::sin(TWO_PI*f_tone_hz*ts*static_cast<double>(j+i*SSR));
			array_signal[i].sample[j].real(static_cast<adc_sample>(sample_re_in));
			array_signal[i].sample[j].imag(static_cast<adc_sample>(sample_im_in));
		}
		data_in.write(array_signal[i]);
	}

	//Write the input data in a file
	try{
		for (int i = 0; i < block_samples; i++) {
				for (int j = 0; j < SSR;j++) {
					file_data_float = static_cast<float>(array_signal[i].sample[j].real());
					d_dump_file_in.write(reinterpret_cast<char *>(&file_data_float), sizeof(float));
					file_data_float = static_cast<float>(array_signal[i].sample[j].imag());
					d_dump_file_in.write(reinterpret_cast<char *>(&file_data_float), sizeof(float));
				}
		}
	}
	catch (const std::ofstream::failure &e){
		std::cout << "Exception writing d_dump_file_in file " << e.what();
	}
	if (d_dump_file_in.is_open()) {
		d_dump_file_in.close();
	}

	bool bypass = false;
	hls::stream<freq_trans> data_out; //The output signal

	float phase_inc_single = TWO_PI * f_nco/f_s; //Phase increment between samples

	float phase_inc_rad = SSR * phase_inc_single; //Phase increment between SSR samples
	if (phase_inc_rad>static_cast<float>(TWO_PI)) while (phase_inc_rad>static_cast<float>(TWO_PI)) phase_inc_rad-=static_cast<float>(TWO_PI);
	else if (phase_inc_rad<static_cast<float>(-TWO_PI)) while (phase_inc_rad<static_cast<float>(-TWO_PI)) phase_inc_rad+=static_cast<float>(TWO_PI);

	float init_nco_phase_accum[SSR]; //Initial phase increment array for each complex multiplier
	for (int k = 0; k < SSR; k++) {
		init_nco_phase_accum[k] = k*phase_inc_single;
		if (init_nco_phase_accum[k]>static_cast<float>(TWO_PI)) while (init_nco_phase_accum[k]>static_cast<float>(TWO_PI)) init_nco_phase_accum[k]-=static_cast<float>(TWO_PI);
		else if (init_nco_phase_accum[k]<static_cast<float>(-TWO_PI)) while (init_nco_phase_accum[k]<static_cast<float>(-TWO_PI)) init_nco_phase_accum[k]+=static_cast<float>(TWO_PI);
	}

	nco_struct init_nco_phase_accum_apfix;
	for (int k = 0; k < SSR; k++) {
		init_nco_phase_accum_apfix.mixer[k]=static_cast<ap_fixed_nco_phase>(init_nco_phase_accum[k]);
	}
	ap_fixed_nco_phase phase_inc_rad_fixed = static_cast<ap_fixed_nco_phase>(phase_inc_rad);

	//Function call
	freq_translator(data_in,
		bypass,
		init_nco_phase_accum_apfix,
		phase_inc_rad_fixed,
		data_out);

	//Read the output data
	complex_fixed sample_out[block_samples];
	while (data_out.empty()==false) {
		sample_out[l] = data_out.read();
		l++;
	}

	//Write the output data in a file
	try{
		for (int i = 0; i < block_samples; i++) {
			for (int j = 0; j < SSR;j++) {
				file_data_float = static_cast<float>(sample_out[i].sample[j].real());
				d_dump_file_out.write(reinterpret_cast<char *>(&file_data_float), sizeof(float));
				file_data_float = static_cast<float>(sample_out[i].sample[j].imag());
				d_dump_file_out.write(reinterpret_cast<char *>(&file_data_float), sizeof(float));
			}
		}
	}
	catch (const std::ofstream::failure &e){
		std::cout << "Exception writing d_dump_file_out file " << e.what();
	}
	if (d_dump_file_out.is_open()) {
		d_dump_file_out.close();
	}

	return 0;
}

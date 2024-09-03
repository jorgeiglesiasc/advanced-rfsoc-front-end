// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Version: 2022.1
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps

module freq_translator_mul_80s_24ns_80_5_1(clk, ce, reset, din0, din1, dout);
parameter ID = 1;
parameter NUM_STAGE = 4;
parameter din0_WIDTH = 14;
parameter din1_WIDTH = 12;
parameter dout_WIDTH = 26;
input clk;
input ce;
input reset;
input[din0_WIDTH - 1 : 0] din0; 
input[din1_WIDTH - 1 : 0] din1; 
output[dout_WIDTH - 1 : 0] dout;

reg signed [din0_WIDTH - 1 : 0] a_reg0;
reg [din1_WIDTH - 1 : 0] b_reg0;
wire signed [dout_WIDTH - 1 : 0] tmp_product;
reg signed [dout_WIDTH - 1 : 0] buff0;
reg signed [dout_WIDTH - 1 : 0] buff1;
reg signed [dout_WIDTH - 1 : 0] buff2;

assign dout = buff2;
assign tmp_product = a_reg0 * $signed({1'b0, b_reg0});
always @ (posedge clk) begin
    if (ce) begin
        a_reg0 <= din0;
        b_reg0 <= din1;
        buff0 <= tmp_product;
        buff1 <= buff0;
        buff2 <= buff1;
    end
end
endmodule

----------------------------------------------------------------------------------
--
-- Company: CTTC
-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
-- 
-- File Name: complexToSlice.vhd
-- Target Devices: RFSoC4x2 and ZCU208
-- Tool Versions: 2022.1
-- Description:  Q7,I7...,Q0,I0 to I7,I6...,I0 and Q7...,Q0
-- 
----------------------------------------------------------------------------------
--
-- Advanced-RFSoC-front-end is an Advanced multi-band GNSS SDR front-end
--                                implementation in an RFSoC integrated circuit
-- This file is part of Advanced-RFSoC-front-end
--
-- Copyright (C) 2024 (see AUTHORS file for a list of contributors)
-- SPDX-License-Identifier: GPL-3.0-or-later
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity complexToSlice is
    Port ( data_in : in STD_LOGIC_VECTOR (255 downto 0);
           data_out_re : out STD_LOGIC_VECTOR (127 downto 0);
           data_out_im : out STD_LOGIC_VECTOR (127 downto 0));
end complexToSlice;

architecture Behavioral of complexToSlice is

begin
    data_out_re <= data_in(239 downto 224) & data_in(207 downto 192) & data_in(175 downto 160) & data_in(143 downto 128) & data_in(111 downto 96) & data_in(79 downto 64) & data_in(47 downto 32) & data_in(15 downto 0);
    data_out_im <= data_in(255 downto 240) & data_in(223 downto 208) & data_in(191 downto 176) & data_in(159 downto 144) & data_in(127 downto 112) & data_in(95 downto 80) & data_in(63 downto 48) & data_in(31 downto 16);

end Behavioral;

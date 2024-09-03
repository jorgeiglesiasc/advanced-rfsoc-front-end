----------------------------------------------------------------------------------
--
-- Company: CTTC
-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
-- 
-- File Name: concatToComplex.vhd
-- Target Devices: RFSoC4x2 and ZCU208
-- Tool Versions: 2022.1
-- Description:  I7,I6...,I0 and Q7...,Q0 to Q7,I7...,Q0,I0
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

entity concatToComplex is
    Port ( data_in_re : in STD_LOGIC_VECTOR (127 downto 0);
           data_in_im : in STD_LOGIC_VECTOR (127 downto 0);
           data_out : out STD_LOGIC_VECTOR (255 downto 0));
end concatToComplex;

architecture Behavioral of concatToComplex is

begin
    data_out <= data_in_im(127 downto 112) & data_in_re(127 downto 112) & data_in_im(111 downto 96) & data_in_re(111 downto 96) & data_in_im(95 downto 80) & data_in_re(95 downto 80) & data_in_im(79 downto 64) & data_in_re(79 downto 64) & data_in_im(63 downto 48) & data_in_re(63 downto 48) & data_in_im(47 downto 32) & data_in_re(47 downto 32) & data_in_im(31 downto 16) & data_in_re(31 downto 16) & data_in_im(15 downto 0) & data_in_re(15 downto 0);

end Behavioral;

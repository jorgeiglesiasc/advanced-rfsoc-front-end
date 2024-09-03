----------------------------------------------------------------------------------
--
-- Company: CTTC
-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
-- 
-- File Name: complexToSliceSingle.vhd
-- Target Devices: RFSoC4x2 and ZCU208
-- Tool Versions: 2022.1
-- Description: I0 and Q0 to Q0,I0
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

entity concatToComplexSingle is
    Port ( data_in_re : in STD_LOGIC_VECTOR (15 downto 0);
           data_in_im : in STD_LOGIC_VECTOR (15 downto 0);
           data_out : out STD_LOGIC_VECTOR (31 downto 0));
end concatToComplexSingle;

architecture Behavioral of concatToComplexSingle is

begin
    data_out <= data_in_im(15 downto 0) & data_in_re(15 downto 0);

end Behavioral;

//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//--
//-- File Name: dma2udp.h
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Description: dma2udp.cc header
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
#ifndef DMA2UDP_H
#define DMA2UDP_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define S2MM_DMACR 0x30 //S2MM DMA Control Register
#define S2MM_DMASR 0x34 //S2MM DMA Status Register
#define S2MM_DA 0x48 //S2MM DMA Destination Address Register
#define S2MM_LENGTH 0x58 //S2MM DMA Transfer Length Register

#define DESTINATION_ADDR 0x2000000
#define TRANSFER_BYTES 320000
#define DMA_BASE_ADDR 0x800e0000

#define UDP_IP "10.1.3.141" //IP destination
#define UDP_PORT 5005

void dma_write(unsigned int* dma_dma_reg_addr, int reg_offset, unsigned int value);
unsigned int dma_read(unsigned int* dma_dma_reg_addr, int reg_offset);
void intHandler(int dummy __attribute__((unused)));
void send_to_udp_from_mem();

#endif //DMA2UDP_H

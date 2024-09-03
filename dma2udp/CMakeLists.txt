#----------------------------------------------------------------------------------
#--
#-- Company: CTTC
#-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
#--
#-- File Name: CMakeLists.txt
#-- Target Devices: RFSoC4x2 and ZCU208
#-- Description: dma2udp CMakeLists
#--
#----------------------------------------------------------------------------------
#--
#-- Advanced-RFSoC-front-end is an Advanced multi-band GNSS SDR front-end
#                                  implementation in an RFSoC integrated circuit
#-- This file is part of Advanced-RFSoC-front-end
#--
#-- Copyright (C) 2024 (see AUTHORS file for a list of contributors)
#-- SPDX-License-Identifier: GPL-3.0-or-later
#--
#----------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.15...3.30)

#Project statement
project(
  dma2udp
  VERSION 1.0
  LANGUAGES CXX)

#Optimizations
#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release)
#endif()
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O1")

include_directories(include)

set(SOURCES
	src/dma2udp.cc)

set(HEADERS
	include/dma2udp.h
	include/concurrent_queue.h)

add_executable(dma2udp ${SOURCES} ${HEADERS})


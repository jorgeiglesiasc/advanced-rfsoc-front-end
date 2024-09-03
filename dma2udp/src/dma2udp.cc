//----------------------------------------------------------------------------------
//--
//-- Company: CTTC
//-- Author: Jorge Iglesias, 2024. jorgeiglesiascostas(at)gmail.com
//-- Author: Javier Arribas, 2024. jarribas(at)cttc.es
//--
//-- File Name: dma2udp.cc
//-- Target Devices: RFSoC4x2 and ZCU208
//-- Description: Once the target device has been initialized and configured by
//                executing the multipleChain_singleDMA_system.ipynb code, dma2udp
//                sends the samples from the PL DMA to the final device via socket.
//         Use "sudo ./dma2udp" to executate this program
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
#include "dma2udp.h"
#include "concurrent_queue.h"

#include <iostream>
#include <thread>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <memory>
#include <signal.h>

#define RAM_BUFFERS 32

static volatile bool keep_working = true;

//Using queues of smart pointers to memory
Concurrent_Queue<uint8_t *> mem_free_buffers;
Concurrent_Queue<uint8_t *> mem_used_buffers;

//----------------------------------------------------------------------------------
//-- Function name: dma_write
//-- Variables:
//             dma_dma_reg_addr: DMA register base address
//	       reg_offset: Register offset to select a DMA register
//             value: Value to load
//-- Description: Write a value to a DMA register
//----------------------------------------------------------------------------------
void dma_write(unsigned int* dma_dma_reg_addr, int reg_offset, unsigned int value) {
    dma_dma_reg_addr[reg_offset>>2] = value;
}

//----------------------------------------------------------------------------------
//-- Function name: dma_read
//-- Variables:
//             dma_dma_reg_addr: DMA register base address
//             reg_offset: Register offset to select a DMA register
//-- Description: Read the value of a DMA register
//-- Return: The value of the DMA register
//----------------------------------------------------------------------------------
unsigned int dma_read(unsigned int* dma_dma_reg_addr, int reg_offset) {
    return dma_dma_reg_addr[reg_offset>>2];
}

//----------------------------------------------------------------------------------
//-- Function name: intHandler
//-- Description: Interruption handler
//----------------------------------------------------------------------------------
void intHandler(int dummy __attribute__((unused))) {
    keep_working = false;
}

//----------------------------------------------------------------------------------
//-- Function name: send_to_udp_from_mem
//-- Description: Create the socket and send the samples to the next device
//----------------------------------------------------------------------------------
void send_to_udp_from_mem() {
    uint8_t *ram_current_samples;

    std::cout << "Starting send_to_udp_from_mem thread...\n ";
    std::cout << std::flush;

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return;
    }

    // Define the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_PORT);
    server_addr.sin_addr.s_addr = inet_addr(UDP_IP);

    ssize_t r;
    while (keep_working == true)
    {
        if (mem_used_buffers.timed_wait_and_pop(ram_current_samples, 1000) == true)
        {
            //sendto(sockfd, (void *)ram_current_samples, 32000, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            sendto(sockfd, (void *)&ram_current_samples[0], 8000, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	    sendto(sockfd, (void *)&ram_current_samples[8000], 8000, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	    sendto(sockfd, (void *)&ram_current_samples[16000], 8000, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	    sendto(sockfd, (void *)&ram_current_samples[24000], 8000, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            mem_free_buffers.push(ram_current_samples);
        }
    }
    close(sockfd);
}

//----------------------------------------------------------------------------------
//-- Function name: main
//-- Return: Any value other than '0' means error
//----------------------------------------------------------------------------------
int main() {
    signal(SIGINT, intHandler);

    //Using queues of smart pointers to preallocated buffers
    mem_free_buffers.clear();
    mem_used_buffers.clear();

    //Preallocate buffers and use queues
    std::cerr << "Allocating memory..\n";
    try
    {
        for (int n = 0; n < RAM_BUFFERS; n++)
        {
            uint8_t *aligned_buffer;
            if (posix_memalign((void **)&aligned_buffer, 512, TRANSFER_BYTES))
            {
                perror("posix_memalign failed");
                exit(EXIT_FAILURE);
            }
            mem_free_buffers.push(aligned_buffer);
        }
    }
    catch (const std::exception &ex)
    {
        std::cout << "ERROR: Problem allocating RAM buffer: " << ex.what() << "\n";
        return false;
    }

    //Create a mapping in the virtual address space of the calling process
    int dh = open("/dev/mem", O_RDWR | O_SYNC);
    unsigned int* dma_reg_addr = (unsigned int*)mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, dh, DMA_BASE_ADDR); // AXI Lite address
    uint8_t* buffer = (uint8_t*)mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, dh, DESTINATION_ADDR); // S2MM destination address

    unsigned int s2mm_status;
    uint8_t *ram_current_samples;

    //Start sample capture process dma thread
    std::thread send_to_udp_from_mem_thread;
    send_to_udp_from_mem_thread = std::thread(&send_to_udp_from_mem);

    std::cout << "Running AXI DMA to UDP...\n";
    std::cout<< std::flush;

    //Reset the channel
    dma_write(dma_reg_addr, S2MM_DMACR, 4);

    //Halt the channel
    dma_write(dma_reg_addr, S2MM_DMACR, 0);

    //Set destination address
    dma_write(dma_reg_addr, S2MM_DA, DESTINATION_ADDR);

    //Mask interrupts
    dma_write(dma_reg_addr, S2MM_DMACR, 0xf001);

    while(keep_working)
    {
        mem_free_buffers.wait_and_pop(ram_current_samples);

        //Set transfer length and starts the DMA process
        dma_write(dma_reg_addr, S2MM_LENGTH, TRANSFER_BYTES);

	//Wait for idle bit
        do {
	    s2mm_status=dma_read(dma_reg_addr, S2MM_DMASR);
	}while(!(s2mm_status & 0x02));

        memcpy(ram_current_samples,buffer,32000);
        mem_used_buffers.push(ram_current_samples);
    }

    std::cout << "Joining send_to_udp_from_mem thread...\n";
    send_to_udp_from_mem_thread.join();

    std::cout << "Done!\n";
    return 0;
}

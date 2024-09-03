![N|Solid](https://52north.org/wp-content/uploads/2023/05/gsoc-horizontal.png)
# GNSS-SDR with a RFSoC IC
### Contributor: Jorge Iglesias | Mentor: Javier Arribas | Organization: GNSS-SDR
Google Summer of Code (GSoC) is a global, online program focused on bringing new contributors into open source software development. I have been a contributor to the GNSS-SDR project (https://gnss-sdr.org/) with my **Advanced multi-band GNSS SDR front-end implementation in an RFSoC integrated circuit**. For further information, please do not hesitate to contact me (jorgeiglesiascostas@gmail.com).

## Introduction
Nowadays, a superheterodyne analog front-end is normally used to receive carrier signals of the order of GHz. The radio frequency (RF) signal is translated to an Intermediate Frequency (IF), to finally obtain it in baseband. This technique has some well-known inherent limitations, such as the image frequency problem that limits the available bandwidth and the number of required analog components. Direct-to-baseband conversion technique removes some of the superheterodyne limitations, however it still requires analog filters and mixers.  In the area of radio navigation receivers, in a near future, when we want to provide a universal navigation system suitable for multi-band and multi-constellation operation and flexible enough to upgrade its capabilities by a firmware update, it is necessary to change this technology. For this reason, the future of front-ends involves using systems that have Analog-to-Digital Converters (ADCs) on the order of Giga Samples Per Second (GSPS) where the signal received by the antenna is amplified and sampled, and all the processing is done in the digital domain. This technology is referred as direct-RF sampling in the literature. An example of this type of system is the advanced multi-band Global Navigation Satellite System (GNSS) Software Defined Radio (SDR) front-end designed in this project using a Radio Frequency System-on-Chip (RFSoC).

### GNSS
GNSS is used to describe any satellite navigation system with global or regional coverage. Satellite navigation systems transmit highly precise geolocation information to GNSS receiving devices to determine its current location. The proposed multi-band RFSoC front-end digital baseband sample stream will be connected to a SDR-GNSS receiver in real-time. The open source GNSS-SDR project allows implementing a SDR receiver to perform global satellite navigation using the C++ language. It implements the GNSS receiver software by creating a graph where the nodes are signal processing blocks and the lines represent the dataflow between them and, for that reason, it is used in this project.
*Figure 1: GNSS constellations, bands and frequencies.*
*Figure 2: General block diagram GNSS-SDR open-source project.*

### RFSoC

ZYNQ Ultrascale+ RFSoC processor takes advantage of the high signal acquisition performance that Field Programmable Gate Arrays (FPGAs) provides and the computing power that Central Processing Units (CPUs) offers. A SoC is an integrated circuit that brings together all the necessary components to process the received signal on a single piece of silicon. The RFSoC device is mainly divided by two parts: the Processing System (PS) and the Programmable Logic (PL). The PS is the equivalent of the CPU and the PL of the FPGA. The PL can be reprogrammed using Very High Speed Integrated Circuit Hardware Description Language (VHDL). The integrated ADCs are capable of sampling signals up to 5 GSPS, and that is the reason why it is used for this project, since it is possible to sample radio signals directly from the antenna without any external front-end. Each ADC has a Digital Downconverter (DDC) to perform the translation of a high frequency RF signal to baseband. The PS executes instructions of an operating system and/or an application written with PYNQ. The PS incorporates the multiple processor cores of a Multi-Processor SoC (MPSoC). The architecture includes a quad-core APU, a dual-core RPU, a PMU and a CSU, and also contains local memories, interconnects and peripheral interfaces.
*Figure 3: RFSoC4x2 development board components.*

### Multi-band

A multi-band front-end implies that it is capable of simultaneously processing several bands, allowing the final device that receives not only to operate with different types of satellites, but also that the position estimates will be better, since it will be able to use more satellites at the same time. To obtain the desired bands, a first translation of the entire GNSS band to the baseband is made. Then the signal goes through different processing chains. Each one is responsible for transferring a single band to the baseband.
*Figure 4: Two translations to baseband to select GPS L1.*
*Figure 5: Multiple processing chains diagram.*

## Objectives
The main objective of this project is the design and the implementation of an advanced multi-band GNSS SDR front-end, equipped with the following features and specifications:
- No translation stage to IF.
- SDR
- Multi-band
- Easy update
- No sample losing

## SDK and Software frameworks
The Zynq Ultrascale+ RFSoC processor, being a SoC system, has several programming stages, which mainly differ in programming the PS, the PL and the connection between the two. While the PL requires several HDL-dedicated software, the PS and part of the processor connection are mainly implemented in Python through an open source framework called PYNQ.
*Figure 6: The different software layers of the RFSoC processor.*

## Design and Implementation
The direct RF sampling capability of RFSoC integrated circuits enables the implementation of a novel multi-band GNSS SDR front-end receiver. The available RF bandwidth is sufficient to simultaneously process all GNSS signals, using only one ADC from the RFSoC4x2. Figure 6 shows the ADC output signal processing chain that is composed of (left to right): the RFDC, the Frequency Translator (FT), the FIR IP core and the DMA. The GNSS signal goes through a series of transformations as it is processed by different blocks of the diagram:
1. ADC: The signal goes from being analog to digital from the ADC.
2. RFDC: The signal goes from being real to IQ complex and is translated to baseband, through which the complex multiplier and the NCO of the DDC of one of the dual tile receivers frequently move the signal from its original centre frequency to 0Hz. Then,the signal is filtered by the corresponding programmable decimator, reducing its sample rate.
3. Frequency Translator: A second baseband drop is produced from complex multipliers and NCOs so that the user can choose the desired frequency band within the one that had already been selected.
4. FIR filter: The second filtering and decimation process is done by the FIR IP core. In this stage, the signal passes through a Low Pass Filter (LPF) type FIR filter which occupies a bandwidth of half the number of samples per second that the user want the end of the reception chain to go to.
5. DMA: From the DMA the processed signal is sent to the CPU memory and from it, to the Ethernet port connected to the PS CPU and this will transfer the data to the device which will use the desired signal from the receiver.
*Figure 7: A single processing chain diagram.*

### PL
The PL scheme of the project can be mainly divided into two parts. The first part consists of processing the input signal using the hardware blocks provided by the RFSoC itself together with the base overlay. An
overlay is a programmable FPGA design that contain all the information about the hardware blocks called Intellectual Property (IP) cores and how they relate to each other as if it were a hardware library. The second part consists of using the set of IP cores of the BaseOverlay, and custom-made SDR IP cores coded with Vitis HLS to process the antenna input signal and extract the desired GNSS bands.
*Figure 8: RFSoC4x2 BaseOverlay hardware layer.*

#### _RFDC_
The RFDC IP core, is probably the most complex and characteristic block of an RFSoC, since from it all the functionalities related to the ADCs, DACs, DDCs and DUCs are configured. For this reason, it not only modifies the internal logic part of the processor that directs all the RF processes, but it also has to have a high temporal precision to not desynchronize any sample of the signal to be sent or received. The advantage of using the RFDC is that it configures in a simple and compact way both the functionalities to transfer the GNSS frequencies to baseband and those related to the programmable decimator.
*Figure 9: RF-ADC Tile hierarchy for the ZU48DR model.*
*Figure 10: RF-ADC Tile Configuration Vivado GUI.*
*Figure 11: RF-ADC Clocking Configuration Vivado GUI.*

#### _FT_
Once the received signal that has information from all GNSS bands is translated to baseband, filtered and decimated, it is time to select which particular GNSS carrier frequency should be received by applying a translation from the apparent IF in the global baseband signal to baseband (zeroIF). This frequency translation process can be instantiated several times to complete a multi-band front-end. After applying a second baseband
translation, the user can choose which GNSS frequency band they want to work with. In order to do this, it is necessary to pass the signal through a translation and decimation stages again. The first stage is based on programming a Frequency Translator from Vitis HLS and adapting the reception chain in Vivado to be able to control this new IP core correctly.
*Figure 12: Frequency Translator concept explanation.*

As the I component and the Q component of the complex signal processed by the RFDC come out through different ports, a multiplexed concatenation is carried out, since the Frequency Translator input is made through a single port. It is true that two input streams could are implemented, but thereby the ’std::complex’ data type would not are used, generating a possible desynchronization of the processed data. This multiplexed concatenation is carried out directly in VHDL from Vivado creating a VHDL model, since thereby the implementation of the block is completely optimized. Creating native VHDL blocks to optimize certain simple processes, such as the one described above, has been a resource that has been used on several occasions throughout the signal processing.

Moreover, an AXI GPIO IP core is added to control the state of the control flags. In this way, the FT can be controlled from the PS.
*Figure 13: AXI GPIO GUI.*

Finally, to be able to configure the Frequency Translator parameters as those of the AXI GPIO IP core via AXI through the PS, these ports have to add as slaves to the PS block named ’zynq_ultra_ps_e_0’ in the memory map, as shown in Figure 14. To make this connection, the option provided by Vivado is used so that the wiring is automatically generated from the port without connecting to the specified IP core. It should been sured that the wiring does not pass through any other set of blocks than the desire done. If this occurs, once the new IP core is mapped, the relevant wiring should be eliminated and the desired port should be manually connected to the closest AXI Interconnect IP core where the connection of a new port is created. Thereby, when the specific driver for each block is created, the PS will have the memory address to whic hit has to send the information.
*Figure 14: Frequency Translator memory map.*

#### _FIR_
The Vivado FIR IP core it is responsible for filtering and decimating the signal once it has been transferred to baseband for the second time. The design of its coeficients was carried out using MATLAB’s ’Basic FIR Filter’ tool and the configuration via the Vivado GUI, changing the Super Sample Rate (SSR) and the decimation factor.
*Figure 15: FIR filter IP core.*
*Figure 16: Designing the filter in MATLAB Filter Design & Analysis Tool.*
*Figure 17: Filter Coefficients and Filter Specification FIR GUI panel.*
*Figure 18: Interleaved Channel, Parallel Channel and Hardware Oversampling FIR GUI panel.*
*Figure 19: Summary FIR GUI panel.*

#### _Chain Selector_
To create a system that allows working with several bands at the same time, a sample of each band should be provided to the final device consecutively. In other words, for the final device to be equipped with satellite navigation using several GNSS bands at the same time, it is necessary for the front-end to send it the data of the desired receiving chains consecutively. For this reason, a Chain Selector is implemented in Vitis HLS as shown in Figure 20.
*Figure 20: Chain Selector IP core.*

#### _DMA_

### PS
At the beginning, the overlay is loaded, which contains all the instances of the generated IP cores and the drivers to make communication possible between the hardware, software and application layers. The GNSS bands to receive are selected by configuring the Chain Selector. After the signal has been processed by the PL, the PS DMA transfers the data received from the PL DMA to the Ethernet port of the RFSoC4x2. Furthermore, the processed data is transmitted as User Datagram Protocol (UDP) packets to the specified IP and port through the Ethernet cable to the final device which performs satellite navigation.
*Figure 21: Packet transmission diagram.*


## How to use it

As a summary, a flowchart is made, which defines the various states that the RFSoC4x2 and its control go through to end up obtaining positioning with the final device.
*Figure 22: General flowchart of the project.*

## Conclusion

By analysing in detail the satellite navigation signals and the RFSoC4x2 development board, equipped with a Zynq Ultrascale+ RFSoC processor, a novel flexible multi-band GNSS SDR front-end was designed and implemented. This project demonstrated that:
-   The direct-RF sampling technique allows implementing an 'universal' multi-band front-end for GNSS. It is possible to process a wideband signal with a carrier frequency in the order of 1-2 GHz by sampling it directly with a sampling frequency of 3-4 GSPS, without having an IF stage using an ADC provided by the RFSoC4x2 development board. One DDC can obtain the multiple GNSS bands necessary for the receiver. The front-end receives signals which are downconverted correctly through the RFDC and the Frequency Translator.
-   Adding new bands with this system becomes a simple firmware update. Instead of a conventional analog front-ends, with the implemented front-end, adding a new GNSS band only requires instantiating a new processing chain in the PL in Vivado and, with no hardware modifications.
-   By using high-level implementation tools, a new custom IP core can be designed, implemented, and controlled very quickly. A straightforward process can be followed to implement a new custom IP core, firstly, its behaviour is programmed and exported in Vitis HLS, and it is instantiated and connected in Vivado, then, the files that contain the behaviour of the hardware layer are exported, and the IP core driver is created in the software layer and, finally, the overlay is loaded, and the IP core is configured.

## Future work

## Bibliography


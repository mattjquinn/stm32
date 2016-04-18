# STM32 Template/Projects

This repo is a combination of the original STM32 template, combined with my own (minor) deviations and chapter implementations. The sections below are the step by step instructions I used to start programming my STM32. The final section at the end is the original README authored by the author of the STM32 Template, from which this repo was forked.

Retrieving my clone of STM32-Template
=====================================
- sudo apt-get install git
- mkdir ~/stm32
- cd ~/stm32
- git clone https://github.com/mquinn/STM32.git

Install stlink
==============
- sudo apt-get install vim
- cd ~/stm32
- git clone https://github.com/texane/stlink.git
- Began following README instructions in stlink repo.
- sudo apt-get install libusb-1.0 (NOTE: ensure this includes -dev package)
- sudo apt-get install pkg-config
- cd stlink
- For STLINKv1:
	- sudo cp stlink_v1.modprobe.conf /etc/modprobe.d
	- sudo modprobe -r usb-storage && modprobe usb-storage (this error'ed out with "Operation not permitted.")
- sudo apt-get install autoconf
- ./autogen.sh
- ./configure
- make

Install STM32 Peripheral Library
================================
- Downloaded via: http://www.st.com/web/en/catalog/tools/PF257890
- Moved unzipped folder to /opt (final path: /opt/STM32F10x_StdPeriph_Lib_V3.5.0)

Install ARM compiler/debugger
=============================
sudo apt-get -o Dpkg::Options::="--force-overwrite" install gdb-arm-none-eabi
	- For justification for extra flag, see: http://askubuntu.com/questions/596302/e-sub-process-usr-bin-dpkg-returned-an-error-code-1-problem-with-dpkg

Final configuration tasks
=========================
- Modified TOOLROOT in STM32-Template/Makefile.common to point to /usr/bin
- Modified LIBROOT in STM32-Template/Makefile.common to point to /opt/STM32F10x_StdPeriph_Lib_V3.5.0
- To test:
  - Scrolled to Chapter 3 of "Discovering the STM32 Microcontroller"
  - Plugged in STM32, passed through to VirtualBox
  - In first terminal:
    - cd ~/stm32/stlink
    - sudo ./st-util -1 (connected successfully to device)
  - In second terminal:
    - cd ~/stm32/STM32-Template
    - cd Demo
    - make
    - arm-none-eabi-gdb Demo.elf
      - (gdb) target extended-remote :4242
      - (gdb) load
      - (gdb) continue  -> red light begins flashing on board, indicating successful execution

Original STM32-Template README
==============================

A Build template for projects using the stm32vl discovery board, 
CodeSourcery gnu toolchain, and the STM32F10x Standard Peripheral Library.

To test:

   (1) install the toolchain and libarary.
   (2) change the TOOLROOT and LIBROOT paths in Makefile.common
   (3) cd to Demo
   (4) type make

To create new projects

   (1) clone the Demo directory (name the directory appropriately)
   (2) change TEMPLATEROOT in the cloned makefile to point to the 
       template directory
   (3) modify as needed, adding any needed library objects to the OBJ 
       list in the Makefile


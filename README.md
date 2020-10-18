# PPVM - Plug and Play Virtual Machine

A really simple virtual machine developed originally to a college project, it runs on top of an ESP32 micro controller and works as an emulator for an non existent hardware, based on the Von Neumann Architecture.



### Tools used:

* ESP-IDF;
* Eclipse IDE.



### Main features:

* 16-bit architecture, 19 registers;
* 6kB addressable memory;
* 37 different instructions;
* Connection to virtual external devices.



The architecture of the virtual machine was very simplified by the use of meta-programming, namely C macros, hence all the instructions' implementation can be seen on the **macros.h** file, that also works as a very basic form of documentation, by now.

This project, currently, is nothing more than a proof of concept, and needs a lot of improvements, including the documentation itself, in order to become solid, all help is welcome.
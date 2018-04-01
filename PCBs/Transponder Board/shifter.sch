EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:a2135-h
LIBS:ap2204k-5
LIBS:arduino_nano
LIBS:fgpmmopa6h
LIBS:Recovery Board Parts
LIBS:Recovery Board-cache
LIBS:sot-223
LIBS:instrumentation_board_parts
LIBS:Transponder-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PI4ULS5V201TAEX U?
U 1 1 5AB9CBBE
P 5300 3600
F 0 "U?" H 5300 4150 60  0000 C CNN
F 1 "PI4ULS5V201TAEX" H 5300 3400 60  0000 C CNN
F 2 "" H 5300 3600 60  0001 C CNN
F 3 "" H 5300 3600 60  0001 C CNN
	1    5300 3600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5AB9CC15
P 6100 3800
F 0 "C?" H 6125 3900 50  0000 L CNN
F 1 "0.1uF" H 6125 3700 50  0000 L CNN
F 2 "" H 6138 3650 50  0001 C CNN
F 3 "" H 6100 3800 50  0001 C CNN
	1    6100 3800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5AB9CC50
P 4550 3600
F 0 "C?" H 4575 3700 50  0000 L CNN
F 1 "0.1uF" H 4575 3500 50  0000 L CNN
F 2 "" H 4588 3450 50  0001 C CNN
F 3 "" H 4550 3600 50  0001 C CNN
	1    4550 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3250 6150 3250
Wire Wire Line
	6100 3250 6100 3650
Wire Wire Line
	4550 3450 4550 3250
Wire Wire Line
	4500 3250 4850 3250
$Comp
L GND #PWR?
U 1 1 5AB9CCC7
P 6100 3950
F 0 "#PWR?" H 6100 3700 50  0001 C CNN
F 1 "GND" H 6100 3800 50  0000 C CNN
F 2 "" H 6100 3950 50  0001 C CNN
F 3 "" H 6100 3950 50  0001 C CNN
	1    6100 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB9CD06
P 4800 3750
F 0 "#PWR?" H 4800 3500 50  0001 C CNN
F 1 "GND" H 4800 3600 50  0000 C CNN
F 2 "" H 4800 3750 50  0001 C CNN
F 3 "" H 4800 3750 50  0001 C CNN
	1    4800 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB9CD20
P 4550 3750
F 0 "#PWR?" H 4550 3500 50  0001 C CNN
F 1 "GND" H 4550 3600 50  0000 C CNN
F 2 "" H 4550 3750 50  0001 C CNN
F 3 "" H 4550 3750 50  0001 C CNN
	1    4550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3750 4800 3550
Wire Wire Line
	4800 3550 4850 3550
Text HLabel 4500 3250 0    60   Input ~ 0
VccA
Text HLabel 6150 3250 2    60   Input ~ 0
VccB
Text HLabel 5750 3450 2    60   Input ~ 0
B
Text HLabel 4850 3350 0    60   Input ~ 0
A
NoConn ~ 5750 3350
NoConn ~ 4850 3450
Connection ~ 4550 3250
Connection ~ 6100 3250
Wire Wire Line
	5750 3550 5750 4000
Wire Wire Line
	5750 4000 4350 4000
Wire Wire Line
	4350 4000 4350 3400
Wire Wire Line
	4350 3400 4550 3400
Connection ~ 4550 3400
$EndSCHEMATC

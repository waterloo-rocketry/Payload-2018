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
LIBS:instrumentation_board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 10
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
L XC6201P302MR-G U1
U 1 1 5AB2EE92
P 5050 3350
F 0 "U1" H 5050 3650 60  0000 C CNN
F 1 "XC6201P302MR-G" H 5050 3250 60  0000 C CNN
F 2 "" H 5050 3350 60  0001 C CNN
F 3 "" H 5050 3350 60  0001 C CNN
	1    5050 3350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5AB2EE9A
P 4100 3350
F 0 "C1" H 4125 3450 50  0000 L CNN
F 1 "1uF" H 4125 3250 50  0000 L CNN
F 2 "" H 4138 3200 50  0001 C CNN
F 3 "" H 4100 3350 50  0001 C CNN
	1    4100 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 5AB2EEA1
P 4100 3500
F 0 "#PWR16" H 4100 3250 50  0001 C CNN
F 1 "GND" H 4100 3350 50  0000 C CNN
F 2 "" H 4100 3500 50  0001 C CNN
F 3 "" H 4100 3500 50  0001 C CNN
	1    4100 3500
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AB2EEA7
P 5650 3350
F 0 "C2" H 5675 3450 50  0000 L CNN
F 1 "1uF" H 5675 3250 50  0000 L CNN
F 2 "" H 5688 3200 50  0001 C CNN
F 3 "" H 5650 3350 50  0001 C CNN
	1    5650 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 5AB2EEAE
P 5650 3500
F 0 "#PWR17" H 5650 3250 50  0001 C CNN
F 1 "GND" H 5650 3350 50  0000 C CNN
F 2 "" H 5650 3500 50  0001 C CNN
F 3 "" H 5650 3500 50  0001 C CNN
	1    5650 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 5AB2EEB4
P 4450 3400
F 0 "#PWR18" H 4450 3150 50  0001 C CNN
F 1 "GND" H 4450 3250 50  0000 C CNN
F 2 "" H 4450 3400 50  0001 C CNN
F 3 "" H 4450 3400 50  0001 C CNN
	1    4450 3400
	1    0    0    -1  
$EndComp
NoConn ~ 5450 3350
Wire Wire Line
	4600 3250 4450 3250
Wire Wire Line
	4450 3250 4450 3400
Connection ~ 4100 3150
Wire Wire Line
	4100 3150 4100 3200
Wire Wire Line
	3850 3150 4100 3150
Wire Wire Line
	4100 3150 4600 3150
Text HLabel 3850 3150 0    60   Input ~ 0
7.4V
Text HLabel 5850 3150 2    60   Input ~ 0
3V
Wire Wire Line
	5450 3150 5650 3150
Wire Wire Line
	5650 3150 5850 3150
Wire Wire Line
	5650 3200 5650 3150
Connection ~ 5650 3150
NoConn ~ 4600 3350
$EndSCHEMATC

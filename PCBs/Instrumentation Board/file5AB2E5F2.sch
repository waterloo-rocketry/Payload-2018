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
LIBS:instrumentation_board_parts
LIBS:instrumentation_board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 4
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
P 3650 3350
F 0 "C1" H 3675 3450 50  0000 L CNN
F 1 "1uF" H 3675 3250 50  0000 L CNN
F 2 "" H 3688 3200 50  0001 C CNN
F 3 "" H 3650 3350 50  0001 C CNN
	1    3650 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB2EEA1
P 3650 3500
F 0 "#PWR?" H 3650 3250 50  0001 C CNN
F 1 "GND" H 3650 3350 50  0000 C CNN
F 2 "" H 3650 3500 50  0001 C CNN
F 3 "" H 3650 3500 50  0001 C CNN
	1    3650 3500
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AB2EEA7
P 3850 3700
F 0 "C2" H 3875 3800 50  0000 L CNN
F 1 "1uF" H 3875 3600 50  0000 L CNN
F 2 "" H 3888 3550 50  0001 C CNN
F 3 "" H 3850 3700 50  0001 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB2EEAE
P 3850 3850
F 0 "#PWR?" H 3850 3600 50  0001 C CNN
F 1 "GND" H 3850 3700 50  0000 C CNN
F 2 "" H 3850 3850 50  0001 C CNN
F 3 "" H 3850 3850 50  0001 C CNN
	1    3850 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB2EEB4
P 5600 3300
F 0 "#PWR?" H 5600 3050 50  0001 C CNN
F 1 "GND" H 5600 3150 50  0000 C CNN
F 2 "" H 5600 3300 50  0001 C CNN
F 3 "" H 5600 3300 50  0001 C CNN
	1    5600 3300
	1    0    0    -1  
$EndComp
NoConn ~ 5450 3350
NoConn ~ 5450 3150
NoConn ~ 4600 3250
Wire Wire Line
	4350 3700 4800 3700
Wire Wire Line
	4350 3350 4350 3700
Wire Wire Line
	5450 3250 5600 3250
Wire Wire Line
	5600 3250 5600 3300
Connection ~ 4350 3550
Wire Wire Line
	3850 3550 4350 3550
Connection ~ 3650 3150
Wire Wire Line
	3650 3150 3650 3200
Wire Wire Line
	3550 3150 4600 3150
Wire Wire Line
	4600 3350 4350 3350
Text HLabel 3550 3150 0    60   Input ~ 0
7.4V
Text HLabel 4800 3700 2    60   Input ~ 0
3V
$EndSCHEMATC

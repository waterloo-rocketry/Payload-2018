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
LIBS:Transponder-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
L Arduino_Nano A1
U 1 1 5AA8875C
P 1900 5050
F 0 "A1" H 1900 5050 60  0000 C CNN
F 1 "Arduino_Nano" H 1900 5200 60  0000 C CNN
F 2 "arduino:Arduino_Nano" H 1900 5050 60  0001 C CNN
F 3 "" H 1900 5050 60  0000 C CNN
	1    1900 5050
	1    0    0    -1  
$EndComp
Text GLabel 1250 4400 0    60   Input ~ 0
7.4V
$Comp
L GND #PWR01
U 1 1 5AA887D5
P 1250 6250
F 0 "#PWR01" H 1250 6000 50  0001 C CNN
F 1 "GND" H 1250 6100 50  0000 C CNN
F 2 "" H 1250 6250 50  0001 C CNN
F 3 "" H 1250 6250 50  0001 C CNN
	1    1250 6250
	1    0    0    -1  
$EndComp
$Comp
L XBee-S2C U3
U 1 1 5AA887F8
P 9000 2250
F 0 "U3" H 8900 3050 60  0000 C CNN
F 1 "XBee-S2C" H 9000 1450 60  0000 C CNN
F 2 "SparkFun-RF:XBEE-1" H 8600 2200 60  0001 C CNN
F 3 "" H 8600 2200 60  0001 C CNN
	1    9000 2250
	1    0    0    -1  
$EndComp
$Comp
L MicroSDBreakout U2
U 1 1 5AA8882F
P 7350 4000
F 0 "U2" H 7350 4350 60  0000 C CNN
F 1 "MicroSDBreakout" H 7350 3700 60  0000 C CNN
F 2 "adafruit:adafruit254" H 7500 4000 60  0001 C CNN
F 3 "" H 7500 4000 60  0001 C CNN
	1    7350 4000
	1    0    0    -1  
$EndComp
Text GLabel 1250 4500 0    60   Input ~ 0
5V
Text GLabel 6850 3850 0    60   Input ~ 0
5V
$Comp
L GND #PWR02
U 1 1 5AA88B2D
P 6550 4300
F 0 "#PWR02" H 6550 4050 50  0001 C CNN
F 1 "GND" H 6550 4150 50  0000 C CNN
F 2 "" H 6550 4300 50  0001 C CNN
F 3 "" H 6550 4300 50  0001 C CNN
	1    6550 4300
	1    0    0    -1  
$EndComp
Text GLabel 6850 4150 0    60   Input ~ 0
SLK
Text GLabel 7850 3850 2    60   Input ~ 0
MISO
Text GLabel 7850 3950 2    60   Input ~ 0
MOSI
Text GLabel 7850 4050 2    60   Input ~ 0
SS
Text GLabel 2600 5000 2    60   Input ~ 0
SS
Text GLabel 2600 5100 2    60   Input ~ 0
MOSI
Text GLabel 2600 5200 2    60   Input ~ 0
MISO
Text GLabel 2600 5300 2    60   Input ~ 0
SLK
$Comp
L R-78E3.3-0.5 U1
U 1 1 5AA8916C
P 4350 1050
F 0 "U1" H 4350 1500 60  0000 C CNN
F 1 "R-78E3.3-0.5" H 4350 450 60  0000 C CNN
F 2 "sip:SIP3Large" H 4350 1050 60  0001 C CNN
F 3 "" H 4350 1050 60  0001 C CNN
	1    4350 1050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5AA892BD
P 4350 1350
F 0 "#PWR03" H 4350 1100 50  0001 C CNN
F 1 "GND" H 4350 1200 50  0000 C CNN
F 2 "" H 4350 1350 50  0001 C CNN
F 3 "" H 4350 1350 50  0001 C CNN
	1    4350 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5AA8930C
P 3550 1350
F 0 "#PWR04" H 3550 1100 50  0001 C CNN
F 1 "GND" H 3550 1200 50  0000 C CNN
F 2 "" H 3550 1350 50  0001 C CNN
F 3 "" H 3550 1350 50  0001 C CNN
	1    3550 1350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5AA89337
P 3550 1100
F 0 "C1" H 3575 1200 50  0000 L CNN
F 1 "10uF" H 3575 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3588 950 50  0001 C CNN
F 3 "" H 3550 1100 50  0001 C CNN
	1    3550 1100
	1    0    0    -1  
$EndComp
Text GLabel 3300 900  0    60   Input ~ 0
7.4V
$Comp
L C C2
U 1 1 5AA894E2
P 5150 1100
F 0 "C2" H 5175 1200 50  0000 L CNN
F 1 "10uF" H 5175 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5188 950 50  0001 C CNN
F 3 "" H 5150 1100 50  0001 C CNN
	1    5150 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5AA8954D
P 5150 1350
F 0 "#PWR05" H 5150 1100 50  0001 C CNN
F 1 "GND" H 5150 1200 50  0000 C CNN
F 2 "" H 5150 1350 50  0001 C CNN
F 3 "" H 5150 1350 50  0001 C CNN
	1    5150 1350
	1    0    0    -1  
$EndComp
Text GLabel 7900 1900 0    60   Input ~ 0
XBEE-DOUT
Text GLabel 6050 2150 0    60   Input ~ 0
XBEE-DIN
$Comp
L R R2
U 1 1 5AA89647
P 6300 2650
F 0 "R2" V 6380 2650 50  0000 C CNN
F 1 "2k" V 6300 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6230 2650 50  0001 C CNN
F 3 "" H 6300 2650 50  0001 C CNN
	1    6300 2650
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5AA8967B
P 6300 3200
F 0 "R1" V 6380 3200 50  0000 C CNN
F 1 "3k" V 6300 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6230 3200 50  0001 C CNN
F 3 "" H 6300 3200 50  0001 C CNN
	1    6300 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5AA89745
P 6300 3500
F 0 "#PWR06" H 6300 3250 50  0001 C CNN
F 1 "GND" H 6300 3350 50  0000 C CNN
F 2 "" H 6300 3500 50  0001 C CNN
F 3 "" H 6300 3500 50  0001 C CNN
	1    6300 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5AA897AD
P 7800 2900
F 0 "#PWR07" H 7800 2650 50  0001 C CNN
F 1 "GND" H 7800 2750 50  0000 C CNN
F 2 "" H 7800 2900 50  0001 C CNN
F 3 "" H 7800 2900 50  0001 C CNN
	1    7800 2900
	1    0    0    -1  
$EndComp
Text GLabel 1550 1700 2    60   Input ~ 0
7.4V
$Comp
L GND #PWR08
U 1 1 5AA89F41
P 2100 800
F 0 "#PWR08" H 2100 550 50  0001 C CNN
F 1 "GND" H 2100 650 50  0000 C CNN
F 2 "" H 2100 800 50  0001 C CNN
F 3 "" H 2100 800 50  0001 C CNN
	1    2100 800 
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5AA89FA6
P 1350 1000
F 0 "J1" H 1350 1100 50  0000 C CNN
F 1 "Conn_01x02" H 1350 800 50  0000 C CNN
F 2 "Connectors_JST:JST_PH_B2B-PH-K_02x2.00mm_Straight" H 1350 1000 50  0001 C CNN
F 3 "" H 1350 1000 50  0001 C CNN
	1    1350 1000
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5AA8A05F
P 1350 1700
F 0 "J2" H 1350 1800 50  0000 C CNN
F 1 "Conn_01x02" H 1350 1500 50  0000 C CNN
F 2 "molex:molex_kk_22-23-2021" H 1350 1700 50  0001 C CNN
F 3 "" H 1350 1700 50  0001 C CNN
	1    1350 1700
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J3
U 1 1 5AA8A30C
P 1350 2500
F 0 "J3" H 1350 2600 50  0000 C CNN
F 1 "Conn_01x02" H 1350 2300 50  0000 C CNN
F 2 "molex:molex_kk_22-23-2021" H 1350 2500 50  0001 C CNN
F 3 "" H 1350 2500 50  0001 C CNN
	1    1350 2500
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 5AA8A351
P 1350 2900
F 0 "J4" H 1350 3000 50  0000 C CNN
F 1 "Conn_01x02" H 1350 2700 50  0000 C CNN
F 2 "molex:molex_kk_22-23-2021" H 1350 2900 50  0001 C CNN
F 3 "" H 1350 2900 50  0001 C CNN
	1    1350 2900
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J5
U 1 1 5AA8A395
P 1350 3350
F 0 "J5" H 1350 3450 50  0000 C CNN
F 1 "Conn_01x02" H 1350 3150 50  0000 C CNN
F 2 "molex:molex_kk_22-23-2021" H 1350 3350 50  0001 C CNN
F 3 "" H 1350 3350 50  0001 C CNN
	1    1350 3350
	-1   0    0    1   
$EndComp
Text GLabel 1550 2400 2    60   Input ~ 0
5V
Text GLabel 1550 2800 2    60   Input ~ 0
5V
Text GLabel 1550 3250 2    60   Input ~ 0
5V
Text GLabel 3650 5400 2    60   Input ~ 0
D2
Text GLabel 3350 5500 2    60   Input ~ 0
D3
Text GLabel 3050 5600 2    60   Input ~ 0
D4
Text GLabel 1550 2500 2    60   Input ~ 0
D2
Text GLabel 1550 2900 2    60   Input ~ 0
D3
Text GLabel 1550 3350 2    60   Input ~ 0
D4
$Comp
L R R4
U 1 1 5AA8AA2D
P 3300 5650
F 0 "R4" V 3400 5650 50  0000 C CNN
F 1 "10k" V 3300 5650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3230 5650 50  0001 C CNN
F 3 "" H 3300 5650 50  0001 C CNN
	1    3300 5650
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5AA8AB66
P 3000 5750
F 0 "R3" V 3100 5750 50  0000 C CNN
F 1 "10k" V 3000 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2930 5750 50  0001 C CNN
F 3 "" H 3000 5750 50  0001 C CNN
	1    3000 5750
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5AA8A8A4
P 3600 5550
F 0 "R5" V 3680 5550 50  0000 C CNN
F 1 "10k" V 3600 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3530 5550 50  0001 C CNN
F 3 "" H 3600 5550 50  0001 C CNN
	1    3600 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5AA8AFB2
P 3000 5900
F 0 "#PWR09" H 3000 5650 50  0001 C CNN
F 1 "GND" H 3000 5750 50  0000 C CNN
F 2 "" H 3000 5900 50  0001 C CNN
F 3 "" H 3000 5900 50  0001 C CNN
	1    3000 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5AA8AFED
P 3300 5800
F 0 "#PWR010" H 3300 5550 50  0001 C CNN
F 1 "GND" H 3300 5650 50  0000 C CNN
F 2 "" H 3300 5800 50  0001 C CNN
F 3 "" H 3300 5800 50  0001 C CNN
	1    3300 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5AA8B028
P 3600 5700
F 0 "#PWR011" H 3600 5450 50  0001 C CNN
F 1 "GND" H 3600 5550 50  0000 C CNN
F 2 "" H 3600 5700 50  0001 C CNN
F 3 "" H 3600 5700 50  0001 C CNN
	1    3600 5700
	1    0    0    -1  
$EndComp
Text GLabel 2600 4000 2    60   Input ~ 0
XBEE-DIN
Text GLabel 5500 900  2    60   Input ~ 0
3.3V
Text GLabel 6400 1800 0    60   Input ~ 0
3.3V
$Comp
L Conn_01x09 J6
U 1 1 5AB72699
P 6150 5450
F 0 "J6" H 6150 5950 50  0000 C CNN
F 1 "Conn_01x09" H 6150 4950 50  0000 C CNN
F 2 "screwTerminals:VI0921550000G" H 6150 5450 50  0001 C CNN
F 3 "" H 6150 5450 50  0001 C CNN
	1    6150 5450
	1    0    0    1   
$EndComp
$Comp
L GND #PWR012
U 1 1 5AB727EB
P 5850 5900
F 0 "#PWR012" H 5850 5650 50  0001 C CNN
F 1 "GND" H 5850 5750 50  0000 C CNN
F 2 "" H 5850 5900 50  0001 C CNN
F 3 "" H 5850 5900 50  0001 C CNN
	1    5850 5900
	1    0    0    -1  
$EndComp
Text GLabel 5950 5750 0    60   Input ~ 0
5V
$Comp
L GND #PWR013
U 1 1 5AB72A73
P 5300 5900
F 0 "#PWR013" H 5300 5650 50  0001 C CNN
F 1 "GND" H 5300 5750 50  0000 C CNN
F 2 "" H 5300 5900 50  0001 C CNN
F 3 "" H 5300 5900 50  0001 C CNN
	1    5300 5900
	1    0    0    -1  
$EndComp
Text GLabel 5950 5350 0    60   Input ~ 0
LCD_D4
Text GLabel 5950 5250 0    60   Input ~ 0
LCD_D5
Text GLabel 5950 5150 0    60   Input ~ 0
LCD_D6
Text GLabel 5950 5050 0    60   Input ~ 0
LCD_D7
Text Notes 6700 5900 2    60   ~ 0
LCD Pin 1
Text Notes 6700 5800 2    60   ~ 0
LCD Pin 2
Text Notes 6700 5700 2    60   ~ 0
LCD pin 4
Text Notes 6700 5600 2    60   ~ 0
LCD pin 5
Text Notes 6700 5500 2    60   ~ 0
LCD pin 6
Text Notes 6750 5400 2    60   ~ 0
LCD pin 11
Text Notes 6750 5300 2    60   ~ 0
LCD pin 12
Text Notes 6750 5200 2    60   ~ 0
LCD pin 13
Text Notes 6750 5100 2    60   ~ 0
LCD pin 14
Text GLabel 2600 4500 2    60   Input ~ 0
LCD_D4
Text GLabel 2600 4400 2    60   Input ~ 0
LCD_D5
Text GLabel 2600 4300 2    60   Input ~ 0
LCD_D6
Text GLabel 2600 4200 2    60   Input ~ 0
LCD_D7
Text GLabel 5950 5450 0    60   Input ~ 0
LCD_H/L_EN
Text GLabel 5950 5650 0    60   Input ~ 0
LCD_H/L_RS
Text GLabel 2600 4600 2    60   Input ~ 0
LCD_H/L_EN
Text GLabel 2600 4700 2    60   Input ~ 0
LCD_H/L_RS
Text Notes 850  1100 0    60   ~ 0
Battery 1
Text Notes 950  1700 0    60   ~ 0
Switch
$Comp
L C C5
U 1 1 5AB9BB4C
P 7150 2000
F 0 "C5" H 7175 2100 50  0000 L CNN
F 1 "8.2pF" H 7175 1900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7188 1850 50  0001 C CNN
F 3 "" H 7150 2000 50  0001 C CNN
	1    7150 2000
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5AB9BC07
P 6850 2000
F 0 "C4" H 6875 2100 50  0000 L CNN
F 1 "1uF" H 6875 1900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6888 1850 50  0001 C CNN
F 3 "" H 6850 2000 50  0001 C CNN
	1    6850 2000
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5AB9BC5D
P 6550 2000
F 0 "C3" H 6575 2100 50  0000 L CNN
F 1 "10uF" H 6575 1900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6588 1850 50  0001 C CNN
F 3 "" H 6550 2000 50  0001 C CNN
	1    6550 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5AB9C29E
P 6550 2150
F 0 "#PWR014" H 6550 1900 50  0001 C CNN
F 1 "GND" H 6550 2000 50  0000 C CNN
F 2 "" H 6550 2150 50  0001 C CNN
F 3 "" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5AB9C2E8
P 6850 2150
F 0 "#PWR015" H 6850 1900 50  0001 C CNN
F 1 "GND" H 6850 2000 50  0000 C CNN
F 2 "" H 6850 2150 50  0001 C CNN
F 3 "" H 6850 2150 50  0001 C CNN
	1    6850 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5AB9C332
P 7150 2150
F 0 "#PWR016" H 7150 1900 50  0001 C CNN
F 1 "GND" H 7150 2000 50  0000 C CNN
F 2 "" H 7150 2150 50  0001 C CNN
F 3 "" H 7150 2150 50  0001 C CNN
	1    7150 2150
	1    0    0    -1  
$EndComp
$Sheet
S 3450 3850 700  350 
U 5AB9CB76
F0 "shifter" 60
F1 "shifter.sch" 60
F2 "VccA" I L 3450 3950 60 
F3 "VccB" I R 4150 3950 60 
F4 "B" I R 4150 4100 60 
F5 "A" I L 3450 4100 60 
$EndSheet
Text GLabel 3450 3950 0    60   Input ~ 0
5V
Text GLabel 4150 3950 2    60   Input ~ 0
3.3V
Text GLabel 4150 4100 2    60   Input ~ 0
XBEE-DOUT
$Comp
L Conn_01x02 J7
U 1 1 5AC4138A
P 1350 650
F 0 "J7" H 1350 750 50  0000 C CNN
F 1 "Conn_01x02" H 1350 450 50  0000 C CNN
F 2 "Connectors_JST:JST_PH_B2B-PH-K_02x2.00mm_Straight" H 1350 650 50  0001 C CNN
F 3 "" H 1350 650 50  0001 C CNN
	1    1350 650 
	-1   0    0    -1  
$EndComp
Text Notes 850  750  0    60   ~ 0
Battery 2
Wire Wire Line
	1250 5950 1250 6250
Connection ~ 1250 6050
Wire Wire Line
	6850 4050 6550 4050
Wire Wire Line
	6550 4050 6550 4300
Wire Wire Line
	3550 950  3550 900 
Wire Wire Line
	3300 900  3800 900 
Wire Wire Line
	3550 1250 3550 1350
Connection ~ 3550 900 
Wire Wire Line
	5150 950  5150 900 
Connection ~ 5150 900 
Wire Wire Line
	5150 1350 5150 1250
Wire Wire Line
	6050 2150 6300 2150
Wire Wire Line
	6300 2150 6300 2500
Wire Wire Line
	6300 2800 6300 3050
Wire Wire Line
	6300 2950 7700 2950
Wire Wire Line
	7700 2950 7700 2000
Wire Wire Line
	7700 2000 7900 2000
Connection ~ 6300 2950
Wire Wire Line
	6300 3500 6300 3350
Wire Wire Line
	7800 2900 7800 2700
Wire Wire Line
	7800 2700 7900 2700
Wire Wire Line
	2600 5400 3650 5400
Connection ~ 3600 5400
Wire Wire Line
	2600 5500 3350 5500
Connection ~ 3300 5500
Wire Wire Line
	2600 5600 3050 5600
Connection ~ 3000 5600
Wire Wire Line
	4900 900  5500 900 
Wire Wire Line
	5850 5900 5850 5850
Wire Wire Line
	5850 5850 5950 5850
Wire Wire Line
	5300 5900 5300 5550
Wire Wire Line
	5300 5550 5950 5550
Wire Wire Line
	6400 1800 7900 1800
Wire Wire Line
	6550 1850 6550 1800
Connection ~ 6550 1800
Wire Wire Line
	6850 1850 6850 1800
Connection ~ 6850 1800
Wire Wire Line
	7150 1850 7150 1800
Connection ~ 7150 1800
Wire Wire Line
	2600 4100 3450 4100
Wire Wire Line
	1550 1000 1750 1000
Wire Wire Line
	1750 1600 1550 1600
Wire Wire Line
	1550 1100 1750 1100
Wire Wire Line
	1750 1100 1750 1600
Wire Wire Line
	1550 650  2100 650 
Wire Wire Line
	2100 650  2100 800 
Wire Wire Line
	1750 1000 1750 750 
Wire Wire Line
	1750 750  1550 750 
$EndSCHEMATC

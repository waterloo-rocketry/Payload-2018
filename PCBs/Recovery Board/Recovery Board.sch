EESchema Schematic File Version 2
LIBS:Recovery Board-rescue
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
LIBS:arduino_nano
LIBS:fgpmmopa6h
LIBS:sot-223
LIBS:Placeholders
LIBS:Recovery Board Parts
LIBS:ap2204k-5
LIBS:Recovery Board-cache
LIBS:instrumentation_board_parts
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
L Arduino_Nano-RESCUE-Recovery_Board A1
U 1 1 5A446A9A
P 2550 5400
F 0 "A1" H 2550 5400 60  0000 C CNN
F 1 "Arduino_Nano" H 2550 5550 60  0000 C CNN
F 2 "Modules:Arduino_Nano" H 2550 5400 60  0000 C CNN
F 3 "" H 2550 5400 60  0000 C CNN
	1    2550 5400
	1    0    0    -1  
$EndComp
Text GLabel 8200 2400 2    60   Input Italic 0
GoPro_Power
Text GLabel 8200 2050 2    60   Input Italic 0
Intrument_Arduino_Power
$Comp
L XBee-S2C X1
U 1 1 5A767C06
P 9800 5400
F 0 "X1" H 9700 6200 60  0000 C CNN
F 1 "XBee-S2C" H 9800 4600 60  0000 C CNN
F 2 "SparkFun-RF:XBEE-1" H 9400 5350 60  0001 C CNN
F 3 "" H 9400 5350 60  0001 C CNN
	1    9800 5400
	1    0    0    -1  
$EndComp
Text GLabel 4750 4450 2    60   Input Italic 0
XBEE-DOUT
Text GLabel 7350 5200 0    60   Input Italic 0
XBEE-DIN
Text GLabel 8700 5050 0    60   Input Italic 0
XBEE-DOUT
Text GLabel 3250 6150 2    60   Input Italic 0
SDA
Text GLabel 3250 6250 2    60   Input Italic 0
SCL
Wire Wire Line
	7800 4100 8700 4100
$Comp
L CPC1002N S1
U 1 1 5A8B1335
P 6800 2200
F 0 "S1" H 6800 2600 60  0000 C CNN
F 1 "CPC1002N" H 6750 1800 60  0000 C CNN
F 2 "PayloadBoards:CPC1002NTR" H 6850 2200 60  0001 C CNN
F 3 "" H 6850 2200 60  0001 C CNN
	1    6800 2200
	1    0    0    -1  
$EndComp
Text GLabel 1900 4750 0    60   Input ~ 0
7.4V
Wire Wire Line
	5450 5650 3250 5650
$Comp
L R 2k
U 1 1 5A8B21DB
P 7550 5500
F 0 "2k" V 7630 5500 50  0000 C CNN
F 1 "R3" V 7550 5500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7480 5500 50  0001 C CNN
F 3 "" H 7550 5500 50  0001 C CNN
	1    7550 5500
	-1   0    0    1   
$EndComp
$Comp
L R 3k
U 1 1 5A8B22A6
P 7550 6200
F 0 "3k" V 7630 6200 50  0000 C CNN
F 1 "R4" V 7550 6200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7480 6200 50  0001 C CNN
F 3 "" H 7550 6200 50  0001 C CNN
	1    7550 6200
	-1   0    0    1   
$EndComp
$Comp
L CPC1002N S2
U 1 1 5A8B258B
P 6900 1100
F 0 "S2" H 6900 1500 60  0000 C CNN
F 1 "CPC1002N" H 6850 700 60  0000 C CNN
F 2 "PayloadBoards:CPC1002NTR" H 6950 1100 60  0001 C CNN
F 3 "" H 6950 1100 60  0001 C CNN
	1    6900 1100
	1    0    0    -1  
$EndComp
Text GLabel 7550 900  2    60   Input Italic 0
Stratologger_Switch-
Text GLabel 7550 1300 2    60   Input Italic 0
Stratologger_Switch+
Text GLabel 2600 3300 2    60   Input ~ 0
7.4V
Text GLabel 7450 2000 2    60   Input ~ 0
7.4V
Wire Wire Line
	7450 2400 8200 2400
$Comp
L R R1
U 1 1 5A977229
P 5950 2000
F 0 "R1" V 6030 2000 50  0000 C CNN
F 1 "1.9k" V 5950 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5880 2000 50  0001 C CNN
F 3 "" H 5950 2000 50  0001 C CNN
	1    5950 2000
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5A977E9E
P 6050 900
F 0 "R2" V 6130 900 50  0000 C CNN
F 1 "1.9k" V 6050 900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5980 900 50  0001 C CNN
F 3 "" H 6050 900 50  0001 C CNN
	1    6050 900 
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 900  5900 900 
Wire Wire Line
	5450 2000 5800 2000
Wire Wire Line
	7550 5200 7550 5350
Wire Wire Line
	7550 5650 7550 6050
Wire Wire Line
	7550 5800 8300 5800
Connection ~ 7550 5800
Wire Wire Line
	7550 6350 7550 6500
Text GLabel 6100 4100 0    60   Input ~ 0
7.4V
Wire Wire Line
	8700 4100 8700 4950
Wire Wire Line
	5450 900  5450 5650
Connection ~ 5450 2000
Wire Wire Line
	7750 2400 7750 2050
Wire Wire Line
	7750 2050 8200 2050
Connection ~ 7750 2400
Wire Wire Line
	8000 4650 8000 4650
Wire Wire Line
	8000 4650 8000 4500
Wire Wire Line
	8000 4200 8000 4100
Connection ~ 8000 4100
Text Notes 8150 5750 2    60   ~ 0
3.3V data
Text Notes 8250 4050 2    60   ~ 0
3.3V power
Connection ~ 6550 4100
$Comp
L Conn_01x02 J5
U 1 1 5A9A1806
P 2400 3200
F 0 "J5" H 2400 3300 50  0000 C CNN
F 1 "Conn_01x02" H 2400 3000 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 3200 50  0001 C CNN
F 3 "" H 2400 3200 50  0001 C CNN
	1    2400 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8700 5150 8300 5150
Wire Wire Line
	8300 5150 8300 5800
Wire Wire Line
	7350 5200 7550 5200
$Comp
L GND #PWR01
U 1 1 5A9AC8F8
P 7550 6500
F 0 "#PWR01" H 7550 6250 50  0001 C CNN
F 1 "GND" H 7550 6350 50  0000 C CNN
F 2 "" H 7550 6500 50  0001 C CNN
F 3 "" H 7550 6500 50  0001 C CNN
	1    7550 6500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5A9AC98C
P 6550 4650
F 0 "#PWR02" H 6550 4400 50  0001 C CNN
F 1 "GND" H 6550 4500 50  0000 C CNN
F 2 "" H 6550 4650 50  0001 C CNN
F 3 "" H 6550 4650 50  0001 C CNN
	1    6550 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5A9ACBA8
P 7250 4550
F 0 "#PWR03" H 7250 4300 50  0001 C CNN
F 1 "GND" H 7250 4400 50  0000 C CNN
F 2 "" H 7250 4550 50  0001 C CNN
F 3 "" H 7250 4550 50  0001 C CNN
	1    7250 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5A9AD16E
P 8600 6000
F 0 "#PWR04" H 8600 5750 50  0001 C CNN
F 1 "GND" H 8600 5850 50  0000 C CNN
F 2 "" H 8600 6000 50  0001 C CNN
F 3 "" H 8600 6000 50  0001 C CNN
	1    8600 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 6000 8600 5850
Wire Wire Line
	8600 5850 8700 5850
$Comp
L GND #PWR05
U 1 1 5A9AD339
P 8000 4650
F 0 "#PWR05" H 8000 4400 50  0001 C CNN
F 1 "GND" H 8000 4500 50  0000 C CNN
F 2 "" H 8000 4650 50  0001 C CNN
F 3 "" H 8000 4650 50  0001 C CNN
	1    8000 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5A9AD9D1
P 6000 2500
F 0 "#PWR06" H 6000 2250 50  0001 C CNN
F 1 "GND" H 6000 2350 50  0000 C CNN
F 2 "" H 6000 2500 50  0001 C CNN
F 3 "" H 6000 2500 50  0001 C CNN
	1    6000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2500 6000 2400
Wire Wire Line
	6000 2400 6100 2400
$Comp
L GND #PWR07
U 1 1 5A9ADA92
P 6050 1450
F 0 "#PWR07" H 6050 1200 50  0001 C CNN
F 1 "GND" H 6050 1300 50  0000 C CNN
F 2 "" H 6050 1450 50  0001 C CNN
F 3 "" H 6050 1450 50  0001 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1450 6050 1300
Wire Wire Line
	6050 1300 6200 1300
$Comp
L GND #PWR08
U 1 1 5A9ADD02
P 1850 6450
F 0 "#PWR08" H 1850 6200 50  0001 C CNN
F 1 "GND" H 1850 6300 50  0000 C CNN
F 2 "" H 1850 6450 50  0001 C CNN
F 3 "" H 1850 6450 50  0001 C CNN
	1    1850 6450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5A9ADED2
P 1700 6450
F 0 "#PWR09" H 1700 6200 50  0001 C CNN
F 1 "GND" H 1700 6300 50  0000 C CNN
F 2 "" H 1700 6450 50  0001 C CNN
F 3 "" H 1700 6450 50  0001 C CNN
	1    1700 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 6450 1850 6400
Wire Wire Line
	1850 6400 1900 6400
Wire Wire Line
	1700 6450 1700 6300
Wire Wire Line
	1700 6300 1900 6300
$Comp
L GND #PWR010
U 1 1 5A9AE056
P 2950 3400
F 0 "#PWR010" H 2950 3150 50  0001 C CNN
F 1 "GND" H 2950 3250 50  0000 C CNN
F 2 "" H 2950 3400 50  0001 C CNN
F 3 "" H 2950 3400 50  0001 C CNN
	1    2950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3200 2950 3200
Wire Wire Line
	2950 3200 2950 3400
$Comp
L C C1
U 1 1 5A9AEA7D
P 6550 4350
F 0 "C1" H 6575 4450 50  0000 L CNN
F 1 "10uF" H 6575 4250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6588 4200 50  0001 C CNN
F 3 "" H 6550 4350 50  0001 C CNN
	1    6550 4350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5A9AEB07
P 8000 4350
F 0 "C2" H 8025 4450 50  0000 L CNN
F 1 "10uF" H 8025 4250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8038 4200 50  0001 C CNN
F 3 "" H 8000 4350 50  0001 C CNN
	1    8000 4350
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 5A9AED81
P 2400 2600
F 0 "J4" H 2400 2700 50  0000 C CNN
F 1 "Conn_01x02" H 2400 2400 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 2600 50  0001 C CNN
F 3 "" H 2400 2600 50  0001 C CNN
	1    2400 2600
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02 J3
U 1 1 5A9AEDE1
P 2400 2000
F 0 "J3" H 2400 2100 50  0000 C CNN
F 1 "Conn_01x02" H 2400 1800 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 2000 50  0001 C CNN
F 3 "" H 2400 2000 50  0001 C CNN
	1    2400 2000
	-1   0    0    -1  
$EndComp
Text GLabel 2600 2700 2    60   Input Italic 0
Intrument_Arduino_Power
Text GLabel 2600 2100 2    60   Input Italic 0
Stratologger_Switch+
Text GLabel 2600 2000 2    60   Input Italic 0
Stratologger_Switch-
$Comp
L Conn_01x02 J2
U 1 1 5A9AEF72
P 2400 1250
F 0 "J2" H 2400 1350 50  0000 C CNN
F 1 "Conn_01x02" H 2400 1050 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 1250 50  0001 C CNN
F 3 "" H 2400 1250 50  0001 C CNN
	1    2400 1250
	-1   0    0    -1  
$EndComp
Text GLabel 2600 1350 2    60   Input Italic 0
GoPro_Power
$Comp
L GND #PWR011
U 1 1 5A9AF05A
P 3850 2850
F 0 "#PWR011" H 3850 2600 50  0001 C CNN
F 1 "GND" H 3850 2700 50  0000 C CNN
F 2 "" H 3850 2850 50  0001 C CNN
F 3 "" H 3850 2850 50  0001 C CNN
	1    3850 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5A9AF30B
P 3350 1500
F 0 "#PWR012" H 3350 1250 50  0001 C CNN
F 1 "GND" H 3350 1350 50  0000 C CNN
F 2 "" H 3350 1500 50  0001 C CNN
F 3 "" H 3350 1500 50  0001 C CNN
	1    3350 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1250 3350 1250
Wire Wire Line
	3350 1250 3350 1500
Wire Wire Line
	2600 2600 3850 2600
Wire Wire Line
	3850 2600 3850 2850
$Comp
L Conn_01x02 J1
U 1 1 5A9AFA7A
P 2400 700
F 0 "J1" H 2400 800 50  0000 C CNN
F 1 "Conn_01x02" H 2400 500 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 700 50  0001 C CNN
F 3 "" H 2400 700 50  0001 C CNN
	1    2400 700 
	-1   0    0    -1  
$EndComp
Text GLabel 2600 800  2    60   Input Italic 0
SCL
Text GLabel 2600 700  2    60   Input Italic 0
SDA
$Comp
L R-78E3.3-0.5 U1
U 1 1 5A9B412D
P 7250 4250
F 0 "U1" H 7250 4700 60  0000 C CNN
F 1 "R-78E3.3-0.5" H 7250 3650 60  0000 C CNN
F 2 "sip:SIP3" H 7250 4250 60  0001 C CNN
F 3 "" H 7250 4250 60  0001 C CNN
	1    7250 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4100 6700 4100
Wire Wire Line
	6550 4200 6550 4100
Wire Wire Line
	6550 4500 6550 4650
Wire Wire Line
	8250 4650 8250 4650
Wire Wire Line
	8250 4650 8250 4500
Wire Wire Line
	8250 4100 8250 4200
$Comp
L GND #PWR?
U 1 1 5ABA400A
P 8250 4650
F 0 "#PWR?" H 8250 4400 50  0001 C CNN
F 1 "GND" H 8250 4500 50  0000 C CNN
F 2 "" H 8250 4650 50  0001 C CNN
F 3 "" H 8250 4650 50  0001 C CNN
	1    8250 4650
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5ABA4010
P 8250 4350
F 0 "C?" H 8275 4450 50  0000 L CNN
F 1 "1uF" H 8275 4250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8288 4200 50  0001 C CNN
F 3 "" H 8250 4350 50  0001 C CNN
	1    8250 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4650 8500 4650
Wire Wire Line
	8500 4650 8500 4500
Wire Wire Line
	8500 4100 8500 4200
$Comp
L GND #PWR?
U 1 1 5ABA4092
P 8500 4650
F 0 "#PWR?" H 8500 4400 50  0001 C CNN
F 1 "GND" H 8500 4500 50  0000 C CNN
F 2 "" H 8500 4650 50  0001 C CNN
F 3 "" H 8500 4650 50  0001 C CNN
	1    8500 4650
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5ABA4098
P 8500 4350
F 0 "C?" H 8525 4450 50  0000 L CNN
F 1 "8.2pF" H 8525 4250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8538 4200 50  0001 C CNN
F 3 "" H 8500 4350 50  0001 C CNN
	1    8500 4350
	1    0    0    -1  
$EndComp
Connection ~ 8250 4100
Connection ~ 8500 4100
$Comp
L Conn_01x02 J6
U 1 1 5ABE74E1
P 2400 3800
F 0 "J6" H 2400 3900 50  0000 C CNN
F 1 "Conn_01x02" H 2400 3600 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 2400 3800 50  0001 C CNN
F 3 "" H 2400 3800 50  0001 C CNN
	1    2400 3800
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5ABE78A1
P 3450 3900
F 0 "#PWR?" H 3450 3650 50  0001 C CNN
F 1 "GND" H 3450 3750 50  0000 C CNN
F 2 "" H 3450 3900 50  0001 C CNN
F 3 "" H 3450 3900 50  0001 C CNN
	1    3450 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3800 3450 3800
Wire Wire Line
	3450 3800 3450 3900
$Sheet
S 4050 4100 700  450 
U 5ABE85A9
F0 "Sheet5ABE85A8" 60
F1 "file5ABE85A8.sch" 60
F2 "A" I L 4050 4450 60 
F3 "VccA" I L 4050 4250 60 
F4 "VccB" I R 4750 4250 60 
F5 "B" I R 4750 4450 60 
$EndSheet
Text GLabel 3250 4350 2    60   Input Italic 0
XBEE-DIN
Text GLabel 2600 3900 2    60   Input ~ 0
Stratologger_TX
Text GLabel 4500 5150 2    60   Input ~ 0
Stratologger_TX
Wire Wire Line
	3250 4450 4050 4450
Text GLabel 4050 4250 0    60   Input ~ 0
5V
Text GLabel 4750 4250 2    60   Input ~ 0
3.3V
Text GLabel 8700 4100 2    60   Input ~ 0
3.3V
$Sheet
S 3800 4800 700  450 
U 5ABEAE41
F0 "Sheet5ABE85A8" 60
F1 "file5ABE85A8.sch" 60
F2 "A" I L 3800 5150 60 
F3 "VccA" I L 3800 4950 60 
F4 "VccB" I R 4500 4950 60 
F5 "B" I R 4500 5150 60 
$EndSheet
Wire Wire Line
	3250 4550 3350 4550
Wire Wire Line
	3350 4550 3350 5150
Wire Wire Line
	3350 5150 3800 5150
Text GLabel 3800 4950 0    60   Input ~ 0
5V
Text GLabel 4500 4950 2    60   Input ~ 0
3.3V
$EndSCHEMATC

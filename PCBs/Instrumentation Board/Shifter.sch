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
Sheet 5 10
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
L PI4ULS5V201TAEX U1
U 1 1 5AB871B5
P 5050 3200
AR Path="/5AB87152/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB8887F/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB899BF/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB899C9/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB8BB45/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB8D505/5AB871B5" Ref="U1"  Part="1" 
AR Path="/5AB8DDC4/5AB871B5" Ref="U1"  Part="1" 
F 0 "U1" H 5050 3750 60  0000 C CNN
F 1 "PI4ULS5V201TAEX" H 5050 2750 60  0000 C CNN
F 2 "" H 5050 3200 60  0001 C CNN
F 3 "" H 5050 3200 60  0001 C CNN
	1    5050 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 5AB8720A
P 4500 3300
AR Path="/5AB87152/5AB8720A" Ref="#PWR21"  Part="1" 
AR Path="/5AB8887F/5AB8720A" Ref="#PWR24"  Part="1" 
AR Path="/5AB899BF/5AB8720A" Ref="#PWR27"  Part="1" 
AR Path="/5AB899C9/5AB8720A" Ref="#PWR30"  Part="1" 
AR Path="/5AB8BB45/5AB8720A" Ref="#PWR33"  Part="1" 
AR Path="/5AB8D505/5AB8720A" Ref="#PWR36"  Part="1" 
AR Path="/5AB8DDC4/5AB8720A" Ref="#PWR39"  Part="1" 
F 0 "#PWR39" H 4500 3050 50  0001 C CNN
F 1 "GND" H 4500 3150 50  0000 C CNN
F 2 "" H 4500 3300 50  0001 C CNN
F 3 "" H 4500 3300 50  0001 C CNN
	1    4500 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3300 4500 3150
Wire Wire Line
	4500 3150 4600 3150
$Comp
L GND #PWR20
U 1 1 5AB87222
P 4300 3300
AR Path="/5AB87152/5AB87222" Ref="#PWR20"  Part="1" 
AR Path="/5AB8887F/5AB87222" Ref="#PWR23"  Part="1" 
AR Path="/5AB899BF/5AB87222" Ref="#PWR26"  Part="1" 
AR Path="/5AB899C9/5AB87222" Ref="#PWR29"  Part="1" 
AR Path="/5AB8BB45/5AB87222" Ref="#PWR32"  Part="1" 
AR Path="/5AB8D505/5AB87222" Ref="#PWR35"  Part="1" 
AR Path="/5AB8DDC4/5AB87222" Ref="#PWR38"  Part="1" 
F 0 "#PWR38" H 4300 3050 50  0001 C CNN
F 1 "GND" H 4300 3150 50  0000 C CNN
F 2 "" H 4300 3300 50  0001 C CNN
F 3 "" H 4300 3300 50  0001 C CNN
	1    4300 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR22
U 1 1 5AB87230
P 5900 3550
AR Path="/5AB87152/5AB87230" Ref="#PWR22"  Part="1" 
AR Path="/5AB8887F/5AB87230" Ref="#PWR25"  Part="1" 
AR Path="/5AB899BF/5AB87230" Ref="#PWR28"  Part="1" 
AR Path="/5AB899C9/5AB87230" Ref="#PWR31"  Part="1" 
AR Path="/5AB8BB45/5AB87230" Ref="#PWR34"  Part="1" 
AR Path="/5AB8D505/5AB87230" Ref="#PWR37"  Part="1" 
AR Path="/5AB8DDC4/5AB87230" Ref="#PWR40"  Part="1" 
F 0 "#PWR40" H 5900 3300 50  0001 C CNN
F 1 "GND" H 5900 3400 50  0000 C CNN
F 2 "" H 5900 3550 50  0001 C CNN
F 3 "" H 5900 3550 50  0001 C CNN
	1    5900 3550
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5AB8723F
P 5900 3400
AR Path="/5AB87152/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB8887F/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB899BF/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB899C9/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB8BB45/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB8D505/5AB8723F" Ref="C2"  Part="1" 
AR Path="/5AB8DDC4/5AB8723F" Ref="C2"  Part="1" 
F 0 "C2" H 5925 3500 50  0000 L CNN
F 1 ".1uF" H 5925 3300 50  0000 L CNN
F 2 "" H 5938 3250 50  0001 C CNN
F 3 "" H 5900 3400 50  0001 C CNN
	1    5900 3400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5AB872AC
P 4300 3150
AR Path="/5AB87152/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB8887F/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB899BF/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB899C9/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB8BB45/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB8D505/5AB872AC" Ref="C1"  Part="1" 
AR Path="/5AB8DDC4/5AB872AC" Ref="C1"  Part="1" 
F 0 "C1" H 4325 3250 50  0000 L CNN
F 1 ".1uF" H 4325 3050 50  0000 L CNN
F 2 "" H 4338 3000 50  0001 C CNN
F 3 "" H 4300 3150 50  0001 C CNN
	1    4300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3000 4300 2850
Wire Wire Line
	4200 2850 4600 2850
Wire Wire Line
	5500 2850 6000 2850
Wire Wire Line
	5900 2850 5900 3250
NoConn ~ 5500 2950
NoConn ~ 4600 3050
Wire Wire Line
	5500 3150 5900 3150
Connection ~ 5900 3150
Text HLabel 5500 3050 2    60   Input ~ 0
B
Text HLabel 6000 2850 2    60   Input ~ 0
VccB
Connection ~ 5900 2850
Text HLabel 4600 2950 0    60   Input ~ 0
A
Text HLabel 4200 2850 0    60   Input ~ 0
VccA
Connection ~ 4300 2850
$EndSCHEMATC

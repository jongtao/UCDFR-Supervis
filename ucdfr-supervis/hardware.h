#ifndef	HARDWARE_H 
#define HARDWARE_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "state_event.h"

#define F_CPU 16000000UL // 16 MHz
#define CTC_COUNT (((F_CPU/1000)/8) - 1) // 1 millisecond CTC

#define BRAKE_FIFTEEN_PERCENT 150
#define PEDAL2_MIN_MARGIN 30
#define PEDAL2_MAX_MARGIN 1000

// Linear relationship to express pedal2 in terms of pedal1 measurements
#define PEDAL_INTERCEPT 8
#define PEDAL_SLOPE 8

#define PEDAL1_TEN_PERCENT 100
#define PEDAL1_TWENTYFIVE_PERCENT 250

#define BRAKE_MIN_MARGIN 100

#define THRTTL_SLOPE 8
#define THRTTL_INTERCEPT 8


/* Port A
A1	In	HV request
A2	In	Drive request
A3	In	Neutral request
*/

/* Port B
B1	Out	PEE Power
B2	Out	ACUES Power
B3	Out	Drive Enable
B4	Out	Keyswitch Enable
B5	Out	AIR 1
B6	Out	AIR 2
B7	Out	Charger Enable
*/

/* Port C
C0	In	Left Estop
C1	In	Brake Overtravel
C2	In	Interlock Loop
C3	In	Inertia Switch
C4	Out	Red LED
C5	Out	Green LED
C6	Out	Blue LED
*/

/* Port D
D0	Out RTD Buzzer
D1	Out	Dash/TQV
D2	Out	Reserved 1 (DISABLED)
D3	Out Reserved 2 (DISABLED)
D4	In	Charger Detect
D5	In	Inv. 1 Contact Request
D6	In	Inv. 2 Contact Request
D7	In	Master Switch
*/

/* Port E
E0	In	Cockpit Estop
E1	In	Right Estop
E6	In	Powerstage IMD Error
E7	In	Powerstage BPS Error
*/

/* Port F
F0	In	GLV Sys Voltage
F1	In	DC Link Voltage
F2	In	Brake Sensor
F3	In	Traction Sys Current
F4	In	Throttle to Ctrlr 1
F5	In	Throttle to Ctrlr 2
F6	In	Throttle Sensor 1
F7	In	Throttle Sensor 2
*/



void hard_init();
uint32_t analog_vcc();
uint32_t analog_read(uint32_t *vcc, uint8_t f_pin);
void get_inputs(uint16_t *events);

void action_startup();
void action_neutral();
void action_charging();
void action_drive();
void action_soft_fault();
void action_hard_fault();

void reset_drive_sound();

#endif

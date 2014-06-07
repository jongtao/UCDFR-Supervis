#ifndef	HARDWARE_H 
#define HARDWARE_H

#include <stdint.h>
#include <avr/io.h>

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
F1	In	DC Link Boltage
F2	In	Brake Sensor
F3	In	Traction Sys Current
F4	In	Throttle to Ctrlr 1
F5	In	Throttle to Ctrlr 2
F6	In	Throttle Sensor 1
F7	In	Throttle Sensor 2
*/


void hard_init();
unsigned int analog_read(uint8_t f_pin);
void get_inputs(uint16_t *events);
void put_outputs();

#endif

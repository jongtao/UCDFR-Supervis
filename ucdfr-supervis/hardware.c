#include "hardware.h"



void hard_init()
{
	CLKPR = 0x80, CLKPR = 0; // zero prescaler

	DDRA = (0x00);	// A1-A3 In
	DDRB = (0xFE);	// B1-B7 Out
	DDRC = (0x30);	// C0-C3 In, C4-C6 Out
	DDRD = (0x0F);	// D0-D3 Out, D4-D7 In
	DDRE = (0x00);	// E0-E7 In
	DDRF = (0x00);	// F0-F7 In

	PORTF = (0xFF);	// Enable Pullup on F0-F7

	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Prepare ADC
	ADCSRB = 0x80;	// "High Speed"
} // inputs_init()



unsigned int analog_read(uint8_t f_pin)
{
	ADMUX = (1<<REFS0) | f_pin;	// MUX to f_pin. Compare voltage with AVCC
	ADCSRA |= (1<<ADSC); 				// begin conversion
	while(ADCSRA & (1<<ADSC)); 	// wait for the conversion to happen
	return ADCW;								// Read it. 10 bit precision
} // analog_read()



void get_inputs(uint16_t *events)
{
/*	
	PINA&(1<<1); 
	PINA&(1<<2); 
	PINA&(1<<3);

	PINC&(1<<0);
	PINC&(1<<1);
	PINC&(1<<2);
	PINC&(1<<3);
*/
} // get_inputs()

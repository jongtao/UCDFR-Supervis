#include <stdint.h>
#include "hardware.h"



enum States
{
	ZERO,
	STARTUP,
	NEUTRAL,
	DRIVE,
	CHARGING,
	SOFT_FAULT,
	HARD_FAULT
}; // enum States



enum Events
{
	NO_EVENT,
	GLV_UP,
	HV_UP,
	DRIVE_UP,
	NEUTRAL_UP,
	CHARGE_UP,
	CHARGE_DOWN,
	ANALOG_FAULT,
	SHUTDOWN_FAULT,
	DATA_FAULT,
	FAULT_REMEDIED
}; // enum Events



void fatal_fault()
{
	for(;;);
} // fatal_fault()



int main()
{
	uint8_t state = ZERO;
	uint16_t event = 0x00 | (1 << NO_EVENT);

	hard_init();

	for(;;)
	{
		event = 0x00 | (1 << NO_EVENT);
		get_inputs(&event);

		// FSM
		switch(state)
		{
			case ZERO:
				if(event == GLV_UP) state = STARTUP;
				break;
			case STARTUP:
				if(event == HV_UP) state = NEUTRAL;
				break;
			case NEUTRAL:
				if(event == DRIVE_UP) state = DRIVE;
				if(event == CHARGE_UP) state = CHARGING;
				break;
			case DRIVE:
				if(event == NEUTRAL || event == CHARGE_UP) state = NEUTRAL;
				if(event == ANALOG_FAULT) state = SOFT_FAULT;
				if(event == SHUTDOWN_FAULT || event == DATA_FAULT) state = HARD_FAULT;
				break;
			case CHARGING:
				if(event == CHARGE_DOWN) state = NEUTRAL;
				break;
			case SOFT_FAULT:
				if(event == FAULT_REMEDIED) state = DRIVE;
				break;
			case HARD_FAULT:
				fatal_fault();
				break;
			default: // INVALID STATE
				fatal_fault();
				break;
		}; // switch state
	} // main loop

	return 0;
} // main()

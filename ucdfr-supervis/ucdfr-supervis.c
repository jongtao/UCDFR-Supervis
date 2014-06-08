#include <stdint.h>
#include "hardware.h"
#include "interface.h"



enum States
{
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
	HV_UP,
	DRIVE_UP,
	NEUTRAL_UP,
	CHARGE_UP,
	CHARGE_DOWN,
	SOFT_FAULT_SIG,
	SOFT_FAULT_REMEDIED,
	HARD_FAULT_SIG
}; // enum Events



void fatal_fault()
{
	for(;;);
} // fatal_fault()



int main()
{
	uint8_t state = STARTUP;
	uint16_t event = 0x00 | (1 << NO_EVENT);
	//interface_init();	// USB interface
	hard_init();	// initialize hardware

	for(;;)
	{
		event = 0x00 | (1 << NO_EVENT);
		get_inputs(&event);
		usb_terminal(&event, &state);

		// FSM
		switch(state)
		{
			case STARTUP:
				if(event == HV_UP) state = NEUTRAL;
				break;
			case NEUTRAL:
				if(event == DRIVE_UP) state = DRIVE;
				if(event == CHARGE_UP) state = CHARGING;
				break;
			case DRIVE:
				if(event == NEUTRAL || event == CHARGE_UP) state = NEUTRAL;
				if(event == SOFT_FAULT_SIG) state = SOFT_FAULT;
				break;
			case CHARGING:
				if(event == CHARGE_DOWN) state = NEUTRAL;
				break;
			case SOFT_FAULT:
				if(event == SOFT_FAULT_REMEDIED) state = DRIVE;
				break;
			case HARD_FAULT:
				fatal_fault();
				break;
			default: // INVALID STATE
				fatal_fault();
				break;
		}; // switch state

		if(event == HARD_FAULT_SIG) state = HARD_FAULT;
	} // main loop

	return 0;
} // main()

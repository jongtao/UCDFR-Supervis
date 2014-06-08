#include <stdint.h>
#include "hardware.h"
#include "interface.h"
#include "state_event.h"


/*
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
	HV_UP,
	DRIVE_UP,
	NEUTRAL_UP,
	CHARGE_UP,
	CHARGE_DOWN,
	SOFT_FAULT_SIG,
	SOFT_FAULT_REMEDIED,
	HARD_FAULT_SIG
}; // enum Events
*/


void fatal_fault()
{
	for(;;);
} // fatal_fault()



int main()
{
	uint8_t state = STARTUP;
	uint16_t event = 0x00;
	//interface_init();	// USB interface
	hard_init();	// initialize hardware

	for(;;)
	{
		event = 0x00; // wipe events
		get_inputs(&event);
		usb_terminal(&event, &state);

		// FSM
		switch(state)
		{
			case STARTUP:
				action_startup();
				if(event&(1<<HV_UP)) state = NEUTRAL;
				break;
			case NEUTRAL:
				action_neutral();
				if(event&(1<<DRIVE_UP)) state = DRIVE;
				if(event&(1<<CHARGE_UP)) state = CHARGING;
				break;
			case DRIVE:
				action_drive();
				if(event&(1<<NEUTRAL) || event&(1<<CHARGE_UP)) state = NEUTRAL;
				if(event&(1<<SOFT_FAULT_SIG)) state = SOFT_FAULT;
				if(state != DRIVE) reset_drive_sound(); 
				break;
			case CHARGING:
				action_drive();
				if(event&(1<<CHARGE_DOWN)) state = NEUTRAL;
				break;
			case SOFT_FAULT:
				action_soft_fault();
				if(event&(1<<SOFT_FAULT_REMEDIED)) state = DRIVE;
				break;
			case HARD_FAULT:
				action_hard_fault();
				for(;;);	// trap fault
				break;
			default: // INVALID STATE
				fatal_fault();
				break;
		}; // switch state

		if(event == HARD_FAULT_SIG) state = HARD_FAULT;
	} // main loop

	fatal_fault();
	return 0;
} // main()

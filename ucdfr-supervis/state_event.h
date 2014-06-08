#ifndef STATE_EVENT_H
#define STATE_EVENT_H



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



#endif

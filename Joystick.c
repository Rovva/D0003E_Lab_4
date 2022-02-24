#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "TinyTimber.h"
#include "Joystick.h"
#include "GUI.h"

void joystickInterrupt(Joystick *self) {
	ASYNC(self->gui, update_values, 0);
	if(((PINB >> 6) & 1) == 0) {
		SYNC(self->gui, repeatIncrease, self->gui->whichPulse );
	} else if(((PINB >> 7) & 1) == 0) {
		SYNC(self->gui, repeatDecrease, self->gui->whichPulse );
	}

	if(((PINB >> 4) & 1) == 0) {
		if(self->gui->whichPulse == 0) {
			ASYNC(self->gui->generator1, updatePulseValue, 0);
		} else {
			ASYNC(self->gui->generator2, updatePulseValue, 0);
		}
	}
	if(((PINE >> 2) & 1) == 0) {
		self->gui->whichPulse = 0;
	} else if(((PINE >> 3) & 1) == 0) {
		self->gui->whichPulse = 1;
	}
}

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "TinyTimber.h"
#include "Joystick.h"
#include "GUI.h"

void joystickInterrupt(Joystick *self) {
	// Update the display
	ASYNC(self->gui, update_values, 0);
	
	//  If Up or Down is pressed
	if(((PINB >> 6) & 1) == 0) {
		SYNC(self->gui, setButtonPressed, 1);
		ASYNC(self->gui, setFirstPress, false);
		ASYNC(self->gui, repeatIncrease, self->gui->whichPulse );
	} else if(((PINB >> 7) & 1) == 0) {
		SYNC(self->gui, setButtonPressed, 2);
		ASYNC(self->gui, setFirstPress, false);
		ASYNC(self->gui, repeatDecrease, self->gui->whichPulse );
	} else {
		SYNC(self->gui, setButtonPressed, 0);
		ASYNC(self->gui, setFirstPress, true);
	}
	// If Center is pressed, save frequency and reset
	if(((PINB >> 4) & 1) == 0) {
		if(self->gui->whichPulse == 0) {
			ASYNC(self->gui->generator1, updatePulseValue, 0);
		} else {
			ASYNC(self->gui->generator2, updatePulseValue, 0);
		}
	}

	// If Left or Right is pressed then change active pulse generator input
	if(((PINE >> 2) & 1) == 0) {
		self->gui->whichPulse = 0;
	} else if(((PINE >> 3) & 1) == 0) {
		self->gui->whichPulse = 1;
	}
}

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "Generator.h"
#include "Writer.h"

// Write code to handle a 0 in value AND READ UP ABOUT PWM

// Method that saves a value and resets frequency to 0
void updatePulseValue(Generator *self) {
	// If the generator has not been updated
	if(self->updated == 0) {
		// Save current frequency in temp
		uint8_t temp = self->CurrentHzValue;
		// Save the value in temp to the variable OldHzValue
		self->OldHzValue = temp;
		// Set the current frequency to 0
		self->CurrentHzValue = 0;

		self->updated = true;
	// Otherwise restore the old frequency as the active one
	} else {
		self->CurrentHzValue = self->OldHzValue;
		self->OldHzValue = 0;
		self->updated = false;
		updateWriter(self);
	}

}
// Increase the frequency by 1
void increaseFrequency(Generator *self) {

	uint8_t temp;
	temp = self->CurrentHzValue;
	if(temp < 99) {
		if(self->CurrentHzValue == 0) {
			temp++;
			self->CurrentHzValue = temp;
			updateWriter(self);
		} else {
			temp++;
			self->CurrentHzValue = temp;
		}
	}
}
// Decrease the frequency by 1
void decreaseFrequency(Generator *self) {
	uint8_t temp = self->CurrentHzValue;
	if(temp > 0) {
		temp--;
		self->CurrentHzValue = temp;
	}
}

// Method to constantly update the object "Write" to write to the port E
void updateWriter(Generator *self) {
	if(self->CurrentHzValue > 0) {
		SYNC(self->writer, writeToPort, self->GeneratorNr);
		AFTER((MSEC(1000)/(self->CurrentHzValue)/2), self, updateWriter, 0);
	} else {
		SYNC(self->writer, disableOutput, self->GeneratorNr);
	}
}

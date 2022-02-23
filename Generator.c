#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "Generator.h"
#include "Writer.h"

// Write code to handle a 0 in value AND READ UP ABOUT PWM
void updatePulseValue(Generator *self) {
	if(self->updated == 0) {
		uint8_t temp = self->CurrentHzValue;
		self->OldHzValue = temp;
		self->CurrentHzValue = 0;
		self->updated = 1;
	} else {
		self->CurrentHzValue = self->OldHzValue;
		self->OldHzValue = 0;
		self->updated = 0;
		updateWriter(self);
	}

}

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
		//updateWriter(self);
	}
}

void decreaseFrequency(Generator *self) {
	uint8_t temp = self->CurrentHzValue;
	if(temp > 0) {
		temp--;
		self->CurrentHzValue = temp;
		//updateWriter(self);
	}
}

void updateWriter(Generator *self) {
	if(self->CurrentHzValue > 0) {
		SYNC(self->writer, writeToPort, self->GeneratorNr);
		AFTER((MSEC(1000)/(self->CurrentHzValue)/2), self, updateWriter, 0);
	} // Write code to turn off the generator
}

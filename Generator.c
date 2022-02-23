#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "Generator.h"
#include "Writer.h"

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
	}

}

void increaseFrequency(Generator *self) {
	if(self->CurrentHzValue == 0) {
		updateWriter(self);
	}
	uint8_t temp;
	temp = self->CurrentHzValue;
	if(temp < 99) {
		temp++;
		self->CurrentHzValue = temp;
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
	SYNC(self->writer, writeToPort, self->GeneratorNr);
	AFTER(MSEC(2000)/(self->CurrentHzValue), self, updateWriter, 0);
}

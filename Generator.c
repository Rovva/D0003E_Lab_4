/*
 * Generator.c
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "Generator.h"

void updatePulseValue(Generator *self, uint8_t newValue) {
	uint8_t temp = self->CurrentHzValue;
	self->OldHzValue = temp;
	self->CurrentHzValue = newValue;
}

uint8_t getGeneratorNumber(Generator *self) {
	uint8_t temp = self->GeneratorNr;
	return temp;
}

uint8_t getCurrentPulseValue(Generator *self) {
	uint8_t temp = self->CurrentHzValue;
	return temp;
}

uint8_t getOldPulseValue(Generator *self) {
	uint8_t temp = self->OldHzValue;
	return temp;
}

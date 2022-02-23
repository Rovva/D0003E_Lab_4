/*
 * Generator.h
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "TinyTimber.h"

typedef struct {
	Object super;
	uint8_t CurrentHzValue;
	uint8_t OldHzValue;
	uint8_t GeneratorNr;
} Generator;

void updatePulseValue(Generator *self, uint8_t newValue);
uint8_t getGeneratorNumber(Generator *self);
uint8_t getCurrentPulseValue(Generator *self);
uint8_t getOldPulseValue(Generator *self);

#define init_Generator(hz, nr){ initObject(), hz, hz, nr };

#endif /* GENERATOR_H_ */

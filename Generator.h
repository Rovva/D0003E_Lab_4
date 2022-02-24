/*
 * Generator.h
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "TinyTimber.h"
#include "Writer.h"

typedef struct {
	Object super;
	Writer *writer;
	uint8_t CurrentHzValue;
	uint8_t OldHzValue;
	uint8_t GeneratorNr;
	uint8_t updated;
} Generator;

void updatePulseValue(Generator *self);

void increaseFrequency(Generator *self);
void decreaseFrequency(Generator *self);

void updateWriter(Generator *self);

#define initGenerator(writer, hz, nr){ initObject(), writer, hz, hz, nr, 0 }

#endif /* GENERATOR_H_ */

/*
 * Generator.h
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

typedef struct {
	Object super;
	uint8_t CurrentHzValue;
	uint8_t OldHzValue;
	uint8_t GeneratorNr;
} Generator;

#endif /* GENERATOR_H_ */

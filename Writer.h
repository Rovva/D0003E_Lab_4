/*
 * Writer.h
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */

#ifndef WRITER_H_
#define WRITER_H_

#include "TinyTimber.h"

typedef struct {
	Object super;

} Writer;

void writeToPort(Writer *self, uint8_t whichPulse);
void disableOutput(Writer *self, uint8_t whichPulse);

#define initWriter(){ initObject() }

#endif /* WRITER_H_ */

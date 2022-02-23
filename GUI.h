/*
 * GUI.h
 *
 *  Created on: Feb 21, 2022
 *      Author: rovva
 */

#ifndef GUI_H_
#define GUI_H_
#include <stdbool.h>
#include <stdint.h>
#include "Generator.h"

typedef struct {
	Object super;
	uint8_t pulseValue1;
	uint8_t pulseValue2;
	uint8_t whichPulse;
	Generator *generator1;
	Generator *generator2;
	uint8_t previousButton;
	uint8_t firstpress;
	bool firstRun;
} GUI;

uint16_t digitLookUp(GUI *self, uint8_t c);
void writeChar(GUI *self, char ch, int pos);
void printAt(GUI *self, long num, int pos);

void update_values(GUI *self);
void changeGenerator(GUI *self);
void modifyValues(GUI *self);

void repeatIncrease(GUI *self, int pulseGenerator);
void increaseValue(GUI *self, int pulseGenerator);

void decreaseValue(GUI *self, int pulseGenerator);
void repeatDecrease(GUI *self, int pulseGenerator);

#define init_GUI(gen1, gen2){ initObject(), 1, 0, 0, gen1, gen2, 0, 0, true }

#endif /* GUI_H_ */

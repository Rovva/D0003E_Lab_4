/*
 * GUI.h
 *
 *  Created on: Feb 21, 2022
 *      Author: rovva
 */

#ifndef GUI_H_
#define GUI_H_



typedef struct {
	Object super;
	uint8_t pulseValue1;
	uint8_t pulseValue2;
	uint8_t whichPulse;
} GUI;

uint16_t digitLookUp(GUI *self, uint8_t c);
void writeChar(GUI *self, char ch, int pos);
void printAt(GUI *self, long num, int pos);

void update_values(GUI *self);
void modifyValues(GUI *self);

void repeatIncrease(GUI *self, int pulseGenerator);
void increaseValue(GUI *self, int pulseGenerator);

void decreaseValue(GUI *self, int pulseGenerator);
void repeatDecrease(GUI *self, int pulseGenerator);

#define init_GUI(){ initObject(), 1, 0, 0 }

#endif /* GUI_H_ */

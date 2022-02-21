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
	int pulseValue1;
	int pulseValue2;
	int whichPulse;
} GUI;
uint16_t digitLookUp(GUI *self, uint8_t c);
void writeChar(GUI *self, char ch, int pos);
void printAt(GUI *self, long num, int pos);
void update_values(GUI *self);
void increasePulse1Value(GUI *self);
//void decreasePulse1Value(GUI *self);

#define init_GUI(){ initObject(), 1, 0, 0 }

#endif /* GUI_H_ */

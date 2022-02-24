/*
 * Writer.c
 *
 *  Created on: Feb 23, 2022
 *      Author: rovva
 */
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "Writer.h"

void writeToPort(Writer *self, uint8_t whichPulse) {
	if(whichPulse == 0) {
		LCDDR3 = LCDDR3 ^ 0b00000001;
	} else {
		LCDDR1 = LCDDR1 ^ 0b00000010;
	}
}
// Disable the output for the specified generator
void disableOutput(Writer *self, uint8_t whichPulse) {
	uint8_t temp = 0;
	uint8_t mask = 0;
	if(whichPulse == 0) {
		mask = 0b11111110;
		temp = LCDDR3 & mask;
		LCDDR3 = temp;
	} else {
		mask = 0b11111101;
		temp = LCDDR1 & mask;
		LCDDR1 = temp;
	}
}

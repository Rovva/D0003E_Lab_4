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

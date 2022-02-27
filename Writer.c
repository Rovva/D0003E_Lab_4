#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "Writer.h"
/*
// CODE FOR TESTING AT HOME WITH A LCD SYMBOL
void writeToPort(Writer *self, uint8_t whichPulse) {
	if(whichPulse == 0) {
		LCDDR3 = LCDDR3 ^ 0b00000001;
	} else {
		LCDDR1 = LCDDR1 ^ 0b00000010;
	}
}
// CODEF OR TESTING AT HOME WITH A LCD SYMBOL
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
*/

// Write to PORT E pin 6 or 4
void writeToPort(Writer *self, uint8_t whichPulse) {
	if(whichPulse == 0) {
		//PORTE = ^(1<<6);
		PORTE = PORTE ^ 0b01000000;
	} else {
		//PORTE = ^(1<<4);
		PORTE = PORTE ^ 0b00010000;
	}
}

// Disable the output for either pin 6 or 4
void disableOutput(Writer *self, uint8_t whichPulse) {
	if(whichPulse == 0) {
		PORTE = PORTE & 0b10111111;
	} else {
		PORTE = PORTE & 0b11101111;
	}
}

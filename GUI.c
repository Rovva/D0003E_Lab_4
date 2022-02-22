#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "TinyTimber.h"

#include "GUI.h"
#include "init_buttons.h"

uint16_t digitLookUp(GUI *self, uint8_t c) {

	if(c < 48 || c > 57) {
		return 0;
	}

	uint16_t binary[10];

	binary[0] = 0b0001010101010001; // 0
	binary[1] = 0b0000000100010000; // 1
	binary[2] = 0b0001000111100001; // 2
	binary[3] = 0b0001000110110001; // 3
	binary[4] = 0b0000010110110000; // 4
	binary[5] = 0b0001010010110001; // 5
	binary[6] = 0b0001010011110001; // 6
	binary[7] = 0b0001000100010000; // 7
	binary[8] = 0b0001010111110001; // 8
	binary[9] = 0b0001010110110000; // 9
	binary[10] = '\0';

	return binary[(c - 48)];
}

void writeChar(GUI *self, char ch, int pos) {
	// If pos is less than zero or greater than 5, do nothing
	if(pos < 0 || pos > 5) {
		return;
	}

	uint16_t digitBinary = 0;
	uint8_t nibble_0 = 0, nibble_1 = 0, nibble_2 = 0, nibble_3 = 0, oldValue = 0, mask = 0, increment = 0;

	// Fetch the value needed to display number "ch" in LCDDRx
	digitBinary = digitLookUp(self, ch);

	// Bitshift 1 bit to get valid values for incrementing the pointer
	increment = pos >> 1;

	// Depending on if the value of pos is even or odd we adjust the nibbles
	// and mask correctly
	if((pos % 2) == 0) {
		nibble_0 = 0b00001111 & (digitBinary >> 12);
		nibble_1 = 0b00001111 & (digitBinary >> 8);
		nibble_2 = 0b00001111 & (digitBinary >> 4);
		nibble_3 = 0b00001111 & digitBinary;
		// This mask is needed to preserve what is on the right side of
		// LCDDRx
		mask = 0b11110000;
		} else {
		nibble_0 = 0b11110000 & (digitBinary >> 8);
		nibble_1 = 0b11110000 & (digitBinary >> 4);
		nibble_2 = 0b11110000 & digitBinary;
		nibble_3 = 0b11110000 & (digitBinary << 4);
		// Mask needed to preserve what is on the left side of LCDDRx
		mask = 0b00001111;
	}

	// Create a pointer and assign the memory address of LCDDR0
	// (is volatile really needed?)
	volatile uint8_t *LCDDRAddress = &LCDDR0;
	// Increment the pointers memory address with the value calculated earlier
	// This is needed to be able to use LCDDR0+x, LCDDR1+x, LCDDR2+x etc.
	LCDDRAddress = (LCDDRAddress + increment);
	// Preserve the old value by using a mask
	oldValue = mask & *LCDDRAddress;
	// Add the nibble using OR
	*LCDDRAddress = oldValue | nibble_0;
	// Increase the memory address of the pointer with 5 to be able to
	// use LCDDRx+5
	LCDDRAddress = LCDDRAddress + 5;

	oldValue = mask & *LCDDRAddress;
	*LCDDRAddress = oldValue | nibble_1;
	// Increase with 5 to be able to use LCDDRx+10
	LCDDRAddress = LCDDRAddress + 5;

	oldValue = mask & *LCDDRAddress;
	*LCDDRAddress = oldValue | nibble_2;
	// Increase with 5 to be able to use LCDDRx+15
	LCDDRAddress = LCDDRAddress + 5;

	oldValue = mask & *LCDDRAddress;
	*LCDDRAddress = oldValue | nibble_3;

}

void printAt(GUI *self, long num, int pos) {
    int pp = pos;
    writeChar(self, (num % 100) / 10 + '0', pp);
    pp++;
    writeChar(self, num % 10 + '0', pp);
}

void update_values(GUI *self) {
	printAt(self, self->pulseValue1, 4);
	printAt(self, self->pulseValue2, 0);
}

void modifyValues(GUI *self) {
	ASYNC(self, update_values, 0);
	if(((PINE >> 3) & 1) == 0) {
		self->whichPulse = 0;
	} else if(((PINE >> 2) & 1) == 0) {
		self->whichPulse = 1;
	}

	if(((PINB >> 6) & 1) == 0) {
		AFTER(MSEC(100), self, repeatIncrease, self->whichPulse );
	} else if(((PINB >> 7) & 1) == 0) {
		AFTER(MSEC(100), self, repeatDecrease, self->whichPulse );
	}
}

void repeatIncrease(GUI *self, int pulseGenerator) {
	if(((PINB >> 6) & 1) == 0) {
		ASYNC(self, increaseValue, pulseGenerator);
		ASYNC(self, update_values, 0);
		AFTER(1000, self, repeatIncrease, pulseGenerator);
	}
}

void increaseValue(GUI *self, int pulseGenerator) {
	int temp;

	if(pulseGenerator == 0) {
		temp = self->pulseValue1;
		if(temp < 99) {
			temp++;
		}
		self->pulseValue1 = temp;
	} else if(pulseGenerator == 1) {
		temp = self->pulseValue2;
		if(temp < 99) {
			temp++;
		}
		self->pulseValue2 = temp;
	}
}

void repeatDecrease(GUI *self, int pulseGenerator) {
	if(((PINB >> 7) & 1) == 0) {
		ASYNC(self, decreaseValue, pulseGenerator);
		ASYNC(self, update_values, 0);
		AFTER(1000, self, repeatDecrease, pulseGenerator);
	}
}

void decreaseValue(GUI *self, int pulseGenerator) {
	int temp;

	if(pulseGenerator == 0) {
		temp = self->pulseValue1;
		if(temp > 0) {
			temp--;
		}
		self->pulseValue1 = temp;
	} else if(pulseGenerator == 1) {
		temp = self->pulseValue2;
		if(temp > 0) {
			temp--;
		}
		self->pulseValue2 = temp;
	}
}

#include <avr/io.h>
#include <avr/interrupt.h>
#include "init_io.h"

void init_io() {
	// Up, Down and Center
	PORTB = (1<<PB7) | (1<<PB6) | (1<<PB4);
	// Left and Right
	PORTE = (1<<PE3) | (1<<PE2);
	
	// Set PIN 6 and 4 on PORT E as output
	DDRE = (1<<DDE6) | (1<<DDE4);

	// Pin Change Enable Mask (Up, Down and Center on joystick)
	PCMSK1 = (1<<PCINT15) | (1 << PCINT14) | (1<<PCINT12);
	// Pin change Enable Mask (Left and Right on joystick)
	PCMSK0 = (1<<PCINT3) | (1<<PCINT2);

	// External Interrupt Mask Register (EIMSK)
	EIMSK = (1<<PCIE1) | (1<<PCIE0);
}

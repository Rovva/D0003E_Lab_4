#include <avr/io.h>
#include <avr/interrupt.h>
#include "init_buttons.h"

void init_buttons() {
	// Up, Down and Center
	PORTB = (1<<PB7) | (1<<PB6) | (1<<PB4);
	// Left and Right
	PORTE = (1<<PE3) | (1<<PE2);
	// Pin Change Enable Mask (Up, Down and Center on joystick)
	PCMSK1 = (1<<PCINT15) | (1 << PCINT14) | (1<<PCINT12);
	// Pin change Enable Mask (Left and Right on joystick)
	PCMSK0 = (1<<PCINT3) | (1<<PCINT2);

	// External Interrupt Mask Register (EIMSK)
	EIMSK = (1<<PCIE1) | (1<<PCIE0);
}

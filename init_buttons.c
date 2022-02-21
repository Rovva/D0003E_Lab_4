#include <avr/io.h>
#include <avr/interrupt.h>
#include "init_buttons.h"

void init_buttons() {
	PORTB = (1<<PB7);
	// Pin Change Enable Mask (PCINT15)
	PCMSK1 = (1<<PCINT15);
	// External Interrupt Mask Register (EIMSK)
	EIMSK = (1<<PCIE1);
}

#include <avr/io.h>

#include "TinyTimber.h"

#include "GUI.h"
#include "init_lcd.h"
#include "init_buttons.h"

GUI gui = init_GUI();

int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
	init_lcd();
	init_buttons();

	INSTALL(&gui, increasePulse1Value, IRQ_PCINT1);
	return TINYTIMBER(&gui, update_values, 0);
}

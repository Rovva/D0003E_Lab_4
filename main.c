#include <avr/io.h>

#include "TinyTimber.h"

#include "GUI.h"
#include "init_lcd.h"
#include "init_buttons.h"

GUI gui = init_GUI();

int main(void)
{
	init_lcd();
	init_buttons();

	INSTALL(&gui, modifyValues, IRQ_PCINT1);
	INSTALL(&gui, modifyValues, IRQ_PCINT0);
	return TINYTIMBER(&gui, update_values, 0);
}

#include <avr/io.h>

#include "TinyTimber.h"

#include "init_lcd.h"
#include "init_buttons.h"

#include "GUI.h"
#include "Generator.h"

Generator gen1 = init_Generator(1, 0);
Generator gen2 = init_Generator(0, 1);
GUI gui = init_GUI(&gen1, &gen2);

int main(void)
{
	init_lcd();
	init_buttons();

	INSTALL(&gui, modifyValues, IRQ_PCINT1);
	INSTALL(&gui, modifyValues, IRQ_PCINT0);
	return TINYTIMBER(&gui, update_values, 0);
}

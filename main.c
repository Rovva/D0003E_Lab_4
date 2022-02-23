#include <avr/io.h>

#include "TinyTimber.h"

#include "init_lcd.h"
#include "init_buttons.h"

#include "GUI.h"
#include "Generator.h"
#include "Writer.h"

Writer writer = init_Writer();
Generator gen1 = init_Generator(&writer, 0, 0);
Generator gen2 = init_Generator(&writer, 0, 1);
GUI gui = init_GUI(&gen1, &gen2);

int main(void)
{
	init_lcd();
	init_buttons();

	INSTALL(&gui, changeGenerator, IRQ_PCINT0);
	INSTALL(&gui, modifyValues, IRQ_PCINT1);
	return TINYTIMBER(&gui, update_values, 0);
}

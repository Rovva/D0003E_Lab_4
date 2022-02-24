#include <avr/io.h>

#include "TinyTimber.h"

#include "init_lcd.h"
#include "init_buttons.h"

#include "GUI.h"
#include "Generator.h"
#include "Writer.h"
#include "Joystick.h"
// Create all the objects needed
Writer writer = initWriter();
Generator gen1 = initGenerator(&writer, 0, 0);
Generator gen2 = initGenerator(&writer, 0, 1);
GUI gui = initGUI(&gen1, &gen2);
Joystick joy = initJoystick(&gui);

int main(void)
{
	// Setup the clockspeed
	CLKPR  = 0x80;
	CLKPR  = 0x00;

	// Initialize LCD and Joystick
	init_lcd();
	init_buttons();

	// Install interrupts for joystick
	INSTALL(&joy, joystickInterrupt, IRQ_PCINT0);
	INSTALL(&joy, joystickInterrupt, IRQ_PCINT1);
	gui.previousButton = 1;
	return TINYTIMBER(&gui, update_values, 0);
}

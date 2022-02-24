/*
 * Joystick.h
 *
 *  Created on: Feb 24, 2022
 *      Author: rovva
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "TinyTimber.h"
#include "GUI.h"

typedef struct {
	Object super;
	GUI *gui;
	bool firstClick;
} Joystick;

void joystickInterrupt(Joystick *self);

#define initJoystick(gui) { initObject(), gui, true }
#endif /* JOYSTICK_H_ */

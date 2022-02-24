/*
 * Joystick.h
 *
 *  Created on: Feb 24, 2022
 *      Author: rovva
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "GUI.h"

typedef struct {
	Object super;
	GUI *gui;
} Joystick;

void joystickInterrupt(Joystick *self);

#define initJoystick(gui) { initObject(), gui }
#endif /* JOYSTICK_H_ */

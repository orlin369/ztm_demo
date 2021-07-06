/*

Zontromat - Zonal Electronic Automation

Copyright (C) [2020] [POLYGONTeam Ltd.]

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef GPIO_DESCRIPTION_H
#define GPIO_DESCRIPTION_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/**
 * @brief PWM definition number.
 * 
 */
#define PWM_OUTPUT 0x03

/**
 * @brief Analog input.
 * 
 */
#define ANALOG_INPUT 0x04

/**
 * @brief Analog input.
 * 
 */
#define DIGITAL_FUNC_OUTPUT 0x05


/**
 * @brief GPIO Descriptior.
 * 
 */
typedef struct
{
    int Pin; ///< Pin number.
    int Index; ///< Bit index.
    int Type; ///< Pin type.
} GPIOs_t;


#endif // GPIO_DESCRIPTION_H
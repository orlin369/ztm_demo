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

#ifndef APPLICATION_CONFIGURATION_H
#define APPLICATION_CONFIGURATION_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#pragma region MODBUS

/**
 * @brief Slave ID.
 * 
 */
#define SLAVE_ID 1

/**
 * @brief Baudrate of the bus.
 * 
 */
#define SERIAL_BAUDRATE 9600

/**
 * @brief Serial port.
 * 
 */
#define SERIAL_PORT Serial

/**
 * @brief RS485 RE/DE control pin.
 * 
 */
#define PIN_RS485_CTRL -1

#pragma endregion

#pragma region Status LED

/**
 * @brief Pin for the status LED.
 * 
 */
#define PIN_STATUS_LED LED_BUILTIN

/**
 * @brief Status LED blinking interval.
 * 
 */
#define BLINK_INTERVAL 1000

#pragma endregion

#endif // APPLICATION_CONFIGURATION_H

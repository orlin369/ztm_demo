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

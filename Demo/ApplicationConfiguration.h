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

#pragma region PINs

/**
 * @brief Pin input PIR. 
 * 
 */
#define PIN_PIR 2

/**
 * @brief Pin input door tamper.
 * 
 */
#define PIN_DOOR_TAMPER 3

/**
 * @brief Pin input window tamper.
 * 
 */
#define PIN_WINDOW_TAMPER 4

/**
 * @brief PIn button open door.
 * 
 */
#define PIN_OPEN_DOOR 7

/**
 * @brief Pin door lock.
 * 
 */
#define PIN_DOOR_LOCK 8

/**
 * @brief Bit index of the pir input.
 * 
 */
#define INDEX_PIR 0

/**
 * @brief Bit index of the door tamper.
 * 
 */
#define INDEX_DOOR_TAMPER 1

/**
 * @brief Bit index of the window tamper.
 * 
 */
#define INDEX_WINDOW_TAMPER 2

/**
 * @brief Bit index of the button door open.
 * 
 */
#define INDEX_OPEN_DOOR 3

/**
 * @brief Bit index of door lock mechanism.
 * 
 */
#define INDEX_DOOR_LOCK 5

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

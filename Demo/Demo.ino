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

#pragma region Headers

#include "ApplicationConfiguration.h"

#include "GPIOdescription.h"

#include <ModbusSlave.h>

#pragma endregion

#pragma region Prototypes MODBUS

/**
 * @brief Setup the MODBUS module.
 * 
 */
void setup_mb();

/**
 * @brief Read coils callback function. Function code: 01.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_coils(uint8_t fc, uint16_t address, uint16_t length);

/**
 * @brief Read discrete inputs callback function. Function code: 02.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_discrete_inputs(uint8_t fc, uint16_t address, uint16_t length);

/**
 * @brief Read holding registers callback function. Function code: 03.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_holding_registers(uint8_t fc, uint16_t address, uint16_t length);

/**
 * @brief Read input registers callback function. Function code: 04.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_input_registers(uint8_t fc, uint16_t address, uint16_t length);

/**
 * @brief Write coils callback function. Function code: 05 and 15.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t write_coils(uint8_t fc, uint16_t address, uint16_t length);

/**
 * @brief Write coils callback function. Function code: 06 and 16.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t write_holding_registers(uint8_t fc, uint16_t address, uint16_t length);

#pragma endregion

#pragma region Prototypes Status LED

/**
 * @brief Update status LED.
 * 
 */
void update_status_led();

#pragma endregion

#pragma region Variables Pins

/**
 * @brief GPIO description.
 * 
 */
GPIOs_t GPIOs_g [] = 
{
    // PWM
    (GPIOs_t){5, 0, PWM_OUTPUT},
    (GPIOs_t){6, 1, PWM_OUTPUT},
    (GPIOs_t){9, 2, PWM_OUTPUT},
    (GPIOs_t){10, 3, PWM_OUTPUT},
    // Digital Out
    (GPIOs_t){8, 0, OUTPUT},
    // Analog Input
    (GPIOs_t){A0, 0, ANALOG_INPUT},
    (GPIOs_t){A1, 1, ANALOG_INPUT},
    (GPIOs_t){A2, 2, ANALOG_INPUT},
    (GPIOs_t){A3, 3, ANALOG_INPUT},
    // Digital Inputs
    (GPIOs_t){2, 0, INPUT_PULLUP},
    (GPIOs_t){3, 1, INPUT_PULLUP},
    (GPIOs_t){4, 2, INPUT_PULLUP},
    (GPIOs_t){7, 3, INPUT_PULLUP},
};

/**
 * @brief Size of the GPIO description.
 * 
 */
uint8_t GPIOsSize_g = (sizeof(GPIOs_g) / sizeof(GPIOs_g[0]));

#pragma endregion

#pragma region Variables MODBUS

/**
 * @brief Modbus Slave communicator.
 * 
 */
#ifdef PIN_RS485_CTRL
Modbus ModbusSlave_g(SERIAL_PORT, SLAVE_ID, PIN_RS485_CTRL);
#else
Modbus ModbusSlave_g(SERIAL_PORT, SLAVE_ID);
#endif

/**
 * @brief Coils memory block.
 * 
 */
uint8_t Coils_g[] = {false, false, false, false, false, false, false, false};

/**
 * @brief Size of the coils memory block.
 * 
 */
uint8_t CoilsSize_g = (sizeof(Coils_g) / sizeof(Coils_g[0])) + 1;

/**
 * @brief Discrete inputs memory block.
 * 
 */
uint8_t DiscreteInputs_g[] = {false, false, false, false, false, false, false, false};

/**
 * @brief Size of the discrete inputs memory block.
 * 
 */
uint8_t DiscreteInputsSize_g = (sizeof(DiscreteInputs_g) / sizeof(DiscreteInputs_g[0])) + 1;

/**
 * @brief Holding Registers memory block.
 * 
 */
uint16_t HoldingRegisters_g[] = {0, 0, 0, 0, 0, 0, 0, 0};

/**
 * @brief Size of the holding registers memory block.
 * 
 */
uint8_t HoldingRegistersSize_g = (sizeof(HoldingRegisters_g) / sizeof(HoldingRegisters_g[0])) + 1;

/**
 * @brief Input Registers memory block.
 * 
 */
uint16_t InputRegisters_g[] = {0, 0, 0, 0, 0, 0, 0, 0};

/**
 * @brief Size of the input registers memory block.
 * 
 */
uint8_t InputRegistersSize_g = (sizeof(InputRegisters_g) / sizeof(InputRegisters_g[0])) + 1;

/**
 * @brief Used to set the LED
 * 
 */
int StatusLEDState_g = LOW;

/**
 * @brief Will store last time status LED was updated.
 * 
 */
unsigned long PreviousTime_g = 0;

/**
 * @brief Curent time.
 * 
 */
unsigned long CurrentTime_g = 0;

#pragma endregion

/**
 * @brief Setup function.
 * 
 */
void setup()
{
    // Initialize the GPIOs.
    for (uint8_t index = 0; index < GPIOsSize_g; index++)
    {
        if (GPIOs_g[index].Type == INPUT_PULLUP)
        {
            pinMode(GPIOs_g[index].Pin, GPIOs_g[index].Type);
        }
        else if (GPIOs_g[index].Type == OUTPUT)
        {
            pinMode(GPIOs_g[index].Pin, GPIOs_g[index].Type);
            digitalWrite(GPIOs_g[index].Pin, LOW);
        }
        else if (GPIOs_g[index].Type == PWM_OUTPUT)
        {
            analogWrite(GPIOs_g[index].Pin, 0);
        }
        else if (GPIOs_g[index].Type == ANALOG_INPUT)
        {
            // Nothing...
        }
    }

    // Initialize the status LED.
    pinMode(PIN_STATUS_LED, OUTPUT);

    // Initialize the MODBUS module.
    setup_mb();

    // https://lastminuteengineers.com/multiple-ds18b20-arduino-tutorial/
    // Upper thermometer. / 1W
    // Middle thermometer. / 1W
    // Lower thermometer. / 1W

    // https://www.digikey.com/en/maker/projects/design-a-luxmeter-with-an-ldr-and-an-arduino/623aeee0f93e427bb57e02c4592567d1
    // Light sensor. / AI

    // https://create.arduino.cc/projecthub/electropeak/pir-motion-sensor-how-to-use-pirs-w-arduino-raspberry-pi-18d7fa
    // Motion sensor. / DI

    // https://create.arduino.cc/projecthub/tylerpeppy/25-khz-4-pin-pwm-fan-control-with-arduino-uno-3005a1
    // Fan / PWM

    // LEDs
    // Lamps / PWM

    // Digital output.
    // Door LOCK / DO
}

/**
 * @brief Loop function.
 * 
 */
void loop()
{
    // Update state of the inputs.
    for (uint8_t index = 0; index < GPIOsSize_g; index++)
    {
        if (GPIOs_g[index].Type == INPUT_PULLUP)
        {
            DiscreteInputs_g[GPIOs_g[index].Index] = (digitalRead(GPIOs_g[index].Pin) == LOW);
        }
        else if (GPIOs_g[index].Type == INPUT)
        {
            DiscreteInputs_g[GPIOs_g[index].Index] = (digitalRead(GPIOs_g[index].Pin) == LOW);
        }
        else if (GPIOs_g[index].Type == ANALOG_INPUT)
        {
            InputRegisters_g[GPIOs_g[index].Index] = map(analogRead(GPIOs_g[index].Pin), 0, 1023, 0, 50000);
        }
    }

    // Listen for modbus requests on the serial port.
    // When a request is received it's going to get validated.
    // And if there is a function registered to the received function code, this function will be executed.
    ModbusSlave_g.poll();

    static int DOL;
    static int AOL;

    // Update state of the outputs.
    DOL = LOW;
    AOL = 0;
    for (uint8_t index = 0; index < GPIOsSize_g; index++)
    {
        if (GPIOs_g[index].Type == OUTPUT)
        {
            DOL = Coils_g[GPIOs_g[index].Index] ? HIGH : LOW;
            digitalWrite(GPIOs_g[index].Pin, DOL);
        }
        else if (GPIOs_g[index].Type == PWM_OUTPUT)
        {
            AOL = map(HoldingRegisters_g[GPIOs_g[index].Index], 0, 50000, 0, 1023);
            analogWrite(GPIOs_g[index].Pin, AOL);
        }
    }

    // Update status LED.
    update_status_led();
}

#pragma region Functions MODBUS

/**
 * @brief Setup the MODBUS module.
 * 
 */
void setup_mb()
{
    // Register functions to call when a certain function code is received.
    ModbusSlave_g.cbVector[CB_READ_COILS] = read_coils;
    ModbusSlave_g.cbVector[CB_READ_DISCRETE_INPUTS] = read_discrete_inputs;
    ModbusSlave_g.cbVector[CB_READ_HOLDING_REGISTERS] = read_holding_registers;
    ModbusSlave_g.cbVector[CB_READ_INPUT_REGISTERS] = read_input_registers;
    ModbusSlave_g.cbVector[CB_WRITE_COILS] = write_coils;
    ModbusSlave_g.cbVector[CB_WRITE_HOLDING_REGISTERS] = write_holding_registers;

    // Set the serial port and slave to the given baudrate.
    SERIAL_PORT.begin(SERIAL_BAUDRATE);
    ModbusSlave_g.begin(SERIAL_BAUDRATE);
}

/**
 * @brief Read coils callback function. Function code: 01.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_coils(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > CoilsSize_g || (address + length) > CoilsSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Read the digital inputs.
    for (int i = 0; i < length; i++)
    {
        // Write the state of the digital pin to the response buffer.
        status = ModbusSlave_g.writeCoilToBuffer(i, Coils_g[i]);
    }

    return status;
}

/**
 * @brief Read discrete inputs callback function. Function code: 02.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_discrete_inputs(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > DiscreteInputsSize_g || (address + length) > DiscreteInputsSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Read the digital inputs.
    for (int i = 0; i < length; i++)
    {
        // Write the state of the digital pin to the response buffer.
        status = ModbusSlave_g.writeDiscreteInputToBuffer(i, DiscreteInputs_g[i]);
    }

    return status;
}

/**
 * @brief Read holding registers callback function. Function code: 03.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_holding_registers(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > HoldingRegistersSize_g || (address + length) > HoldingRegistersSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Read the analog inputs
    for (int i = 0; i < length; i++)
    {
        // Write the state of the analog pin to the response buffer.
        status = ModbusSlave_g.writeRegisterToBuffer(i, HoldingRegisters_g[i]);
    }

    return status;
}

/**
 * @brief Read input registers callback function. Function code: 04.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t read_input_registers(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > InputRegistersSize_g || (address + length) > InputRegistersSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Read the analog inputs
    for (int i = 0; i < length; i++)
    {
        // Write the state of the analog pin to the response buffer.
        status = ModbusSlave_g.writeRegisterToBuffer(i, InputRegisters_g[i]);
    }

    return status;
}

/**
 * @brief Write coils callback function. Function code: 05 and 15.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t write_coils(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > CoilsSize_g || (address + length) > CoilsSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Set the output pins to the given state.
    for (int i = 0; i < length; i++)
    {
        // Write the value in the input buffer to the digital pin.
        //digitalWrite(output_pins[address + i], ModbusSlave_g.readCoilFromBuffer(i));
        Coils_g[i] = ModbusSlave_g.readCoilFromBuffer(i);
    }

    return status;
}

/**
 * @brief Write coils callback function. Function code: 06 and 16.
 * 
 * @param fc Function code.
 * @param address Address index.
 * @param length Length of the request.
 * @return uint8_t Status code.
 */
uint8_t write_holding_registers(uint8_t fc, uint16_t address, uint16_t length)
{
    uint8_t status = STATUS_OK;

    // Check if the requested addresses exist in the array
    if (address > HoldingRegistersSize_g || (address + length) > HoldingRegistersSize_g)
    {
        return STATUS_ILLEGAL_DATA_ADDRESS;
    }

    // Read the analog inputs
    for (int i = 0; i < length; i++)
    {
        // Write the state of the analog pin to the response buffer.
        // ModbusSlave_g.writeRegisterToBuffer(i, 55+i);
        HoldingRegisters_g[i] = ModbusSlave_g.readRegisterFromBuffer(i);
    }

    return status;
}

#pragma endregion

#pragma region Functions Status LED

/**
 * @brief Update status LED.
 * 
 */
void update_status_led()
{
    CurrentTime_g = millis();
    
    if (CurrentTime_g - PreviousTime_g >= BLINK_INTERVAL)
    {
        // Save the last time you blinked the LED
        PreviousTime_g = CurrentTime_g;

        // If the LED is off turn it on and vice-versa:
        if (StatusLEDState_g == LOW)
        {
           StatusLEDState_g = HIGH;
        }
        else
        {
            StatusLEDState_g = LOW;
        }

        // Set the LED with the StatusLEDState_g of the variable:
        digitalWrite(PIN_STATUS_LED, StatusLEDState_g);
    }
}

#pragma endregion

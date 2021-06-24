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

#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <stdint.h>
#include "Inc/MCAL_gpio.h"

#define TRIG_PIN_1 0
#define ECHO_PIN_1 1

#define TRIG_PIN_2 0
#define ECHO_PIN_2 1

#define TRIG_PIN_3 0
#define ECHO_PIN_3 1

#define US_PORT GPIOB

#define SPEED_OF_SOUND_CM_PER_US 0.0343 // Speed of sound in centimeters per microsecond
#define MM_PER_CM 10                    // Millimeters per centimeter (1 cm = 10 mm)

#define PRESCALER 64


void Ultra_Init(S_GPIO_t *portName, uint8_t trig_pin, uint8_t echo_pin);
uint16_t GetUltrasonicDistance(S_GPIO_t *portName, uint8_t trig_pin, uint8_t echo_pin);

/*
 * Description: This function is used to check if the ultrasonic is
 * working correctly or not. It checks the echo pin for amount of time.
 *
 */
#endif /* ULTRASONIC_H */

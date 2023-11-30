#ifndef SPI_H_
#define SPI_H_

#include "Bit_Math.h"
#include <stdint.h>
#include "Inc/MCAL_gpio.h"

// Uncomment the following line to use SPI in slave mode
// #define SPI_SLAVE_MODE

#define SPI_PORT GPIOB

#define SPI_MOSI GPIO_PIN_5
#define SPI_MISO GPIO_PIN_6
#define SPI_SCK GPIO_PIN_7
#define SPI_SS GPIO_PIN_4

#define SPCR (*(volatile uint8_t *)(0x2C)) // SPCR address for ATmega32
// Define SPI Status Register (SPSR) with its address and bit definitions
#define SPSR (*(volatile uint8_t *)(0x2D)) // SPSR address for ATmega32
// Define SPI Data Register (SPDR) with its address
#define SPDR (*(volatile uint8_t *)(0x2E)) // SPDR address for ATmega32

// SPI Control Register (SPCR) bits
#define SPIE 7 // SPI Interrupt Enable
#define SPE 6  // SPI Enable
#define DORD 5 // Data Order (0: MSB first, 1: LSB first)
#define MSTR 4 // Master/Slave Select
#define CPOL 3 // Clock Polarity (0: SCK low when idle, 1: SCK high when idle)
#define CPHA 2 // Clock Phase (0: Sample on leading edge, 1: Sample on trailing edge)
#define SPR0 0 // SPI Clock Rate Select 0
#define SPR1 1 // SPI Clock Rate Select 1


// SPI Status Register (SPSR) bits
#define SPI2X 0 // Double SPI Speed Bit
#define WCOL 6  // Write Collision Flag
#define SPIF 7  // SPI Transfer Complete Flag

void SPI_init_master(uint8_t freq_div);
void SPI_init_slave();
uint8_t SPI_transfer(uint8_t data);

#endif /* SPI_H_ */
#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

// I2C Modes
#ifndef I2C_AVR_H_
#define I2C_AVR_H_

#define I2C_MASTER 0
#define I2C_SLAVE 1

// Define I2C prescaler values in an enum
typedef enum  {
    I2C_Prescaler_1 = 0,
    I2C_Prescaler_4,
    I2C_Prescaler_16,
    I2C_Prescaler_64
}I2C_Prescaler;
// Define bit masks for I2C Control Register
typedef struct
{
    volatile uint8_t TWSTA : 1; // TWI Start Condition bit
    volatile uint8_t TWSTO : 1; // TWI Stop Condition bit
    volatile uint8_t TWEA : 1;  // TWI Enable Acknowledge bit
    volatile uint8_t TWEN : 1;  // TWI Enable bit
    volatile uint8_t TWIE : 1;  // TWI Interrupt Enable bit
    volatile uint8_t TWINT : 1; // TWI Interrupt Flag bit
    uint8_t reserved : 2;
} TWCR_bits;

// Define bit masks for I2C Status Register
typedef struct
{
    uint8_t reserved : 3;
    uint8_t TWS : 5; // TWI Status
} TWSR_bits;

// Define the I2C base address and struct
typedef struct
{
    volatile uint8_t TWBR;       // TWI Bit Rate Register
    volatile TWSR_bits TWSR_bit; // TWI Status Register
    volatile uint8_t TWAR;       // TWI (Slave) Address Register
    volatile uint8_t TWDR;       // TWI Data Register
    volatile TWCR_bits TWCR_bit; // TWI Control Register
    volatile uint8_t TWAMR;      // TWI (Slave) Address Mask Register
} I2C_Registers;

// Create an instance of the struct to access I2C registers
#define I2C ((I2C_Registers *)0x20)

#endif /* I2C_AVR_H_ */

// Initialize I2C communication
void I2C_init(uint8_t mode, uint32_t bitrate, uint8_t slaveAddress);

// I2C master functions
void I2C_start();
void I2C_stop();
void I2C_write(uint8_t data);
uint8_t I2C_read_ack();
uint8_t I2C_read_nack();

// I2C slave functions
void I2C_set_slave_address(uint8_t address);
void I2C_slave_listen();

#endif /* I2C_H_ */

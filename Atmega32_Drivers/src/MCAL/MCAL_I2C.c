#include "Inc/MCAL_i2c.h"

static uint8_t i2c_mode = I2C_MASTER;

void I2C_init(uint8_t mode, uint32_t bitrate, uint8_t slaveAddress) {
    i2c_mode = mode;

    // Calculate bit rate division factor
    uint16_t bitrate_div = ((F_CPU / bitrate) - 16) / 2;

    // Set bit rate register
    I2C->TWBR = (uint8_t)bitrate_div;

    if (i2c_mode == I2C_SLAVE) {
        // Set the slave address and enable TWI (I2C)
        I2C->TWAR = (slaveAddress << 1);
        I2C->TWCR_bit.TWEN = 1;
        I2C->TWCR_bit.TWEA = 1;
    } else if (i2c_mode == I2C_MASTER) {
        // Enable TWI (I2C)
        I2C->TWCR_bit.TWEN = 1;
    }
}

// I2C master functions
void I2C_start() {
    I2C->TWCR_bit.TWSTA = 1;
    I2C->TWCR_bit.TWEN = 1;
    while (!(I2C->TWCR_bit.TWINT));
}

void I2C_stop() {
    I2C->TWCR_bit.TWSTO = 1;
    I2C->TWCR_bit.TWEN = 1;
}

void I2C_write(uint8_t data) {
    I2C->TWDR = data;
    I2C->TWCR_bit.TWEN = 1;
    while (!(I2C->TWCR_bit.TWINT));
}

uint8_t I2C_read_ack() {
    I2C->TWCR_bit.TWEN = 1;
    I2C->TWCR_bit.TWEA = 1;
    while (!(I2C->TWCR_bit.TWINT));
    return I2C->TWDR;
}

uint8_t I2C_read_nack() {
    I2C->TWCR_bit.TWEN = 1;
    while (!(I2C->TWCR_bit.TWINT));
    return I2C->TWDR;
}

// I2C slave functions
void I2C_set_slave_address(uint8_t address) {
    I2C->TWAR = (address << 1);
}

void I2C_slave_listen() {
    I2C->TWCR_bit.TWEN = 1;
    I2C->TWCR_bit.TWEA = 1;
    while (!(I2C->TWCR_bit.TWINT));

    if ((I2C->TWSR_bit.TWS & 0xF8) == 0x60 || (I2C->TWSR_bit.TWS & 0xF8) == 0xA8) {
        // Addressed in slave receiver mode
        I2C->TWCR_bit.TWEN = 1;
        I2C->TWCR_bit.TWEA = 1;
        while (!(I2C->TWCR_bit.TWINT));
    } else if ((I2C->TWSR_bit.TWS & 0xF8) == 0x80) {
        // Data byte received in slave receiver mode
        // Process the data in TWDR
        I2C->TWCR_bit.TWEN = 1;
        I2C->TWCR_bit.TWEA = 1;
        while (!(I2C->TWCR_bit.TWINT));
    }
}

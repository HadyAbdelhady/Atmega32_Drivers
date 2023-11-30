#ifndef _EEPROM_H
#define _EEPROM_H

#include <stdint.h>
/*-----------------------------------------------*/
// Define the EEPROM base address and struct
typedef struct {
    volatile uint8_t EECR;   // EEPROM Control Register
    volatile uint8_t EEDR;   // EEPROM Data Register
    volatile uint8_t EEARL;  // EEPROM Address Register Low Byte
    volatile uint8_t EEARH;  // EEPROM Address Register High Byte
} EEPROM_Registers;

// Create an instance of the struct to access EEPROM registers

// Define the EEPROM Control Register bit masks
#define EEPROM_EEWE 1
#define EEPROM_EEMWE 2
#define EEPROM_EERE 0

#define EEPROM ((EEPROM_Registers *)0x3F)
/************************* Defines ************************/
#define ERASE 0xFF
/******************** Create Functions ********************/
void EEPROM_write(uint16_t uiaddress, uint8_t ucdata);
void EEPROM_erase(uint16_t start_byte, uint16_t end_byte);
void EEPROM_write_nbyte(uint8_t *str, uint16_t start_byte, uint16_t nbyte);
uint8_t EEPROM_read(uint8_t uiaddress);
void EEPROM_read_nbyte(uint8_t *str, uint16_t start_byte, uint16_t nbyte);
/******************* End Of The Program *******************/
#endif
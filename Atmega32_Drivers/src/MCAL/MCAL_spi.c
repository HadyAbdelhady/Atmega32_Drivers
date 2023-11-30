#include "Inc/MCAL_spi.h"
#include "Inc/MCAL_gpio.h"
#ifdef SPI_SLAVE_MODE
void SPI_init_slave()
{
    MCAL_GPIO_SET_Pin(SPI_PORT, Input, SPI_SS);
    MCAL_GPIO_SET_Pin(SPI_PORT, Input, SPI_SCK);
    MCAL_GPIO_SET_Pin(SPI_PORT, Input, SPI_MOSI);
    MCAL_GPIO_SET_Pin(SPI_PORT, Output, SPI_MISO);

    // disable interrupt
    CLR_BIT(SPCR, SPIE);

    // LSB --select data direction
    SET_BIT(SPCR, DORD);

    // enable slave SS
    CLR_BIT(SPCR, MSTR);

    // polarity >> leading edge is rising
    CLR_BIT(SPCR, CPOL);

    // Sample at leading edge >> sample= receive
    CLR_BIT(SPCR, CPHA);

    // SPI enable
    SET_BIT(SPCR, SPE);
}
#else
void SPI_init_master(uint8_t freq_div)
{
    // Set MOSI, SCK and SS as output pins
    MCAL_GPIO_Set_Port_Direction(SPI_PORT, (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS));
    // Set MISO as input pin
    MCAL_GPIO_SET_Pin(SPI_PORT, Input, SPI_MISO);
    MCAL_GPIO_WritePin(SPI_PORT, GPIO_PIN_4, LOW);

    // disable interrupt
    CLR_BIT(SPCR, SPIE);

    // LSB --select data direction
    SET_BIT(SPCR, DORD);

    // polarity >> leading edge is rising
    CLR_BIT(SPCR, CPOL);
    // clock phase,set leading
    // Sample at leading edge >> sample= receive
    CLR_BIT(SPCR, CPHA);

    switch (freq_div)
    {
    case 2:
        CLR_BIT(SPCR, SPR1);
        SET_BIT(SPCR, SPR0);
        break;
    case 4:
        SPCR &= ~((1 << SPR1) | (1 << SPR0));
        break;
    case 8:
        CLR_BIT(SPCR, SPR0);
        SET_BIT(SPCR, SPR1);
        break;
    case 16:
        SPCR |= (1 << SPR1) | (1 << SPR0);
        break;
    default:
        break;
    }

    // Enable SPI, set as master, set clock rate
    SPCR |= (1 << SPE) | (1 << MSTR);
}
#endif

uint8_t SPI_transfer(uint8_t data)
{
    SPDR = data;
    // Wait for transmission to complete
    while (READ_BIT(SPSR, SPIF) == 0)
        ;
    return SPDR;
}

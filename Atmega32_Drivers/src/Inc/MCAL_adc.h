
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

// USER TYPE DEFINITIONs
//-----------------------------
typedef struct
{

	uint8_t ADC_Mode; // specifies ADC Mode
	// This parameter must be set based on @ref ADC_MODE_DEFINE

	uint8_t ADC_Volt_Ref; // specifies ADC Voltage Referrnce
	// This parameter must be set based on @ref ADC_VOLT_REF_DEFINE

	uint8_t ADC_Res_presentation; // specifies ADC Output result presentation(right adjusted or left adjusted)
	// This parameter must be set based on @ref ADC_RES_PRESENTATION_DEFINE

	uint8_t ADC_Prescaler; //  Selects the division factor between the XTAL frequency and the input clock to ADC
	// This parameter must be set based on @ref ADC_PRESCALER_DEFINE

	uint8_t ADC_IRQ_Enable; // Enable or Disable IRQ
	// This parameter must be set based on @ref ADC_IRQ_ENABLE_DEFINE

	void (*P_CallBack)(void); // set the C Function which will be called once IRQ Happens
} ADC_Config_t;

// Macros

//@ref ADC_MODE_DEFINE
#define ADC_MODE_SINGLE_CONVERSION (uint8_t)(0)
#define ADC_MODE_FREE_RUNNING (uint8_t)(1 << ADCSRA)

//@ref ADC_VOLT_REF_DEFINE
#define ADC_VOLT_REF_AREF (0 << 7 | 0 << 6)
#define ADC_VOLT_REF_AVCC (0 << 7 | 1 << 6)
#define ADC_VOLT_REF_INTERNAL (1 << 7 | 1 << 6)

//@ref ADC_RES_PRESENTATION_DEFINE
#define ADC_RES_PRESENTATION_RIGHT_ADJUSTED (uint8_t)(0)
#define ADC_RES_PRESENTATION_LEFT_ADJUSTED (uint8_t)(1 << 5)

//@ref ADC_PRESCALER_DEFINE
#define ADC_PRESCALER_2 (1 << 0)
#define ADC_PRESCALER_4 (2 << 0)
#define ADC_PRESCALER_8 (3 << 0)
#define ADC_PRESCALER_16 (4 << 0)
#define ADC_PRESCALER_32 (5 << 0)
#define ADC_PRESCALER_64 (6 << 0)
#define ADC_PRESCALER_128 (7 << 0)

//@ref ADC_IRQ_ENABLE_DEFINE
#define ADC_IRQ_ENABLE_NONE (0 << 3)
#define ADC_IRQ_ENABLE_ADIE (1 << 3)

// ADC register addresses
#define ADCSRA *((volatile uint8_t*)0x26)
#define ADMUX *((volatile uint8_t*)0x27)
#define SFIOR *((volatile uint8_t*)0x50)
#define ADCL *((volatile uint8_t *)(0x24))
#define ADCH *((volatile uint8_t *)(0x25))


typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
} Channel_Select_t;

// Enum for ADC reference voltage selection
typedef enum
{
	ADC_REF_EXTERNAL_AREF,
	ADC_REF_AVCC,
	ADC_REF_INTERNAL_2V56
} ADC_ReferenceVoltage_t;

// Enum for ADC result presentation
typedef enum
{
	ADC_RESULT_RIGHT_ADJUSTED,
	ADC_RESULT_LEFT_ADJUSTED
} ADC_ResultPresentation_t;

// Enum for ADC interrupt enable
typedef enum
{
	ADC_IRQ_DISABLE,
	ADC_IRQ_ENABLE
} ADC_IRQ_Enable_t;

// Enum for polling mechanism
typedef enum
{
	ADC_POLLING_DISABLE,
	ADC_POLLING_ENABLE
} ADC_PollingMechanism_t;
/*
 *============================================
 *============================================
 * APIs Supported by "MCAL ADC DRIVER"
 *============================================
 *============================================
 *
 */
void MCAL_ADC_Init(ADC_Config_t *config);
void MCAL_ADC_DeInit(void);

void MCAL_ADC_Start_Conversion(void);
void MCAL_ADC_Get_Result(Channel_Select_t channel, uint16_t *data, ADC_PollingMechanism_t polling);

#endif /* ADC_H_ */
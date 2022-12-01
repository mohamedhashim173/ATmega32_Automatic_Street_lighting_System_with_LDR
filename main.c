/*
 * main.c
 *
 *  Created on: Oct 25, 2022
 *      Author: MSAEED99
 */

// AVR Libraries
#include <util/delay.h>

// Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"
#include "ADC_interface.h"

// HAL
#include "LCD_interface.h"

// Macros
#define LDR_READ_MAX	256

/* Lab 03
 * Using LDR, implement a system that turns on a LED when it gets dark,
   and turns the LED off when it gets bright.
 */

void main(void)
{
	u8 local_u8ChannelRead;

	// Initialize LCD
	LCD_voidInit();

	// Initialize ADC input pin PinA0
	ADC_voidADCInit();
	DIO_voidSetPinDirection(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_INPUT);

	// LEDs
	DIO_voidSetPortDirection(DIO_u8PORTB, DIO_u8PORT_OUTPUT);


	LCD_voidSendString("Light level:");

	while(1)
	{
		// Update ADC channel read
		local_u8ChannelRead = ADC_u8GetChannelRead(0);

		// LED light compensation and LCD monitoring
		if(local_u8ChannelRead > LDR_READ_MAX * 4 / 5)
		{
			DIO_voidSetPortValue(DIO_u8PORTB, 0b00000000);

			// Display light level
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString("Noon      ");
		}
		else if(local_u8ChannelRead > LDR_READ_MAX * 3 / 5)
		{
			DIO_voidSetPortValue(DIO_u8PORTB, 0b00000011);

			// Display light level
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString("01:00PM   ");
		}
		else if(local_u8ChannelRead > LDR_READ_MAX * 2 / 5)
		{
			DIO_voidSetPortValue(DIO_u8PORTB, 0b00001111);

			// Display light level
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString("03:00PM   ");
		}
		else if(local_u8ChannelRead > LDR_READ_MAX * 1 / 5)
		{
			DIO_voidSetPortValue(DIO_u8PORTB, 0b00111111);

			// Display light level
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString("Sun Set   ");
		}
		else if(local_u8ChannelRead > LDR_READ_MAX * 0 / 5)
		{
			DIO_voidSetPortValue(DIO_u8PORTB, 0b11111111);

			// Display light level
			LCD_voidPositionSet(1, 0);
			LCD_voidSendString("Evening   ");
		}

		_delay_ms(1000);
	}
}



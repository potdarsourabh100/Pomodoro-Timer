/**
 * \file           TM1637.c
 * \brief          TM1637 source file
 */

/*
 * Copyright (c) 2024 Sourabh Potdar
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sub-license, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Author:          Sourabh Potdar
 * Version:         V1.0.0
 */

/*****************************************************************************/
/* Include Files                                                             */
/*****************************************************************************/
#include "TM1637.h"
/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
static const uint8_t tm1637digitpattern[] = {    0b00111111,    /* 0 */
										   	   	 0b00000110,    /* 1 */
												 0b01011011,    /* 2 */
												 0b01001111,    /* 3 */
												 0b01100110,    /* 4 */
												 0b01101101,    /* 5 */
												 0b01111101,    /* 6 */
												 0b00000111,    /* 7 */
												 0b01111111,    /* 8 */
												 0b01101111,    /* 9 */
												 0b01000000,    /* - */
												 0b10000000,    /* . */
											};

static uint8_t tm1637currentdisplayvalue[MAX_NO_OF_CHARACTERS] = { };

/*****************************************************************************/
/* TM1637 Functions                                                          */
/*****************************************************************************/
void delay_Us(int time)
{
	for(int i = 0; i < time; i++)
		{
			for(int j = 0; j < 3; j++)
				__asm__("nop");
		}
}
void TM1637_Start (void)
{

	CLK_HIGH();
	DATA_HIGH();
	delay_Us(2);
	DATA_LOW();
}

void TM1637_Stop (void)
{
	CLK_LOW();
	delay_Us(2);
	DATA_LOW();
	delay_Us(2);
	CLK_HIGH();
	delay_Us(2);
	DATA_HIGH();
}

void TM1637_WaitForAck (void)
{
	CLK_LOW();
	delay_Us(5); // After the falling edge of the eighth clock delay 5us
	              // ACK signals the beginning of judgment
	CLK_HIGH();
	delay_Us(2);
	CLK_LOW();
}

void TM1637_WriteByte (uint8_t byte)
{
	int i;
	for (i = 0; i<8; i++)
	{
		CLK_LOW();
		if (byte & 0x01) // low front
		{
			DATA_HIGH();
		}
		else
		{
			DATA_LOW();
		}
		delay_Us(3);
		byte = byte >> 1;
		CLK_HIGH();
		delay_Us(3);
	}
}

void TM1637_WriteDataCommand(uint8_t datacommand)
{
	TM1637_Start();
	TM1637_WriteByte(datacommand);
	TM1637_WaitForAck();
	TM1637_Stop();
}

void TM1637_WriteData(uint8_t address, uint8_t *data)
{
	TM1637_Start();
	TM1637_WriteByte(address);
	TM1637_WaitForAck();
	for (int i = 0; i < MAX_NO_OF_CHARACTERS; i++)
	{
		TM1637_WriteByte(tm1637digitpattern[data[i]]);
		TM1637_WaitForAck();
	}
	TM1637_Stop();
}

void TM1637_WriteDisplayCommand(uint8_t displaycommand)
{
	TM1637_Start();
	TM1637_WriteByte(displaycommand);
	TM1637_WaitForAck();
	TM1637_Stop();
}

void TM1637_Write(uint8_t datacommand,uint8_t address,uint8_t *data,uint8_t displaycommand)
{
		TM1637_Start();
		TM1637_WriteByte(datacommand);
		TM1637_WaitForAck();
		TM1637_Stop();

		TM1637_Start();
		TM1637_WriteByte(address);
		TM1637_WaitForAck();
		for (int i = 0; i < MAX_NO_OF_CHARACTERS; i++)
		{
			tm1637currentdisplayvalue[i] = tm1637digitpattern[data[i]];
			TM1637_WriteByte(tm1637digitpattern[data[i]]);
			TM1637_WaitForAck();
		}
		TM1637_Stop();

		TM1637_Start();
		TM1637_WriteByte(displaycommand);
		TM1637_WaitForAck();
		TM1637_Stop();
}

void TM1637_Convert_To_Digits(uint32_t values, uint8_t digits[4])
{
    uint32_t minutes = values / 60;
    uint32_t seconds = values % 60;

    digits[0] = minutes / 10;        // Tens place of minutes
    digits[1] = minutes % 10;        // Ones place of minutes
    digits[2] = seconds / 10;        // Tens place of seconds
    digits[3] = seconds % 10;        // Ones place of seconds
}

void TM1637_Update_Data_Dots(uint8_t *displayvalue, uint8_t status)
{
	TM1637_Start();
	TM1637_WriteByte((DATA_COMMAND|WRITE_DATA_TO_DISPLAY|AUTOMATIC_ADDRESS_ADD|NORMAL_MODE));
	TM1637_WaitForAck();
	TM1637_Stop();

	if(status)
	{
		TM1637_Start();
		TM1637_WriteByte(DISPLAY_1_REGISTER_ADDRESS);
		TM1637_WaitForAck();
		for (int i = 0; i < MAX_NO_OF_CHARACTERS; i++)
		{
			TM1637_WriteByte((tm1637digitpattern[displayvalue[i]] | tm1637digitpattern[11]));
			TM1637_WaitForAck();
		}
		TM1637_Stop();
	}
	else
	{
		TM1637_Start();
		TM1637_WriteByte(DISPLAY_1_REGISTER_ADDRESS);
		TM1637_WaitForAck();
		for (int i = 0; i < MAX_NO_OF_CHARACTERS; i++)
		{
			TM1637_WriteByte(tm1637digitpattern[displayvalue[i]]);
			TM1637_WaitForAck();
		}
		TM1637_Stop();
	}

	TM1637_Start();
	TM1637_WriteByte((DISPLAY_COMMAND|PULSE_WIDTH_SET_04_16|DISPLAY_ON));
	TM1637_WaitForAck();
	TM1637_Stop();
}

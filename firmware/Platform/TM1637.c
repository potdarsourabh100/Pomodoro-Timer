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
/*****************************************************************************
 * @brief Generates a delay in microseconds.
 *
 * @details This function creates a rough delay using nested loops and NOP
 *          instructions. It is not highly accurate and depends on CPU speed.
 *
 * @param[in] time  Number of microseconds to delay (approximate).
 *
 * @return None
 *
 * @retval None
 *
 * @note Best used for small delays like 1–10 microseconds. Not suitable
 *       for precise timing.
 *
 * @warning Delay accuracy is affected by compiler optimization and CPU speed.
 *****************************************************************************/
void delay_Us(int time)
{
	for(int i = 0; i < time; i++)
		{
			for(int j = 0; j < 3; j++)
				__asm__("nop");
		}
}
/*****************************************************************************
 * @brief Sends the start signal for TM1637 communication.
 *
 * @details Initiates the communication by setting CLK and DATA high, then
 *          pulling DATA low after a short delay.
 *
 * @param None
 *
 * @return None
 *
 * @retval None
 *
 * @note Must be called before sending data to TM1637.
 *
 * @see TM1637_Stop(), TM1637_WriteByte()
 *****************************************************************************/
void TM1637_Start (void)
{

	CLK_HIGH();
	DATA_HIGH();
	delay_Us(2);
	DATA_LOW();
}
/*****************************************************************************
 * @brief Sends the stop signal to TM1637 display.
 *
 * @details Ends the communication by pulling CLK and DATA low, then raising
 *          CLK and DATA with appropriate delays.
 *
 * @param None
 *
 * @return None
 *
 * @retval None
 *
 * @note Must be called after completing any TM1637 data transmission.
 *
 * @see TM1637_Start(), TM1637_WriteByte()
 *****************************************************************************/
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
/*****************************************************************************
 * @brief Waits for an acknowledgment from the TM1637 display.
 *
 * @details After sending 8 bits, this function waits for a brief time,
 *          toggles the clock line to read the ACK signal from the display.
 *
 * @param None
 *
 * @return None
 *
 * @retval None
 *
 * @note Called internally after each byte sent to TM1637.
 *
 * @warning TM1637 does not return a readable ACK signal on all boards.
 *
 * @see TM1637_WriteByte()
 *****************************************************************************/
void TM1637_WaitForAck (void)
{
	CLK_LOW();
	delay_Us(5); // After the falling edge of the eighth clock delay 5us
	              // ACK signals the beginning of judgment
	CLK_HIGH();
	delay_Us(2);
	CLK_LOW();
}
/*****************************************************************************
 * @brief Sends a single byte to the TM1637 display.
 *
 * @details Sends each bit starting from the least significant bit (LSB) by
 *          setting the DATA line and toggling the CLK line.
 *
 * @param[in] byte  The 8-bit data to send.
 *
 * @return None
 *
 * @retval None
 *
 * @note Called in sequences to send data or commands to TM1637.
 *
 * @see TM1637_Start(), TM1637_WaitForAck()
 *****************************************************************************/
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
/*****************************************************************************
 * @brief Sends a command to TM1637 to configure data writing.
 *
 * @details Sends a single byte command to set the data writing mode, such as
 *          fixed address or auto increment mode.
 *
 * @param[in] datacommand  Command byte as per TM1637 protocol.
 *
 * @return None
 *
 * @retval None
 *
 * @note This should be the first command before writing actual data.
 *
 * @see TM1637_WriteByte(), TM1637_WaitForAck()
 *****************************************************************************/
void TM1637_WriteDataCommand(uint8_t datacommand)
{
	TM1637_Start();
	TM1637_WriteByte(datacommand);
	TM1637_WaitForAck();
	TM1637_Stop();
}
/*****************************************************************************
 * @brief Writes multiple digits to TM1637 display starting from a given address.
 *
 * @details Sends a start condition, address, and then digit pattern values
 *          from the data buffer using auto-increment mode.
 *
 * @param[in] address  TM1637 starting register address.
 * @param[in] data     Pointer to an array of display digit values.
 *
 * @return None
 *
 * @retval None
 *
 * @note Expects `data` to have `MAX_NO_OF_CHARACTERS` elements.
 *
 * @see TM1637_WriteByte(), TM1637_WaitForAck(), TM1637_Stop()
 *****************************************************************************/
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
/*****************************************************************************
 * @brief Sends a display control command to TM1637.
 *
 * @details Typically used to set brightness and display ON/OFF status.
 *
 * @param[in] displaycommand  Command byte for display control.
 *
 * @return None
 *
 * @retval None
 *
 * @note Should be called after data writing to update the display output.
 *
 * @see TM1637_WriteByte(), TM1637_Stop()
 *****************************************************************************/
void TM1637_WriteDisplayCommand(uint8_t displaycommand)
{
	TM1637_Start();
	TM1637_WriteByte(displaycommand);
	TM1637_WaitForAck();
	TM1637_Stop();
}
/*****************************************************************************
 * @brief Sends a complete write sequence to TM1637 display.
 *
 * @details Sends data command, address and data bytes, and a display command
 *          in a complete write cycle. Stores the current display state.
 *
 * @param[in] datacommand     Data mode command byte.
 * @param[in] address         Starting register address.
 * @param[in] data            Pointer to digit values to be displayed.
 * @param[in] displaycommand  Display control command byte.
 *
 * @return None
 *
 * @retval None
 *
 * @note Combines all steps to write to TM1637 in one function.
 *
 * @warning Expects `data` to have `MAX_NO_OF_CHARACTERS` entries.
 *
 * @see TM1637_Start(), TM1637_WriteByte(), TM1637_Stop()
 *****************************************************************************/
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
/*****************************************************************************
 * @brief Converts a time value in seconds into 4 display digits.
 *
 * @details Converts `values` (in seconds) to minutes and seconds, then
 *          splits into tens and ones for display on TM1637.
 *
 * @param[in]  values  Time in seconds.
 * @param[out] digits  Array of 4 elements to store digit values.
 *
 * @return None
 *
 * @retval None
 *
 * @note Used before sending data to TM1637 to prepare digit format.
 *
 * @see TM1637_WriteData()
 *****************************************************************************/
void TM1637_Convert_To_Digits(uint32_t values, uint8_t digits[4])
{
    uint32_t minutes = values / 60;
    uint32_t seconds = values % 60;

    digits[0] = minutes / 10;        /* Tens place of minutes*/
    digits[1] = minutes % 10;        /* Ones place of minutes*/
    digits[2] = seconds / 10;        /* Tens place of seconds*/
    digits[3] = seconds % 10;        /* Ones place of seconds*/
}
/*****************************************************************************
 * @brief Updates the TM1637 display with optional dots (colon).
 *
 * @details Sends digit patterns with or without the dot segment active
 *          depending on `status`. Handles full write cycle including commands.
 *
 * @param[in] displayvalue  Pointer to array of digit values to display.
 * @param[in] status        Boolean flag to enable (true) or disable (false) dots.
 *
 * @return None
 *
 * @retval None
 *
 * @note Commonly used to blink the colon every second for visual feedback.
 *
 * @see TM1637_Write(), TM1637_WriteDisplayCommand()
 *****************************************************************************/
void TM1637_Update_Data_Dots(uint8_t *displayvalue, uint8_t status);

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
/*************************************END*************************************/

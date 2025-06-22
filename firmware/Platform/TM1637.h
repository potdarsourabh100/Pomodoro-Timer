/**
 * \file           TM1637.h
 * \brief          TM1637 header file
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


#ifndef TM1637_H_
#define TM1637_H_

#ifdef __cplusplus
extern "C"
{
#endif
/*****************************************************************************/
/* Include Files                                                             */
/*****************************************************************************/
#include "Platform_Translate.h"

/*****************************************************************************/
/* TM1637 Macros                                                             */
/*****************************************************************************/

/**
 * @brief Maximum number of characters the TM1637 display supports.
 *
 * @note Typically 6 for 6-digit 7-segment displays.
 */
#define MAX_NO_OF_CHARACTERS                 6

/**
 * @brief Number of digits used for numeric display (e.g., time MM:SS).
 *
 * @note Used for handling formatting or grouping of digits.
 */
#define NO_OF_DIGIT_CHARACTERS               2

/**
 * @brief TM1637 register address for digit 1 (leftmost).
 */
#define DISPLAY_1_REGISTER_ADDRESS           0xC0

/**
 * @brief TM1637 register address for digit 2.
 */
#define DISPLAY_2_REGISTER_ADDRESS           0xC1

/**
 * @brief TM1637 register address for digit 3.
 */
#define DISPLAY_3_REGISTER_ADDRESS           0xC2

/**
 * @brief TM1637 register address for digit 4.
 */
#define DISPLAY_4_REGISTER_ADDRESS           0xC3

/**
 * @brief TM1637 register address for digit 5.
 */
#define DISPLAY_5_REGISTER_ADDRESS           0xC4

/**
 * @brief TM1637 register address for digit 6 (rightmost).
 */
#define DISPLAY_6_REGISTER_ADDRESS           0xC5

/**
 * @brief Base command to begin writing data to TM1637.
 */
#define DATA_COMMAND                         0x40

/**
 * @brief Command option to write display data.
 */
#define WRITE_DATA_TO_DISPLAY                0x00

/**
 * @brief Command option to read key scan data.
 */
#define READ_KEY_SCAN_DATA                   0x02

/**
 * @brief Addressing mode: automatic address increment.
 */
#define AUTOMATIC_ADDRESS_ADD                0x00

/**
 * @brief Addressing mode: fixed address mode.
 */
#define FIX_ADDRESS                          0x04

/**
 * @brief Operating mode: normal display mode.
 */
#define NORMAL_MODE                          0x00

/**
 * @brief Operating mode: test mode for segment diagnostics.
 */
#define TEST_MODE                            0x08

/**
 * @brief Base command to configure display settings.
 */
#define DISPLAY_COMMAND                      0x80

/**
 * @brief Set display brightness to 1/16 pulse width.
 */
#define PULSE_WIDTH_SET_01_16                0x00

/**
 * @brief Set display brightness to 2/16 pulse width.
 */
#define PULSE_WIDTH_SET_02_16                0x01

/**
 * @brief Set display brightness to 4/16 pulse width.
 */
#define PULSE_WIDTH_SET_04_16                0x02

/**
 * @brief Set display brightness to 10/16 pulse width.
 */
#define PULSE_WIDTH_SET_10_16                0x03

/**
 * @brief Set display brightness to 11/16 pulse width.
 */
#define PULSE_WIDTH_SET_11_16                0x04

/**
 * @brief Set display brightness to 12/16 pulse width.
 */
#define PULSE_WIDTH_SET_12_16                0x05

/**
 * @brief Set display brightness to 13/16 pulse width.
 */
#define PULSE_WIDTH_SET_13_16                0x06

/**
 * @brief Set display brightness to 14/16 pulse width.
 */
#define PULSE_WIDTH_SET_14_16                0x07

/**
 * @brief Command to turn display ON.
 */
#define DISPLAY_ON                           0x08

/**
 * @brief Command to turn display OFF.
 */
#define DISPLAY_OFF                          0x00

/*****************************************************************************/
/* TM1637 Function Declarations                                              */
/*****************************************************************************/

/**
 * @brief Generates an approximate delay in microseconds.
 *
 * @param[in] time Number of microseconds (approximate).
 */
void Delay_us(int time);

/**
 * @brief Sends the start signal for TM1637 communication.
 */
void TM1637_Start(void);

/**
 * @brief Sends the stop signal to TM1637 display.
 */
void TM1637_Stop(void);

/**
 * @brief Waits for an acknowledgment from TM1637 after byte transmission.
 */
void TM1637_WaitForAck(void);

/**
 * @brief Sends a byte to the TM1637 via GPIO.
 *
 * @param[in] byte 8-bit data to send.
 */
void TM1637_WriteByte(uint8_t byte);

/**
 * @brief Sends a TM1637 data command (e.g., auto increment or fixed address).
 *
 * @param[in] datacommand Data command byte.
 */
void TM1637_WriteDataCommand(uint8_t datacommand);

/**
 * @brief Writes data to TM1637 display starting at a specific address.
 *
 * @param[in] address TM1637 digit register address.
 * @param[in] data    Pointer to digit data array.
 */
void TM1637_WriteData(uint8_t address, uint8_t *data);

/**
 * @brief Sends a TM1637 display control command (e.g., brightness, ON/OFF).
 *
 * @param[in] displaycommand Display command byte.
 */
void TM1637_WriteDisplayCommand(uint8_t displaycommand);

/**
 * @brief Sends a complete sequence of command, address, data, and display control.
 *
 * @param[in] datacommand     Data mode command.
 * @param[in] address         Start address for digit writing.
 * @param[in] data            Pointer to data buffer.
 * @param[in] displaycommand  Display command for brightness/on/off.
 */
void TM1637_Write(uint8_t datacommand, uint8_t address, uint8_t *data, uint8_t displaycommand);

/**
 * @brief Converts seconds into MM:SS digit format for 4-digit display.
 *
 * @param[in]  values Time in seconds.
 * @param[out] digits 4-byte array to store digit values.
 */
void TM1637_Convert_To_Digits(uint32_t values, uint8_t digits[4]);

/**
 * @brief Updates display with values and enables/disables the dot/colon.
 *
 * @param[in] displayvalue Pointer to 4-byte digit array.
 * @param[in] status       true = show colon; false = hide colon.
 */
void TM1637_Update_Data_Dots(uint8_t *displayvalue, uint8_t status);

#ifdef __cplusplus
}
#endif

#endif /* TM1637_H_ */

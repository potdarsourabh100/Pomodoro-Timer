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
#define MAX_NO_OF_CHARACTERS                 6
#define NO_OF_DIGIT_CHARACTERS               2

/* Display register addresses */
#define DISPLAY_1_REGISTER_ADDRESS           0xC0
#define DISPLAY_2_REGISTER_ADDRESS           0xC1
#define DISPLAY_3_REGISTER_ADDRESS           0xC2
#define DISPLAY_4_REGISTER_ADDRESS           0xC3
#define DISPLAY_5_REGISTER_ADDRESS           0xC4
#define DISPLAY_6_REGISTER_ADDRESS           0xC5

/* Data Command & default register values */
#define DATA_COMMAND                         0x40

#define WRITE_DATA_TO_DISPLAY                0x00
#define READ_KEY_SCAN_DATA                   0x02

#define AUTOMATIC_ADDRESS_ADD                0x00
#define FIX_ADDRESS                          0x04

#define NORMAL_MODE                          0x00
#define TEST_MODE                            0x08

/* Display Command & default register values */
#define DISPLAY_COMMAND                      0x80

#define PULSE_WIDTH_SET_01_16                0x00
#define PULSE_WIDTH_SET_02_16                0x01
#define PULSE_WIDTH_SET_04_16                0x02
#define PULSE_WIDTH_SET_10_16                0x03
#define PULSE_WIDTH_SET_11_16                0x04
#define PULSE_WIDTH_SET_12_16                0x05
#define PULSE_WIDTH_SET_13_16                0x06
#define PULSE_WIDTH_SET_14_16                0x07

#define DISPLAY_ON                           0x08
#define DISPLAY_OFF                          0x00


void Delay_us(int time);
void TM1637_Start (void);
void TM1637_Stop (void);
void TM1637_WaitForAck (void);
void TM1637_WriteByte (uint8_t byte);
void TM1637_WriteDataCommand(uint8_t datacommand);
void TM1637_WriteData(uint8_t address, uint8_t *data);
void TM1637_WriteDisplayCommand(uint8_t displaycommand);
void TM1637_Write(uint8_t datacommand,uint8_t address,uint8_t *data,uint8_t displaycommand);
void TM1637_Convert_To_Digits(uint32_t values, uint8_t digits[4]);
void TM1637_Update_Data_Dots(uint8_t *displayvalue, uint8_t status);

#ifdef __cplusplus
}
#endif

#endif /* TM1637_H_ */

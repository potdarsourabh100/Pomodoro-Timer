/*
 * TM1637.h
 *
 *  Created on: Apr 18, 2025
 *      Author: potda
 */

#ifndef PLATFORM_TM1637_H_
#define PLATFORM_TM1637_H_

#include "Platform_Translate.h"

#define MAX_NO_OF_CHARACTERS                 6
#define NO_OF_DIGIT_CHARACTERS               2

/*Display register addresses*/
#define DISPLAY_1_REGISTER_ADDRESS           0xC0
#define DISPLAY_2_REGISTER_ADDRESS           0xC1
#define DISPLAY_3_REGISTER_ADDRESS           0xC2
#define DISPLAY_4_REGISTER_ADDRESS           0xC3
#define DISPLAY_5_REGISTER_ADDRESS           0xC4
#define DISPLAY_6_REGISTER_ADDRESS           0xC5

/*Data Command & default register values*/
#define DATA_COMMAND                         0x40

#define WRITE_DATA_TO_DISPLAY                0x00
#define READ_KEY_SCAN_DATA                   0x02

#define AUTOMATIC_ADDRESS_ADD                0x00
#define FIX_ADDRESS                          0x04

#define NORMAL_MODE                          0x00
#define TEST_MODE                            0x08

/*Display Command & default register values*/
#define DISPLAY_COMMAND                      0x80

#define PulSe_WIDTH_SET_01_16                0x00
#define PulSe_WIDTH_SET_02_16                0x01
#define PulSe_WIDTH_SET_04_16                0x02
#define PulSe_WIDTH_SET_10_16                0x03
#define PulSe_WIDTH_SET_11_16                0x04
#define PulSe_WIDTH_SET_12_16                0x05
#define PulSe_WIDTH_SET_13_16                0x06
#define PulSe_WIDTH_SET_14_16                0x07

#define DISPLAY_ON                           0x08
#define DISPLAY_OFF                          0x00


void TM1637_Start (void);
void TM1637_Stop (void);
void TM1637_WaitForAck (void);
void TM1637_WriteByte (uint8_t byte);
void TM1637_WriteDataCommand(uint8_t datacommand);
void TM1637_WriteData(uint8_t address, uint8_t *data);
void TM1637_WriteDisplayCommand(uint8_t displaycommand);

void TM1637_Write(uint8_t datacommand,uint8_t address,uint8_t *data,uint8_t displaycommand);
void TM1637_Toggle_Dots(uint8_t status);
void TM1637_Update_Current_Data(uint8_t *dataupdate);
void TM1637_Update_Data_Dots(uint8_t *displayvalue, uint8_t status);

#endif /* PLATFORM_TM1637_H_ */

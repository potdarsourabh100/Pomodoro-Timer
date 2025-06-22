/*
 *
 *
 *  Created on: Apr 18, 2025
 *      Author: potda
 */
/**
 * \file           Platform_Translate.h
 * \brief          Platform translation for application header file
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
 * Author:          Sourabh potdar
 * Version:         V1.0.0
 *                   1 Major version change with entire function/hardware/system change
 *                   0 Minor version change with few exsting function/hardware/system change
 *                   0 daily changes mark.value increment with day change
 */
#ifndef PLATFORM_PLATFORM_TRANSLATE_H_
#define PLATFORM_PLATFORM_TRANSLATE_H_

#include "main.h"

/**
 * @brief Sets the CLK (Clock) line high for TM1637 communication.
 *
 * @details This macro sets GPIO pin PB12 to high state to indicate a rising edge
 *          or high logic level on the clock line as required by the TM1637 protocol.
 */
#define CLK_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

/**
 * @brief Sets the CLK (Clock) line low for TM1637 communication.
 *
 * @details This macro sets GPIO pin PB12 to low state to indicate a falling edge
 *          or low logic level on the clock line.
 */
#define CLK_LOW()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

/**
 * @brief Sets the DATA line high for TM1637 communication.
 *
 * @details This macro sets GPIO pin PB13 to high state, representing a logic high
 *          signal on the data line for bit transmission.
 */
#define DATA_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)

/**
 * @brief Sets the DATA line low for TM1637 communication.
 *
 * @details This macro sets GPIO pin PB13 to low state, representing a logic low
 *          signal on the data line for bit transmission.
 */
#define DATA_LOW()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

#endif /* PLATFORM_PLATFORM_TRANSLATE_H_ */

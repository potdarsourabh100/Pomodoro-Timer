/**
 * \file           pomodorotimer.h
 * \brief          Pomodoro Timer Header file
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

#ifndef POMODOROTIMER_H_
#define POMODOROTIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif
/*****************************************************************************/
/* Include Files                                                             */
/*****************************************************************************/
#include "main.h"
#include "TM1637.h"

/*****************************************************************************/
/* Private Defines                                                           */
/*****************************************************************************/

/**
 * @brief Pomodoro session duration in seconds.
 *
 * @details Represents 25 minutes (25 * 60 = 1500 seconds).
 */
#define POMODOROMODE_TIME            (1500) /*25 minutes in seconds*/

/**
 * @brief Short break duration in seconds.
 *
 * @details Represents 5 minutes (5 * 60 = 300 seconds).
 */
#define SHORTBREAK_TIME              (300)  /*5 minutes in seconds*/

/**
 * @brief Long break duration in seconds.
 *
 * @details Represents 15 minutes (15 * 60 = 900 seconds).
 */
#define LONGBREAK_TIME               (900)  /*15 minutes in seconds*/

/**
 * @brief No of cycles to shift to Long Break.
 *
 * @details If we required to take 6 cycles i.e. 3 pomodoros & 2 Short Breaks,
 *          then Total no of cycles - 1 put 5 over here.
 */
#define NO_OF_CYCLES                  (5) /*3 Pomodoros & 2 Short Breaks*/

/*****************************************************************************/
/* Private Enums                                                             */
/*****************************************************************************/

/**
 * @brief Enum for Pomodoro timer modes.
 *
 * @details Used to switch between different Pomodoro states during operation.
 */
typedef enum
{
	PomodoroFunctions_PomodoroMode,   /**< Pomodoro work session */
	PomodoroFunctions_ShortBreak,     /**< Short break session */
	PomodoroFunctions_LongBreak,      /**< Long break session */
}PomodoroFunctions_e;

/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
// (Add comments here when variables are defined in this section)

/*****************************************************************************/
/* User Functions                                                            */
/*****************************************************************************/

/**
 * @brief Entry function for the user Pomodoro application.
 *
 * @details Initializes and continuously manages button input, time tracking,
 *          display updates, and mode transitions for the Pomodoro clock.
 *
 * @note Should be called once from `main()` or scheduler to start application.
 */
void userMain(void);


#ifdef __cplusplus
}
#endif

#endif /* POMODOROTIMER_H_ */

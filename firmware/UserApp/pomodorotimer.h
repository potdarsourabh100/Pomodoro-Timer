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
#define POMODOROMODE_TIME            (1500) /*25 minutes in seconds*/
#define SHORTBREAK_TIME              (300) /*5 minutes in seconds*/
#define LONGBREAK_TIME               (900) /*15 minutes in seconds*/
/*****************************************************************************/
/* Private Enums                                                             */
/*****************************************************************************/
typedef enum
{
	PomodoroFunctions_PomodoroMode,
	PomodoroFunctions_ShortBreak,
	PomodoroFunctions_LongBreak,
}PomodoroFunctions_e;
/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/


/*****************************************************************************/
/* User Functions                                                            */
/*****************************************************************************/
void userMain(void);

#ifdef __cplusplus
}
#endif

#endif /* POMODOROTIMER_H_ */

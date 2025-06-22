/**
 * \file            Version.h
 * \brief           Version header file
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
 *                   0 Minor version change with few existing function/hardware/system change
 *                   0 daily changes mark.value increment with day change
 */

#ifndef VERSION_H_
#define VERSION_H_

#define MAJOR           1
#define MINOR           0
#define INCREMENTAL     0

// To convert the parameter into string
#define _STRING(x)          #x
#define STRING(x)           _STRING(x)

#define VERSION_STRING      STRING(v.MAJOR.MINOR.INCREMENTAL)

/*
 * Update firmware version information here (not above) Latest information first.
 *
 *  Date          FirmWare  File Changed            File V/R    Programmer          Description
 * *-------------*---------*-----------------------*-----------*-------------------*---------------------------------------------------------------------------------------
 * 22-06-2025     1.0.0     All Files               1.0.0        Sourabh Potdar     🚀 Initial Release
																					- Core Pomodoro functionality (25/5/15 minute cycles)
																				    ⚠️ Warning/Notice
																					- Button-related activities are started.
																					- The pause function is yet to be added.
																					- Buzzer hardware not yet added.
																					💤 Power/Performance
																					- Although initial performance looks good
																					- Power-related activities are yet to be tested thoroughly.
 * 22-06-2025     1.0.1     pomodorotimer.c         1.0.1        Sourabh Potdar     🐞 Bug fix
																					- The timer was not performing correct mode in the proper order fixed
																					⚠️ Warning/Notice
																					- Button-related activities are started.
																					- The pause function is yet to be added.
																					- Buzzer hardware not yet added.
																					💤 Power/Performance
																					- Although the initial performance looks good
																					Power-related activities are yet to be tested thoroughly.
 *
*/

#endif /* VERSION_H_ */

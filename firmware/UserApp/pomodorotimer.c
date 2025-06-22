/**
 * \file           pomodorotimer.c
 * \brief          pomodoro timer source file
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
#include "../UserApp/pomodorotimer.h"
/*****************************************************************************/
/* Private Defines                                                           */
/*****************************************************************************/
#define DEBOUNCEDELAY        20      /* The De-bounce Time; increase it if the output still flicker */
/*****************************************************************************/
/* External Variables                                                        */
/*****************************************************************************/
extern TIM_HandleTypeDef htim3;
/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
volatile uintmax_t glbSecondCounter = 0;

volatile uintmax_t glbSysTicks = 0;

uintmax_t glbLastSecondsCount = 0;

uint8_t displayData[] = {0,0,0,0};

bool glbLastDotState = false;
bool glbTimerState = false;

PomodoroFunctions_e glbModeSelection = PomodoroFunctions_PomodoroMode;
uintmax_t glbCurrentModeTime = POMODOROMODE_TIME;

uint8_t glbPomodoroCycles = 0;
/*****************************************************************************/
/* User Function                                                             */
/*****************************************************************************/
void buttonControlDebounce(void)
{
	static uintmax_t glbLastDebounceTime = 0;  /* The Last Time The Output Pin Was Toggled */
	static uint8_t glbButtonState;            /* The Current Reading From The Input Pin */
	static uint8_t glbLastButtonState = 0;    /* The previous reading from The Input Pin */

	uint8_t tempButtonReading = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); /* read the state of the switch into a local variable */

    if(tempButtonReading != glbLastButtonState) /* If the switch changed, due to noise or pressing */
    {
        glbLastDebounceTime = glbSysTicks; /* reset the debouncing timer */
    }
    if((glbSysTicks - glbLastDebounceTime) > DEBOUNCEDELAY)
    {
        if(tempButtonReading != glbButtonState)
        {
            glbButtonState = tempButtonReading;
            if(glbButtonState == GPIO_PIN_RESET)
            {
            	if(glbTimerState == false)
            	{
            		/* Start counting seconds*/
                    glbSecondCounter = 0;

                    /*Reset Mode counter*/
                    glbModeSelection = PomodoroFunctions_PomodoroMode;

                    /* Reset Time selection*/
                    glbCurrentModeTime = POMODOROMODE_TIME;

                    /*Reset Pomodoro Cycles*/
                    glbPomodoroCycles = 0;

            		glbTimerState = true;
            		/* Start The timer */
            	    if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
            		{
            		  /* Starting Error */
            		  Error_Handler();
            		}
            	}
            	else if(glbTimerState == true)
				{
            		/* Start counting seconds*/
                    glbSecondCounter = 0;

                    /*Reset Mode counter*/
                    glbModeSelection = PomodoroFunctions_PomodoroMode;

                    /* Reset Time selection*/
                    glbCurrentModeTime = POMODOROMODE_TIME;

                    /*Reset Pomodoro Cycles*/
                    glbPomodoroCycles = 0;

            		glbTimerState = false;
                	/* Stop The timer */
                   if (HAL_TIM_Base_Stop_IT(&htim3) != HAL_OK)
                   {
                	   /* Stopping Error */
                	   Error_Handler();
                   }

				}
            }
        }
    }
    glbLastButtonState = tempButtonReading;
}

void buttonFunctionDebounce(void)
{
	static uintmax_t glbLastDebounceTime = 0;  /* The Last Time The Output Pin Was Toggled */
	static uint8_t glbButtonState;            /* The Current Reading From The Input Pin */
	static uint8_t glbLastButtonState = 0;    /* The previous reading from The Input Pin */

	uint8_t tempButtonReading = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1); /* read the state of the switch into a local variable */

    if(tempButtonReading != glbLastButtonState) /* If the switch changed, due to noise or pressing */
    {
        glbLastDebounceTime = glbSysTicks; /* reset the debouncing timer */
    }
    if((glbSysTicks - glbLastDebounceTime) > DEBOUNCEDELAY)
    {
        if(tempButtonReading != glbButtonState)
        {
            glbButtonState = tempButtonReading;
            if(glbButtonState == GPIO_PIN_RESET)
            {
            	glbSecondCounter = 0;
            	if(glbModeSelection == PomodoroFunctions_PomodoroMode)
            	{
            		glbModeSelection = PomodoroFunctions_ShortBreak;
            		glbCurrentModeTime = SHORTBREAK_TIME;
            		glbPomodoroCycles++;
            	}
            	else if(glbModeSelection == PomodoroFunctions_ShortBreak)
            	{
            		glbPomodoroCycles++;
            		if(glbPomodoroCycles == 8)
            		{
            			glbModeSelection = PomodoroFunctions_LongBreak;
            			glbPomodoroCycles = 0;
            		}
            		else
            		{
            			glbModeSelection = PomodoroFunctions_PomodoroMode;
            		}

            		glbCurrentModeTime = LONGBREAK_TIME;

            	}
            	else if(glbModeSelection == PomodoroFunctions_LongBreak)
            	{
            		glbModeSelection = PomodoroFunctions_PomodoroMode;
            		glbCurrentModeTime = POMODOROMODE_TIME;

            	}

            }
        }
    }
    glbLastButtonState = tempButtonReading;
}

void updateDisplay(void)
{
	if(glbLastSecondsCount != glbSecondCounter)
	{
		if(glbSecondCounter == glbCurrentModeTime)
		{
        	glbSecondCounter = 0;
        	if(glbModeSelection == PomodoroFunctions_PomodoroMode)
        	{
        		glbModeSelection = PomodoroFunctions_ShortBreak;
        		glbCurrentModeTime = SHORTBREAK_TIME;
        		glbPomodoroCycles++;
        	}
        	else if(glbModeSelection == PomodoroFunctions_ShortBreak)
        	{
        		glbPomodoroCycles++;
        		if(glbPomodoroCycles == 8)
        		{
        			glbModeSelection = PomodoroFunctions_LongBreak;
        			glbPomodoroCycles = 0;
        		}
        		else
        		{
        			glbModeSelection = PomodoroFunctions_PomodoroMode;
        		}

        		glbCurrentModeTime = LONGBREAK_TIME;

        	}
        	else if(glbModeSelection == PomodoroFunctions_LongBreak)
        	{
        		glbModeSelection = PomodoroFunctions_PomodoroMode;
        		glbCurrentModeTime = POMODOROMODE_TIME;

        	}

		}

			glbLastSecondsCount = glbSecondCounter;
			TM1637_Convert_To_Digits(glbSecondCounter,&displayData[0]);

			if(glbLastDotState == true)
			{
				glbLastDotState = false;
				TM1637_Update_Data_Dots(displayData,true);
			}
			else if(glbLastDotState == false)
			{
				glbLastDotState = true;
				TM1637_Update_Data_Dots(displayData,false);
			}

	}

}
/*****************************************************************************/
/* User Main Function                                                        */
/*****************************************************************************/
void userMain(void)
{
	/* Initialize data on display */
    TM1637_Update_Data_Dots(displayData,true);

	while(1)
	{
		buttonControlDebounce();
		buttonFunctionDebounce();
		updateDisplay();
	}
}
/*************************************END*************************************/

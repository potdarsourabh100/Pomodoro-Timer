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
 * Version:         V1.2.2
 * Fixes:           22-06-2025 The timer was not performing correct mode in the proper order fixed.
 * 					14-07-2025 The given platform dependency are removed & buzzer functionalities added.
 * 					16-07-2025 The values for cycles changed to 5 correct Logic implemented.
 */
/*****************************************************************************/
/* Include Files                                                             */
/*****************************************************************************/
#include "../UserApp/pomodorotimer.h"
/*****************************************************************************/
/* Private Defines                                                           */
/*****************************************************************************/
#define DEBOUNCEDELAY        20      /* The De-bounce Time; increase it if the output still flicker */
/** Minimum time in milliseconds to consider a button press valid and ignore bouncing **/

/*****************************************************************************/
/* External Variables                                                        */
/*****************************************************************************/
extern TIM_HandleTypeDef htim3; /** Timer handler used for counting seconds **/

/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
volatile uintmax_t glbSecondCounter = 0; /** Used to count total seconds since the timer started **/

volatile uintmax_t glbSysTicks = 0; /** System tick value that increments periodically **/

uintmax_t glbLastSecondsCount = 0; /** Stores the last updated value of glbSecondCounter **/

uint8_t displayData[] = {0,0,0,0}; /** 4-digit array used for display driver **/

bool glbLastDotState = false; /** Tracks the state of colon/dot between digits on the display **/
bool glbTimerState = false; /** Indicates whether the timer is currently running or stopped **/

PomodoroFunctions_e glbModeSelection = PomodoroFunctions_PomodoroMode; /** Current mode of Pomodoro session **/

uintmax_t glbCurrentModeTime = POMODOROMODE_TIME; /** Duration of the current mode **/

uint8_t glbPomodoroCycles = 0; /** Counter for the number of Pomodoro sessions completed **/

/*****************************************************************************/
/* User Function                                                             */
/*****************************************************************************/
/*****************************************************************************
 * @brief Handles the control button with software debounce logic.
 *
 * @details This function checks for a stable button press on GPIO_PIN_0.
 *          When pressed, it toggles the timer state between start and stop.
 *          It resets the Pomodoro mode, timer counter, and cycles when toggled.
 *          It also starts or stops the TIM3 interrupt accordingly.
 *
 * @param   None
 *
 * @return  None
 *
 * @retval  None
 *
 * @note The function must be called periodically inside the main loop.
 *       It uses `glbSysTicks` as a system time base for debounce delay.
 *
 * @warning Assumes HAL_TIM_Base_Start_IT and HAL_TIM_Base_Stop_IT will
 *          handle timer errors through Error_Handler().
 *
 * @see HAL_GPIO_ReadPin(), HAL_TIM_Base_Start_IT(), HAL_TIM_Base_Stop_IT()
 *****************************************************************************/
void buttonControlDebounce(void)
{
	static uintmax_t glbLastDebounceTime = 0;  /* The Last Time The Output Pin Was Toggled */
	static uint8_t glbButtonState;            /* The Current Reading From The Input Pin */
	static uint8_t glbLastButtonState = 0;    /* The previous reading from The Input Pin */

	uint8_t tempButtonReading = CONTROLBUTTON_READ(); /* read the state of the switch into a local variable */
	/** GPIO_PIN_0 is the control button used to start/stop the Pomodoro timer **/

    if(tempButtonReading != glbLastButtonState) /* If the switch changed, due to noise or pressing */
    {
        glbLastDebounceTime = glbSysTicks; /* reset the debouncing timer */
    }

    if((glbSysTicks - glbLastDebounceTime) > DEBOUNCEDELAY)
    {
        if(tempButtonReading != glbButtonState)
        {
            glbButtonState = tempButtonReading;
            if(glbButtonState == GPIO_PIN_RESET) /** Button is pressed **/
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
            	    if (TIMER_ON() != HAL_OK)
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
                   if (TIMER_OFF() != HAL_OK)
                   {
                	   /* Stopping Error */
                	   Error_Handler();
                   }
				}
            }
        }
    }
    glbLastButtonState = tempButtonReading; /** Store current reading for comparison in next cycle **/
}
/*****************************************************************************
 * @brief Handles the function button to switch Pomodoro modes.
 *
 * @details This function reads GPIO_PIN_1 and applies debounce logic. When the
 *          button is pressed, it transitions between Pomodoro, Short Break, and
 *          Long Break modes. It also resets the Pomodoro second counter and
 *          updates the mode time and cycle count.
 *
 * @param   None
 *
 * @return  None
 *
 * @retval  None
 *
 * @note Call this periodically in the main loop. The function uses a debounce
 *       timer based on `glbSysTicks`.
 *
 * @warning Cycle count wraps after 4 Pomodoro sessions(4 Pomodoros & 4 Short Breaks)
 *          and switches to a Long Break automatically.
 *
 * @see HAL_GPIO_ReadPin()
 *****************************************************************************/
void buttonFunctionDebounce(void)
{
	static uintmax_t glbLastDebounceTime = 0;  /* The Last Time The Output Pin Was Toggled */
	static uint8_t glbButtonState;            /* The Current Reading From The Input Pin */
	static uint8_t glbLastButtonState = 0;    /* The previous reading from The Input Pin */

	uint8_t tempButtonReading = FUNCTIONBUTTON_READ(); /* read the state of the switch into a local variable */
	/** GPIO_PIN_1 is the function button used to switch between Pomodoro modes **/

    if(tempButtonReading != glbLastButtonState) /* If the switch changed, due to noise or pressing */
    {
        glbLastDebounceTime = glbSysTicks; /* reset the debouncing timer */
    }

    if((glbSysTicks - glbLastDebounceTime) > DEBOUNCEDELAY)
    {
        if(tempButtonReading != glbButtonState)
        {
            glbButtonState = tempButtonReading;
            if(glbButtonState == GPIO_PIN_RESET) /** Button is pressed **/
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
            		if(glbPomodoroCycles >= NO_OF_CYCLES)
            		{
            			glbModeSelection = PomodoroFunctions_LongBreak;
            			glbCurrentModeTime = LONGBREAK_TIME;
            			glbPomodoroCycles = 0;
            		}
            		else
            		{
            			glbModeSelection = PomodoroFunctions_PomodoroMode;
            			glbCurrentModeTime = POMODOROMODE_TIME;
            		}
            	}
            	else if(glbModeSelection == PomodoroFunctions_LongBreak)
            	{
            		glbModeSelection = PomodoroFunctions_PomodoroMode;
            		glbCurrentModeTime = POMODOROMODE_TIME;
            	}
            }
        }
    }
    glbLastButtonState = tempButtonReading; /** Store current reading for comparison in next cycle **/
}
/*****************************************************************************
 * @brief Updates the display with the current Pomodoro timer value.
 *
 * @details Compares `glbSecondCounter` with the previous value. If changed,
 *          the function converts the new value to digits for display. It also
 *          toggles the dot/colon visual on the display and manages transitions
 *          between Pomodoro, Short Break, and Long Break modes based on elapsed time.
 *
 * @param   None
 *
 * @return  None
 *
 * @retval  None
 *
 * @note TM1637_Convert_To_Digits() converts the seconds into 4-digit format.
 *       TM1637_Update_Data_Dots() toggles the colon/dot every second for blinking.
 *
 * @warning Be sure that the display is initialized before calling this.
 *
 * @see TM1637_Convert_To_Digits(), TM1637_Update_Data_Dots()
 *****************************************************************************/
void updateDisplay(void)
{
	if(glbLastSecondsCount != glbSecondCounter)
	{
		/** Time has changed, so update the display **/
		if(glbSecondCounter == glbCurrentModeTime)
		{
        	glbSecondCounter = 0;
        	if(glbModeSelection == PomodoroFunctions_PomodoroMode)
        	{
        		glbModeSelection = PomodoroFunctions_ShortBreak;
        		glbCurrentModeTime = SHORTBREAK_TIME;
        		glbPomodoroCycles++;
        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        	}
        	else if(glbModeSelection == PomodoroFunctions_ShortBreak)
        	{
        		glbPomodoroCycles++;
        		if(glbPomodoroCycles >= NO_OF_CYCLES)
        		{
        			glbModeSelection = PomodoroFunctions_LongBreak;
        			glbCurrentModeTime = LONGBREAK_TIME;
        			glbPomodoroCycles = 0;
        		}
        		else
        		{
        			glbModeSelection = PomodoroFunctions_PomodoroMode;
        			glbCurrentModeTime = POMODOROMODE_TIME;
        		}
        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        		APP_DELAY(50);
        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        	}
        	else if(glbModeSelection == PomodoroFunctions_LongBreak)
        	{
        		glbModeSelection = PomodoroFunctions_PomodoroMode;
        		glbCurrentModeTime = POMODOROMODE_TIME;

        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        		APP_DELAY(50);
        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        		APP_DELAY(50);
        		BUZZER_ON();
        		APP_DELAY(50);
        		BUZZER_OFF();
        	}
		}

		glbLastSecondsCount = glbSecondCounter; /** Update the stored count for future comparison **/
		TM1637_Convert_To_Digits(glbSecondCounter,&displayData[0]); /** Convert seconds to digit format **/

		if(glbLastDotState == true)
		{
			glbLastDotState = false;
			TM1637_Update_Data_Dots(displayData,true); /** Toggle dot ON **/
		}
		else if(glbLastDotState == false)
		{
			glbLastDotState = true;
			TM1637_Update_Data_Dots(displayData,false); /** Toggle dot OFF **/
		}
	}
}

/*****************************************************************************/
/* User Main Function                                                        */
/*****************************************************************************/
/*****************************************************************************
 * @brief Main user function to handle Pomodoro control logic.
 *
 * @details This is the main loop function which initializes the display state
 *          and continuously checks the control and function button inputs.
 *          It updates the timer display accordingly.
 *
 * @param   None
 *
 * @return  None
 *
 * @retval  None
 *
 * @note Should be called after system and peripheral initialization.
 *
 * @warning This function runs in an infinite loop. Make sure all critical
 *          initialization is done before calling it.
 *
 * @see buttonControlDebounce(), buttonFunctionDebounce(), updateDisplay()
 *****************************************************************************/
void userMain(void)
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

	/* Initialize data on display */
    TM1637_Update_Data_Dots(displayData,false); /** Set initial colon/dot state on display **/

	while(1)
	{
		buttonControlDebounce(); /** Handle control button with debounce **/
		buttonFunctionDebounce(); /** Handle mode change button with debounce **/
		updateDisplay(); /** Refresh display based on timer count **/
	}
}
/*************************************END*************************************/

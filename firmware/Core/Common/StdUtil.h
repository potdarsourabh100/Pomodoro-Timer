/**
 * \file           StdUtils.h
 * \brief          Standard utility header file
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

#ifndef STDUTIL_H_
#define STDUTIL_H_

/*****************************************************************************/
/* Include Files                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
/*****************************************************************************/
/* Miscellaneous Macro Deceleration                                          */
/*****************************************************************************/
#define  FALSE                   0
#define  TRUE                    1

#define  YES                     1
#define  NO                      0

#define  READ                    0
#define  WRITE                   1

#define  INACTIVE                0
#define  ACTIVE                  1

#define  INVALID                 0
#define  VALID                   1

#define  ON                      1
#define  OFF                     0

#define  SET                     1
#define  CLEAR                   0

#define  HIGH                    1
#define  LOW                     0

#define  OK                      1
#define  NOK                     0

#define  ZERO                    0x00u
#define  NULL_CHAR               0x00u

#define  FAILED                  0x00u
#define  SUCCESSFUL              0x01u
#define  BUSY                    0x02u

#define stdutil_GetBitMask(bit)          (1<<(bit))
#define stdutil_BitSet(x,bit)            ((x) |=  util_GetBitMask(bit))
#define stdutil_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
#define stdutil_BitToggle(x,bit)         ((x) ^=  util_GetBitMask(bit))
#define stdutil_UpdateBit(x,bit,val)     ((val)? util_BitSet(x,bit): util_BitClear(x,bit))

#define stdutil_GetBitStatus(x,bit)      (((x)&(util_GetBitMask(bit)))!=0u)
#define stdutil_IsBitSet(x,bit)          (((x)&(util_GetBitMask(bit)))!=0u)
#define stdutil_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)

#define stdutil_AreAllBitsSet(x,BitMask) (((x)&(BitMask))==BitMask)
#define stdutil_AreAnyBitsSet(x,BitMask) (((x)&(BitMask))!=0x00u)

#define stdutil_ExtractNibble0to4(x)      (uint8_t) ((x) & 0x0Fu)
#define stdutil_ExtractNibble4to8(x)      (uint8_t) (((x)>>4)  & 0x0Fu)
#define stdutil_ExtractNibble8to12(x)     (uint8_t) (((x)>>8)  & 0x0Fu)
#define stdutil_ExtractNibble12to16(x)    (uint8_t) (((x)>>12) & 0x0Fu)

#define stdutil_ExtractByte0to8(x)        (uint8_t) ((x) & 0xFFu)
#define stdutil_ExtractByte8to16(x)       (uint8_t) (((x)>>8) & 0xFFu)
#define stdutil_ExtractByte16to24(x)      (uint8_t) (((x)>>16) & 0xFFu)
#define stdutil_ExtractByte24to32(x)      (uint8_t) (((x)>>24) & 0xFFu)

#define stdutil_Ascii2Hex(Asc)            (((Asc)>0x39) ? ((Asc + 10) - 0x41): ((Asc) - 0x30))
#define stdutil_Hex2Ascii(Hex)            (((Hex)>0x09) ? ((Hex - 10) + 0x41): ((Hex) + 0x30))

#define DEBUG_PRINTF_BUFFER_SIZE          128

__attribute__((weak)) void stdutil_putchar(char c)
{
    /*For example: USART1->DR = c;
     Or implement your HAL_UART_Transmit(&huart, &c, 1, timeout);*/
}

void debugprintf(const char *format, ...)
{
    char buffer[DEBUG_PRINTF_BUFFER_SIZE];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    while(*p != '\0')
    {
    	stdutil_putchar(*p++);
    }
}
/***********************************END****************************************/


#endif /* STDUTIL_H_ */

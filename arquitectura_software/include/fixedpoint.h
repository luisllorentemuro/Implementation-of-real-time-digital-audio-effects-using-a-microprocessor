/* fixedpoint.h                                                              */

/* Copyright (c) 2010 Tomasz Hadula                                          */

/* Permission is hereby granted, free of charge, to any person               */
/* obtaining a copy of this software and associated documentation            */
/* files (the "Software"), to deal in the Software without                   */
/* restriction, including without limitation the rights to use,              */
/* copy, modify, merge, publish, distribute, sublicense, and/or sell         */
/* copies of the Software, and to permit persons to whom the                 */
/* Software is furnished to do so, subject to the following                  */
/* conditions:                                                               */

/* The above copyright notice and this permission notice shall be            */
/* included in all copies or substantial portions of the Software.           */

/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES           */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                  */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT               */
/* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,              */
/* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING              */
/* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR             */
/* OTHER DEALINGS IN THE SOFTWARE.                                           */

#ifndef	_FIXEDPOINT_INT_H_
#define	_FIXEDPOINT_INT_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//#include <unistd.h>

/*@{*/

/**
 * Some basic types
 */

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef signed long long int64;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;

/*@}*/

/**
 * This macro simply calculates a static array size
 */

#define	ARRAYSIZE(x)	(sizeof(x) / sizeof(x[ 0 ]))

/*@{*/

/**
 * Those macros below help calculate size expressed in KB, MB
 * and GB
 */

#define KILOBYTES(n) ((n) * 1024)
#define MEGABYTES(n) ((n) * 1024 * 1024)
#define GIGABYTES(n) ((n) * 1024 * 1024 * 1024)

/*@}*/

/**
 * This method calculates a binary logarithm for a 16-bit number + 1.
 * The result for 0 is 0.
 */
uint8 log2plus1 (uint16 x);

/**
 * This method calculates a binary logarithm for a 16-bit number.
 * The result for 0 is 0.
 */
//uint8 log2 (uint16 x);

/**
 * This method calculates de sign for a 16-bit number.
 */
int16_t sign (int16_t input);

/**
 * This method reverses bit order in an octet.
 */
uint8 reverseByte (uint8 byte);

/**
 * This method calculates a number of positions a parameter has to be
 * shifted left to the most significant non-sign bit of its mantissa
 * (a number of redundant sign bits). 31 if the parameter is 0.
 */
int norm (int a);

/**
 * This function calculates a scaled sine of a number in 1.15 format.
 *
 * @param[in]  uint16  a number to calculate a sine of
 * @return     uint16  a sine of a 1.15 number (-1 <= x < 1)
 *                     multiplied by pi in 1.15 representation
 */
uint16 sinpi (uint16 x);

/**
 * This function calculates a scaled cosine of a number in 1.15 format.
 *
 * @param[in]  uint16  a number to calculate a cosine of
 * @return     uint16  a cosine of a 1.15 number (-1 <= x < 1)
 *                     multiplied by pi in 1.15 representation
 */
uint16 cospi (uint16 x);

/**
 * This function calculates a scaled arctangent.
 *
 * @param[in]  uint32  a number to calculate an arctangent of
 *                     in 17.15 form
 * @return     uint32  arctangent divided by pi in 1.15 representation
 *                     (-1/2 <= y <= 1/2; 0xC000 <= Y <= 0xFFFF OR
 *                     0 <= Y <= 0x4000)
 */
uint16 atanpi (uint32 x);

/**
 * This function calculates a square root.
 *
 * @param[in]  uint32  a number to calculate a square root of
 *                     in 17.15 form
 * @return     uint32  square root in 17.15 representation
 */
uint32 squareroot (uint32 x);

/**
 * This function calculates a natural logarithm.
 *
 * @param[in]  uint32  a number to calculate a square root of
 *                     in 17.15 form
 * @return     uint32  natural logarithm in 17.15 representation
 */
uint32 logn (uint32 x);

/**
 * This function calculates a exponent function.
 *
 * @param[in]  uint32  a number to calculate a square root of
 *                     in 17.15 form
 * @return     uint32  exponent (exp(x)) in 17.15 representation
 */
uint32 exponent (uint32 x);

/**
 * This method initializes lookup tables.
 */
void fixedpoint_init(void);

#endif	/* _FIXEDPOINT_INT_H_ */

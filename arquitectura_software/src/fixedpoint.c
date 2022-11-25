/* fixedpoint.c                                                              */

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

#include "fixedpoint.h"

/**
 * ln(2) in 1.15 format
 */

#define	LN_2_1F15	0x000058B9

/**
 * class FixedPoint
 */

uint16 exptable[] =
{
		1,     2,     4,     8,    16,    32,    64,   128,
	  256,   512,  1024,  2048,  4096,  8192, 16384, 32768
};

int16_t sign (int16_t input)
{
    if (input > 0) return 32767;
    if (input < 0) return -32768;
    return 0;
}

uint8 logtable[ KILOBYTES(64) ] = { 0 };

uint8 reversedbytes[] =
{
	0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
	0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
	0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
	0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
	0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4,
	0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
	0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC,
	0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
	0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
	0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
	0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA,
	0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
	0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6,
	0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
	0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
	0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
	0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
	0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
	0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9,
	0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
	0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
	0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
	0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED,
	0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
	0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3,
	0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
	0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
	0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
	0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7,
	0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
	0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF,
	0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

uint16 sintable[ KILOBYTES(64) ] = { 0 };

/* sine coefficients in 4.12 fixed point format */

int sincoefftable[] =
{
	0x00003240, 0x00000053, 0xFFFFAACC, 0x000008B7,
	0x00001CCE
};

/* arctangent coefficients in 1.15 fixed point format */

int atancoefftable[] =
{
	0x000028BD, 0x0000006D, 0xFFFFEF3E, 0x000008C6,
	0xFFFFFED4
};

/* square root coefficients in 17.15 fixed point format */

int sqrtcoefftable[] =
{
	0x00001A91, 0x0000BA3A, 0xFFFF53DA, 0x00008DAC,
	0xFFFFBB54, 0x00000E5A
};

/* square root of 2 powered to (index - 15) in 17.15 format */

int sqrt2powers[] =
{
	0x000000B5,	0x00000100, 0x0000016A, 0x00000200,
	0x000002D4,	0x00000400, 0x000005A8, 0x00000800,
	0x00000B50,	0x00001000, 0x000016A1, 0x00002000,
	0x00002D41,	0x00004000, 0x00005A82, 0x00008000,
	0x0000B505,	0x00010000, 0x00016A0A, 0x00020000,
	0x0002D414,	0x00040000, 0x0005A828, 0x00080000,
	0x000B504F,	0x00100000, 0x0016A09E, 0x00200000,
	0x002D413D,	0x00400000, 0x005A827A, 0x00800000
};

/* natural logarithm coefficients in 17.15 fixed point format */

int logncoefftable[] =
{
	0x00007FE3, 0xFFFFC149, 0x00002491, 0xFFFFEEF8,
	0x00000404
};

/* integer and fraction parts of exponent values */

int integerexptable[] =
{
	0x00000001, 0x00000002, 0x00000007, 0x00000014,
	0x00000036, 0x00000094, 0x00000193, 0x00000448,
	0x00000BA4,	0x00001FA7, 0x0000560A, 0x0000E9E2

};

int fractionexptable[] =
{
	0x00000000, 0x00005BF1, 0x000031CD, 0x00000AF3,
	0x00004C90, 0x000034E2, 0x000036E3, 0x0000510B,
	0x00007A9F, 0x00000ABE, 0x00003B9F, 0x00001224

};

/* exponent coefficients in 17.15 fixed point format */

int expcoefftable[] =
{
	0x00008000, 0x00008000, 0x00004000, 0x00001555,
	0x00000555,	0x00000111, 0x0000002E, 0x00000007,
	0x00000001
};

void fixedpoint_init()
{
	register unsigned int   i, j, index;
	register int            x, result;

	static int              initialized = 0;

	if (initialized)
		return;

	// build log lookup table

	index = 0;
	for (i = 0; i < ARRAYSIZE (logtable); i++)
	{
		for (; index < ARRAYSIZE (exptable); index++)
			if (i < exptable [ index ])
				break;
		logtable[ (uint16) i ] = index;
	}

	for (i = 0; i < ARRAYSIZE (sintable) / 4; i++)
	{
		/**
		 * sin (x) = 3.140625 * x + 0.02026367 * x ^ 2
		 *         - 5.325196 * x ^ 3 + 0.5446778 * x ^ 4
		 *         + 1.800293 * x ^ 5
		 */

		x = ((i * i) >> 15);
		result = sincoefftable[ 0 ] * i;
		for (j = 1; j < ARRAYSIZE (sincoefftable); j++)
		{
			result += x * sincoefftable[ j ];
			x = ((x * i) >> 15);
		}
		result >>= 12;
		if (result > 0x7FFF)
			result = 0x7FFF;
		if (i > 0 && result < sintable[ i - 1 ])
			result = sintable[ i - 1 ];

		sintable[ (uint16) i ] = (uint16) result;
	}
	sintable[ (uint16) i++ ] = (uint16) 0x7FFF;
	for (; i < ARRAYSIZE (sintable) / 2; i++)
		sintable[ (uint16) i ] =
			sintable[ (uint16) (ARRAYSIZE (sintable) / 2 - i) ];
	sintable[ (uint16) i++ ] = (uint16) 0;
	for (; i < ARRAYSIZE (sintable); i++)
		sintable[ (uint16) i ] =
			(uint16) ((int16) -sintable[ (uint16) (i - ARRAYSIZE (sintable) / 2) ]);

	++initialized;     /* done */
}

uint8 log2plus1 (uint16 x)
{
	return logtable[ x ];
}

#if 0
uint8 log2 (uint16 x)
{
	return logtable[ x >> 1 ];
}
#endif

uint8 reverseByte (uint8 byte)
{
	return reversedbytes[ byte ];
}

int norm (int a)
{
	register int   n;

	if (a < 0)
		a = -a;
	n = log2plus1 ((uint16) (a >> 16));
	if (n > 0)
		return 15 - n;
	return 31 - log2plus1 ((uint16) (a & 0xFFFF));
}

uint16 sinpi (uint16 x)
{
	return sintable[ x ];
}

uint16 cospi (uint16 x)
{
	return sintable[ (uint16) (x + 0x4000) ];
}

uint16 atanpi (uint32 x)
{
	register unsigned int   i;
	register int            y, z, hi, result;

	if (!x)
		return 0;

	y = (int) ((x > 0x7FFFFFFF) ? (-x) : x);	/* absolute value */
	if (y == 0x8000)
		result = 0x2000;	/* 0.25 */
	else
	{
		/* |x| > 1 => arctan (x) = 0.5 - arctan (1/x) */
		hi = (y & 0xFFFF8000);
		if (hi)
			y = ((0x7FFFFFFF / y) >> 1);

		/**
		 * atan (x) = 0.318253 * x + 0.003314 * x ^ 2 +
		 *          - 0.130908 * x ^ 3 + 0.068542 * x ^ 4
		 *          - 0.009159 * x ^ 5
		 */
		z = ((y * y) >> 15);
		result = atancoefftable[ 0 ] * y;
		for (i = 1; i < ARRAYSIZE (atancoefftable); i++)
		{
			result += z * atancoefftable[ i ];
			z = ((z * y) >> 15);
		}
		result >>= 15;	/* now in 1.15 format */
		if (hi)
			result = 0x4000 - result;
	}
	if (x > 0x7FFFFFFF)
		result = -result;
	return (uint16) result;
}

uint32 squareroot (uint32 x)
{
	register unsigned int   i, exponent;
	register int            result, y, z;

	if (!x)
		return 0;
	if (x > 0x7FFFFFFF)
		return 0;	/* negative value */

	exponent = (unsigned int) norm ((int) x);
	y = ((x << exponent) >> 16);

	/**
	 * sqrt(x) = 0.2075806 + 1.454895 * x - 1.34491 * x^2 + 1.106812 * x^3
	 *         - 0.536499 * x^4 + 0.1121216 * x^5
	 */
	z = y;
	result = 0;
	for (i = 1; i < ARRAYSIZE (sqrtcoefftable); i++)
	{
		result += z * sqrtcoefftable[ i ];
		z = ((z * y) >> 15);
	}
	result >>= 15;
	result += sqrtcoefftable[ 0 ];

	if (exponent != 16)
		result = ((result * sqrt2powers[ 31 - exponent ]) >> 15);

	return (uint32) result;
}

uint32 logn (uint32 x)
{
	register unsigned int   i, exponent;
	register int            result, y, z;

	if (!x)
		return 0x80000000;
	if (x > 0x7FFFFFFF)
		return 0x80000000;	/* negative value */

	exponent = (unsigned int) norm ((int) x);
	y = ((x << exponent) >> 15) - 0x8000;

	/**
	 * ln(x) = 0.9991150 * (x -1) - 0.4899597 * (x -1) ^ 2
	 *       + 0.2856751 * (x -1) ^ 3 - 0.1330566 * (x -1) ^ 4
	 *       + 0.03137207 * (x -1) ^ 5
	 */
	z = ((y * y) >> 15);
	result = logncoefftable[ 0 ] * y;
	for (i = 1; i < ARRAYSIZE (logncoefftable); i++)
	{
		result += z * logncoefftable[ i ];
		z = ((z * y) >> 15);
	}
	result >>= 15;
	if (exponent != 15)
		result += LN_2_1F15 * (15 - exponent);

	return (uint32) result;
}

uint32 exponent (uint32 x)
{
	register unsigned int   i;
	register int            y, z, result, intx, fractx, scaleint, scalefract;

	if (!x)
		return 0x8000;
	y = (int) ((x > 0x7FFFFFFF) ? (-x) : x);

	intx = (y >> 15);
	fractx = (y & 0x7FFF);
	if (fractx >= 0x4000)
	{
		/* Taylor series converges quickly only when | fractx | < 0.5 */
		fractx -= 0x8000;
		++intx;
	}
	if (intx >= (int) ARRAYSIZE (integerexptable))
		return 0x7FFFFFFF;

	scaleint = integerexptable[ intx ];
	scalefract = fractionexptable[ intx ];

	/**
	 * Taylor's series:
	 *
	 * exp(x) = 1 + x + x ^ 2 / 2 + x ^ 3 / 3! + x ^ 4 / 4!
	 *        + x ^ 5 / 5! + x ^ 6 / 6! + x ^ 7 / 7! + x ^ 8 / 8!
	 */
	z = fractx;
	result = 0;
	for (i = 1; i < ARRAYSIZE (expcoefftable); i++)
	{
		result += z * expcoefftable[ i ];
		z = ((z * fractx) >> 15);
	}
	result >>= 15;
	result += expcoefftable[ 0 ];

	z = result;
	result = ((z * scalefract) >> 15) + z * scaleint;

	if (x > 0x7FFFFFFF)
		result = ((0x7FFFFFFF / result) >> 1);	/* negative value */

	return (uint32) result;
}

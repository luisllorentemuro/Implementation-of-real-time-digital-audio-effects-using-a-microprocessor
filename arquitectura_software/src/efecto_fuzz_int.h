/** \file efecto_fuzz_int.h
* A brief file description.
* Created on:    2022/07/13
* Last modified: 2022/07/13 18:38:53
*/

#ifndef _EFECTO_FUZZ_INT_H_
#define _EFECTO_FUZZ_INT_H_

#include <stdint.h>
#include <math.h>
#include "fixedpoint.h"

efecto_t * efecto_fuzz_create(void);
void efecto_fuzz_update(efecto_t * efecto, efecto_fuzzparams_t * params);
int16_t efecto_fuzz_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_FUZZ_INT_H_ */ 

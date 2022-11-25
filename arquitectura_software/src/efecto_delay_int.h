/** \file efecto_delay_int.h
* A brief file description.
* Created on:    2022/07/13
* Last modified: 2022/07/13 18:38:53
*/

#ifndef _EFECTO_DELAY_INT_H_
#define _EFECTO_DELAY_INT_H_

#include <stdint.h>

efecto_t * efecto_delay_create(void);
void efecto_delay_update(efecto_t * efecto, efecto_delayparams_t * params);
int16_t efecto_delay_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_DELAY_INT_H_ */ 

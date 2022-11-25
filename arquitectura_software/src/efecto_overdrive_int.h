/** \file efecto_overdrive_int.h
* A brief file description.
* Created on:    2022/07/13
* Last modified: 2022/07/13 18:38:53
*/

#ifndef _EFECTO_OVERDRIVE_INT_H_
#define _EFECTO_OVERDRIVE_INT_H_

#include <stdint.h>
#include <math.h>


efecto_t * efecto_overdrive_create(void);

int16_t efecto_overdrive_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_OVERDRIVE_INT_H_ */ 

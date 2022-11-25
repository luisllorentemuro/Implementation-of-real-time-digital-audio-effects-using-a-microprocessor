/** \file efecto_distortion_int.h
* A brief file description.
* Created on:    2022/07/13
* Last modified: 2022/07/13 18:38:53
*/

#ifndef _EFECTO_DISTORTION_INT_H_
#define _EFECTO_DISTORTION_INT_H_

#include <stdint.h>
#include <math.h>
#include "fixedpoint.h"

efecto_t * efecto_distortion_create(void);
void efecto_distortion_update(efecto_t * efecto, efecto_distortionparams_t * params);
int16_t efecto_distortion_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_DISTORTION_INT_H_ */ 

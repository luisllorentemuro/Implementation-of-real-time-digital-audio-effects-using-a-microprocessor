/** \file efecto_mute.h
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/13 18:15:31
*/

#ifndef _EFECTO_MUTE_INT_H_
#define _EFECTO_MUTE_INT_H_

#include <stdint.h>
#include "efectos.h"

efecto_t * efecto_mute_create(void);

int16_t efecto_mute_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_MUTE_INT_H_ */ 

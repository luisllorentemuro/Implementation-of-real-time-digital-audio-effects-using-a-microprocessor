/** \file efecto_none.h
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/13 18:15:31
*/

#ifndef _EFECTO_NONE_INT_H_
#define _EFECTO_NONE_INT_H_

#include <stdint.h>
#include "efectos.h"

efecto_t * efecto_none_create(void);

int16_t efecto_none_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_NONE_INT_H_ */ 

/** \file efecto_atenuacion_int.h
* A brief file description.
* Created on:    2022/07/13
* Last modified: 2022/07/13 18:38:53
*/

#ifndef _EFECTO_ATENUACION_INT_H_
#define _EFECTO_ATENUACION_INT_H_

#include <stdint.h>
#include "efectos.h"

efecto_t * efecto_atenuacion_create(void);
void efecto_atenuacion_update(efecto_t * efecto, efecto_atenuacionparams_t * params);
int16_t efecto_atenuacion_apply(efecto_t * efecto, int16_t sample);

#endif  /* _EFECTO_ATENUACION_INT_H_ */ 

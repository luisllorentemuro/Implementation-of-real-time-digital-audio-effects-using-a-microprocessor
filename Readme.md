---
title: "Módulo Efectos"

toc:
  depth_from: 1
  depth_to: 4
  ordered: false
  ignoreLink: true
html:
  embed_local_images: true
  embed_svg: true
---

## Módulo efectos:

![](classes.svg)

## Procedimiento para crear un nuevo efecto:

### Componentes:

- **Datos**: definir dos estructuras, una para los parámetros de configuración, y otra para los elementos internos del efecto:
  ```c
  // Estructura para definir los parámetros 
    typedef struct efecto_PARAMS_st{
        int16_t param1;  /* <! param1: bla bla bla */
        int16_t param2;  /* <! param2: bla bla bla */
        //...
    } efecto_NOMBREparams_t;
 
  // Estructura para definir los elementos internos
    typedef struct efecto_NOMBRE_internals_str {
        int16_t id;
        int16_t z_1;
        //...
    } efecto_NOMBREinternals_t;

  ```
- **Funciones**: crear las 3 funciones que permiten crear, actualizar y aplicar el efecto:
  ```c 
    efecto_t * efecto_NOMBRE_create(void);
    void efecto_NOMBRE_update(efecto_t * efecto, void * params);
    int16_t efecto_NOMBRE_apply(efecto_t * efecto, int16_t sample);
  ```

### Ficheros:
- `efecto_NOMBRE.h` fichero *público*, incluye la definición del tipo para los parámetros del algoritmo. Se situará en el directorio `include`.
- `efecto_NOMBRE_int.h` fichero *privado*, incluye los prototipos de las 3 funciones creadas. Se situará en el directorio `src`.
- `efecto_NOMBRE.c` fichero *privedo*, incluye la definición del tipo para los elementos internos del efecto y el cuerpo de las funciones creadas. Se situará en el directorio `src`.

## Procedimiento para añadir un efecto:

1.- Modificar el fichero `include/efectos.h`

```c
#include <stdint.h>
#include "efecto_none.h"
#include "efecto_mute.h"                     // <<---- Incluir el efecto_NOMBRE.h
#include "efecto_atenuacion.h"
#include "efecto_reverb.h"
#include "efecto_overdrive.h"
#include "efecto_distortion.h"
#include "efecto_fuzz.h"

typedef enum efectos_enu { EFECTO_NONE, 
                           EFECTO_MUTE,      // <<---- Incluir el nombre del efecto
                           EFECTO_ATENUACION,   
                           EFECTO_REVERB,       
                           EFECTO_OVERDRIVE,    
                           EFECTO_DISTORTION,   
                           EFECTO_FUZZ,         
                           } efectos_enu_t;

```

2.- Modificar el fichero `src/efectos_int.h`

```c
#include "efectos.h"

#include "efecto_none_int.h"
#include "efecto_mute_int.h"                  // <<---- Incluir el efecto_NOMBRE_int.h
#include "efecto_atenuacion_int.h"    
#include "efecto_reverb_int.h"         
#include "efecto_overdrive_int.h"     
#include "efecto_distortion_int.h"     
#include "efecto_fuzz_int.h"           

```

3.- Modificar las funciones de `src/efectos.c` para soportar el nuevo efecto:

```c 


efecto_t *efecto_create(efectos_enu_t efecto)
{
    efecto_t *efecto_ptr;
    switch (efecto)
    {
    case EFECTO_NONE:
        efecto_ptr = efecto_none_create();
        break;
    case EFECTO_MUTE:                       //
        efecto_ptr = efecto_mute_create();  // <<---- Código añadido para el nuevo efecto
        break;                              //
    case EFECTO_ATENUACION:
        efecto_ptr = efecto_atenuacion_create();
        break;
    case EFECTO_REVERB:
        efecto_ptr = efecto_reverb_create();
        break;
    case EFECTO_OVERDRIVE:
        efecto_ptr = efecto_overdrive_create();
        break;
    case EFECTO_DISTORTION:
        efecto_ptr = efecto_distortion_create();
        break;
    case EFECTO_FUZZ:
        efecto_ptr = efecto_fuzz_create();
        break;
    default:
        efecto_ptr = NULL;
    }
    return efecto_ptr;
}


void efecto_destroy(efecto_t * efecto) {
    if (efecto != NULL)
    {
    if (efecto->internals != NULL) {
        free(efecto->internals);
    }
    if (efecto->params != NULL) {
        free(efecto->params);
    }
    free(efecto);
    }
}

void efecto_update(efecto_t *efecto, void *params)
{
    switch (efecto->efecto)
    {
    case EFECTO_NONE:
        break;
    case EFECTO_MUTE:
        break;
    case EFECTO_ATENUACION:                       //
        efecto_atenuacion_update(efecto, params); // <<---- Código añadido para el nuevo efecto
        break;                                    //
    case EFECTO_REVERB:
        efecto_reverb_update(efecto, params);
        break;
    case EFECTO_OVERDRIVE:
        break;
    case EFECTO_DISTORTION:
        efecto_distortion_update(efecto, params);
        break;
    case EFECTO_FUZZ:
        efecto_fuzz_update(efecto, params);
        break;
    default:
        break;
    }
}




int16_t efecto_apply(efecto_t *efecto, int16_t sample)
{
    int16_t salida = 0;
    switch (efecto->efecto)
    {
    case EFECTO_NONE:
        salida = efecto_none_apply(efecto,sample);
        break;
    case EFECTO_MUTE:                               //
        salida = efecto_mute_apply(efecto,sample);  // <<---- Código añadido para el nuevo efecto
        break;                                      //
    case EFECTO_ATENUACION:
        salida = efecto_atenuacion_apply(efecto, sample);
        break;
    case EFECTO_REVERB:
        salida = efecto_reverb_apply(efecto, sample);
        break;
    case EFECTO_OVERDRIVE:
        salida = efecto_overdrive_apply(efecto, sample);
        break;
    case EFECTO_DISTORTION:
        salida = efecto_distortion_apply(efecto, sample);
        break;
    case EFECTO_FUZZ:
        salida = efecto_fuzz_apply(efecto, sample);
        break;
    default:
        break;
    }
    return salida;
}

```









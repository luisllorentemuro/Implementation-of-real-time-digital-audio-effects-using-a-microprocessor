
#include <stdint.h>
#include "pulsaciones.h"

static const uint16_t tiempo1=400;
static const uint16_t tiempo2=100;

uint8_t pulsaciones2(uint8_t pulsado)
{
  typedef enum  {INIT, P1_1, P1_0, P2_1, P2_0, ESPERA, 
                 CLICK_1, CLICK_2, PULS_1, PULS_2} puls_t;
  static puls_t estado_puls=INIT;
  static uint16_t contador=0;
  uint16_t salida=0;

  switch (estado_puls){
      case INIT: if (pulsado)
                    {estado_puls=P1_1;
                     contador=0;
                    }
        break;
        case P1_1: contador++;
                     if (!pulsado) 
                     {  contador=0;
                        estado_puls=P1_0;
                     }
                     if (contador>tiempo1) estado_puls=PULS_1;
        break;
        case P1_0: contador++;
                     if (pulsado) estado_puls=P2_1;
                     if (contador>tiempo2) estado_puls=CLICK_1;
        break;
        case P2_1: contador++;
                     if (!pulsado) 
                     {  contador=0;
                        estado_puls=P2_0;
                     }
                     if (contador>tiempo1) estado_puls=PULS_2;
        break;
        case P2_0: contador++;
                     if (contador>tiempo2) estado_puls=CLICK_2;
        break;
        case CLICK_1: salida=1;
                        estado_puls=ESPERA;
        break;
        case CLICK_2: salida=2;
                        estado_puls=ESPERA;
        break;
        case PULS_1: salida=3;
                        estado_puls=ESPERA;
        break;
        case PULS_2: salida=4;
                        estado_puls=ESPERA;
        break;
        case ESPERA: if (!pulsado) estado_puls=INIT;
        break;
        default: salida=0xFFFF;
        break;
  }
  return salida;
}


uint8_t pulsaciones(uint8_t pulsado)
{
  typedef enum  {INIT, P1_1, P1_0, ESPERA, PULS_1} puls_t;
  static puls_t estado_puls=INIT;
  static uint16_t contador=0;
  uint16_t salida=0;

  switch (estado_puls){
        case INIT: contador=0;
                   if (pulsado)
                      {estado_puls=P1_1;
                      }
        break;
        case P1_1: contador++;
                     if (!pulsado) 
                     {  contador=0;
                        estado_puls=P1_0;
                     }
                     if (contador>tiempo1) estado_puls=PULS_1;
        break;
        case P1_0: contador++;
                     if (pulsado) contador=0;
                     if (contador>tiempo2) 
                        {   estado_puls=INIT;
                            salida=1;
                        }
        break;
        case PULS_1: salida=2;
                     estado_puls=ESPERA;
        break;
        case ESPERA: if (!pulsado) estado_puls=INIT;
        break;
        default: salida=0xFFFF;
        break;
  }
  return salida;
}

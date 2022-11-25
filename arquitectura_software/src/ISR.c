/*
 * ISR.c
 *  Created on: 13 jul. 2020
 *  Last modified: 2020/11/17 12:38:57
 */

#include "mcu.h"
#include "FM4_WM8731.h"
#include "HAL_FM4_i2s.h"
#include "HAL_FM4_gpio.h"
#include "pulsaciones.h"
#include "efectos.h"
#include "efectos_int.h"

extern uint8_t g_contador;

void PRGCRC_I2S_IRQHandler(void)
{
    int16_t segnal_input, dummy;  // Señal entrada
		int16_t segnal_proc;
					
		static efectos_enu_t efecto = EFECTO_NONE;
		const efectos_enu_t efectos[7] = {EFECTO_NONE, EFECTO_MUTE, EFECTO_ATENUACION, EFECTO_DELAY, EFECTO_OVERDRIVE, EFECTO_DISTORTION, EFECTO_FUZZ};
		
    // Coge datos del codec
    FM4_WM8731_rd(&segnal_input, &dummy);
		efecto = efectos[g_contador]; 
		
		efecto_t *efecto_ptr;
		efecto_atenuacionparams_t *atenuacion_params;
		efecto_delayparams_t *delay_params;
		efecto_distortionparams_t *distortion_params;
		efecto_fuzzparams_t *fuzz_params;

		switch(efecto)
		{
		case EFECTO_NONE:
			efecto_ptr = efecto_none_create();
			segnal_proc = efecto_none_apply(efecto_ptr, segnal_input);
			efecto_destroy(efecto_ptr);
		break;	
			
		case EFECTO_MUTE:
			efecto_ptr = efecto_mute_create();
			segnal_proc = efecto_mute_apply(efecto_ptr, segnal_input);
			efecto_destroy(efecto_ptr);
		break;		
			
		case EFECTO_ATENUACION:
			efecto_ptr = efecto_atenuacion_create();
			efecto_atenuacion_update(efecto_ptr, atenuacion_params); // 4096
			segnal_proc = efecto_atenuacion_apply(efecto_ptr, segnal_input);
			efecto_destroy(efecto_ptr);
		break;

		case EFECTO_DELAY:
			efecto_ptr = efecto_delay_create();
			efecto_delay_update(efecto_ptr, delay_params); // 49152
			segnal_proc = efecto_delay_apply(efecto_ptr, segnal_input);
		  efecto_destroy(efecto_ptr);
		break;
		
		case EFECTO_OVERDRIVE:
			efecto_ptr = efecto_overdrive_create();
			segnal_proc = efecto_overdrive_apply(efecto_ptr, segnal_input);
		  efecto_destroy(efecto_ptr);
		break;

		case EFECTO_DISTORTION:
			efecto_ptr = efecto_distortion_create();
			efecto_distortion_update(efecto_ptr, distortion_params); // 96000,32767
			segnal_proc = efecto_distortion_apply(efecto_ptr, segnal_input);
		  efecto_destroy(efecto_ptr);
		break;
			
		case EFECTO_FUZZ:
			efecto_ptr = efecto_fuzz_create();
			efecto_fuzz_update(efecto_ptr, fuzz_params); // 32767,8192,32401,32401,7248.25594031620096
			segnal_proc = efecto_fuzz_apply(efecto_ptr, segnal_input);
		  efecto_destroy(efecto_ptr);
		break;		
}

//segnal_proc = segnalFSK_in;
FM4_WM8731_wr(segnal_proc, segnal_proc);

#if _LAB_DEBUG_ == 0
    // Variable salida, buffer circular de 512 palabras donde se guardan las señales
    // Para volcalrlas a un fichero ejecutar en el debugger:
    //
    //      dump_salida(512,1.0/8000)
    //
    volatile static int16_t salida[512];
    static uint16_t j = 0;
    // Almacena en salida las 2 señales
    salida[j++] = segnalFSK_in;
    salida[j] = segnal_proc;
    j = (j + 1) & 0x007FF;
#endif
}


/*
 * HAL_FM4_timer.c
 *   Dual Timer HAL
 *  
 *      Author: Isidro
 */
#include <stdint.h>
#include "HAL_FM4_dtimer.h"
#include "mcu.h"



// CICLOS_US: n�mero de ciclos que corresponden a 1us (50 . 100MHz)
static const uint32_t CICLOS_US=200u;



static irq_handler_t Dtim_Isr_v[2]={NULL,NULL};


/*------------------------------------------------- DTIM_InitAll -----
 *
 * Funcion: DTIM_InitAll(DTIMER, period, ctl)
 *
 * Proposito:  Da valor a los registros PRD y TCR del timer.
 *
 * Parametros:
 *             DTIMER  (IN): Timer sobre el que se actua
 *                           (DTIMER1, DTIMER2)
 *             period (IN): Valor que carga el registro PRD
 *             ctl    (IN): Valor que carga el registro ctl
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
void DTIM_InitAll(const Dtimers_t DTIMER, const uint32_t period, const uint32_t ctl)
{  
	 // Valor de recarga del timer
   FM4_DTIM[DTIMER].TIMERXBGLOAD=period;
   FM4_DTIM[DTIMER].TIMERXLOAD=period;
   // Habilitacion del timer ...
   FM4_DTIM[DTIMER].TIMERXCONTROL=ctl;
}

/*------------------------------------------------- DTIM_Init -----
 *
 * Funcion: DTIM_Init(TIMER, period, ctl)
 *
 * Proposito:  Da valor a los registros TIMERXBGLOAD/TIMERXLOAD y 
 *                  TIMERXCONTROL.
 *
 * Parametros:
 *             DTIMER  (IN): Timer sobre el que se actua
 *                           (DTIMER1, DTIMER2)
 *             period (IN): Valor que carga el registro 
 *                            TIMERXBGLOAD/TIMERXLOAD
 *
 *
 * Returns:    void
 *
 * Nota:  Se configura en modo periódico y 32 bits y se habilita
 *          TIMERXCONTROL=(1u<<7)|(1u<<6)|(1u<<1)
 *
 *-------------------------------------------------------------------*/
void DTIM_Init(const Dtimers_t DTIMER, const uint32_t period)
{  // Valor de recarga del timer
   FM4_DTIM[DTIMER].TIMERXBGLOAD=period-1;
   if(!(FM4_DTIM[DTIMER].TIMERXCONTROL&(1<<7))) 
   { FM4_DTIM[DTIMER].TIMERXLOAD=period-1;
     // Habilitacion del timer 32 bits en modo periodico
     FM4_DTIM[DTIMER].TIMERXCONTROL=(1u<<7)|(1u<<6)|(1u<<1);
   }
}


/*------------------------------------------------- DTIM_ChkOvf -----
 *
 * Funcion: DTIM_ChkOvf(DTIMER)
 *
 * Proposito:  Comprueba si un timer ha desbordado (pasado por 0).
 *
 * Parametros:
 *             DTIMER  (IN): Timer sobre el que se actua
 *                           (DTIMER1, DTIMER2)
 *
 * Returns:    1 . El timer ha desbordado
 *             0 . el timer no ha desbordado
 *
 * Nota: Si el timer ha desbordado, la funcion limpia la interrupcion 
 *          pendiente en  TimerXRIS escribiendo en TimerXIntClr
 *
 *-------------------------------------------------------------------*/
int  DTIM_ChkOvf (const Dtimers_t DTIMER)
{   int tim = 0;
      
    if (FM4_DTIM[DTIMER].TIMERXRIS & 1u)
    {
        tim = 1;
        // Writing any value to TimerXIntClr clears an interrupt output from the counter.
        FM4_DTIM[DTIMER].TIMERXINTCLR = 1234;
    }
    return tim;
}

/*------------------------------------------------- DTIM_DelayUs -----
 *
 * Funcion: DTIM_DelayUs(DTIMER, delay_us)
 *
 * Proposito:  Utiliza un timer para implementar un retraso
 *              el tiempo de este retraso se expresa en us.
 *
 * Parametros:
 *             DTIMER    (IN): Timer utilizado (DTIMER1, DTIMER2)
 *             delay_us (IN): tiempo en us
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
void DTIM_DelayUs (const Dtimers_t DTIMER, const uint32_t delay_us)
{   uint32_t ciclos;
    ciclos=delay_us*CICLOS_US;
    DTIM_InitAll(DTIMER,ciclos,(1<<7)|(1<<1)|(1<<0));
    while(!DTIM_ChkOvf(DTIMER));
}


/** IRQ DT1_2_IRAHandler */

void DTIM_RegISR(const Dtimers_t DTIMER, const irq_handler_t Dtim_Isr)
{
    Dtim_Isr_v[DTIMER]=Dtim_Isr;
}

void DT1_2_IRAHandler(void)
{
    if (DTIM_ChkOvf(DTIMER1))
    {
        if (Dtim_Isr_v[DTIMER1]!=NULL)
        {
            Dtim_Isr_v[DTIMER1]();
        }
    }
    if (DTIM_ChkOvf(DTIMER2))
    {
        if (Dtim_Isr_v[DTIMER2]!=NULL)
        {
            Dtim_Isr_v[DTIMER2]();
        }
    }
}

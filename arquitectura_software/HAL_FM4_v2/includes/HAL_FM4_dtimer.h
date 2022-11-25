/** @file HAL_FM4_dtimer.h	
* @brief This module contains interface definitions for the
* Dual timer configuration. 
* Created: 2019/11/18 19:02:23
* @date Last modified: 2020/09/28 11:37:26
*/
#ifndef HAL_HAL_FM4_DTIMER_H_
#define HAL_HAL_FM4_DTIMER_H_

#include <stdint.h>
/**********************************************************************
* Typedefs
**********************************************************************/
/**
* Defines the two timers in Dual Timer peripheral.
*/
typedef enum Dtimers_enum 
    { 
        DTIMER1=0,    /** Defines Dtimer channel 1 */
        DTIMER2=1,    /** Defines Dtimer channel 2 */
        MAX_DTIMER=2  /** Defines Number of channels in Dtimer */
    } Dtimers_t;
    
typedef  void (* irq_handler_t)();

void DTIM_InitAll(const Dtimers_t DTIMER, const uint32_t period, const uint32_t ctl);
void DTIM_Init(const Dtimers_t DTIMER, const uint32_t period);
int  DTIM_ChkOvf (const Dtimers_t DTIMER);
void DTIM_IntEnable (const Dtimers_t TIMER);
void DTIM_RegISR(const Dtimers_t DTIMER, const irq_handler_t Dtim_Isr);


void DTIM_DelayUs (const Dtimers_t DTIMER, const uint32_t delay_us);


#endif /* HAL_HAL_FM4_DTIMER_H_ */

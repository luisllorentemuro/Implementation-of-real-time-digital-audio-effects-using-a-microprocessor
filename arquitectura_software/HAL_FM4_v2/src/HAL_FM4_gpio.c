/*
 * HAL_FM4_gpio.c
 * Cypress FM4 Funciones para acceder a los GPIO:
 *      GPIO_ChannelRead
 *      GPIO_ChannelWrite
 *      GPIO_ChannelToggle
 *      GPIO_ChannelMode
 *      GPIO_ChannelDigAna
 *  Last modified: 2020/09/24 11:07:08
 */

//#include <assert.h>
#include "mcu.h"
#include "HAL_FM4_gpio.h" /* For this modules definitions */

/*------------------------------------------------- GPIO_ChannelRead -----
*  Funcion: GPIO_ChannelRead(channel)
*
* Proposito:    Esta función permite leer el estado de un pin GPIO
*
* Pre-condición: El canal debe estar configurado
*
* Parametros: channel  (IN)  Canal GPIO a leer
*
* Return:                    Valor lógico del canal (GPIO_LOW,GPIO_HIGH)
*
**********************************************************************/
GpioPinState_t GPIO_ChannelRead(const GpioChannel_t channel)
{
    uint8_t port;
    uint8_t bitport;
    uint16_t dataport;
    GpioPinState_t pin;

    //assert(channel < 256);

    port = channel >> 4;
    bitport = channel & 0xF;

    volatile uint32_t *registro;
    registro = &FM4_GPIO->PDIR0 + port;
    dataport = *registro;
    pin = (dataport & (1u << bitport)) ? GPIO_HIGH : GPIO_LOW;
    return pin;
}

/*------------------------------------------------- GPIO_ChannelWrite -----
*  Funcion: GPIO_Channelwrite(channel,pin)
*
* Proposito:    Esta función permite escribir en un pin GPIO
*
* Pre-condición: El canal debe estar configurado
*
* Parametros: channel  (IN)  Canal GPIO a leer
              pin      (IN)  Valor lógico (GPIO_LOW,GPIO_HIGH)
*
* Return:      void
*
**********************************************************************/

void GPIO_ChannelWrite(const GpioChannel_t channel, const GpioPinState_t pin)
{
    uint8_t port;
    uint8_t bitport;

    //assert(channel < 256);

    port = channel >> 4;
    bitport = channel & 0xF;
    volatile uint32_t *registro;
    registro = &FM4_GPIO->PDOR0 + port;
    *registro = (*registro & (~(1u << bitport))) | (pin << bitport);
}

/*------------------------------------------------- GPIO_ChannelToggle -----
*  Funcion: GPIO_ChannelToggle(channel)
*
* Proposito:    Esta función cambia el estado un pin GPIO
*
* Pre-condición: El canal debe estar configurado
*
* Parametros: channel  (IN)  Canal GPIO 
*
* Return:      void
*
**********************************************************************/
void GPIO_ChannelToggle(const GpioChannel_t channel)
{
    uint8_t port;
    uint8_t bitport;
    //uint16_t dataport;

    //assert(channel < 256);

    port = channel >> 4;
    bitport = channel & 0xF;

    volatile uint32_t *registro;
    registro = &FM4_GPIO->PDOR0 + port;
    *registro = *registro ^ (1u << bitport);

}


/*------------------------------------------------- GPIO_ChannelMode -----
*  Funcion: GPIO_ChannelMode(channel, mode)
*
* Proposito:    Esta función cambia el modo un pin GPIO Entrada/Salida
*
* Parametros: channel  (IN)  Canal GPIO
              mode:    (IN)  Modo del canal (GPIO_INPUT/GPIO_OUTPUT)
*
* Return:      void
*
**********************************************************************/

void GPIO_ChannelMode(const GpioChannel_t channel, const GpioDir_t mode)
{
    uint8_t port;
    uint8_t bitport;
    //uint16_t dataport;

    //assert(channel < 256);

    port = channel >> 4;
    bitport = channel & 0xF;

    volatile uint32_t *registro;
    registro = &FM4_GPIO->DDR0 + port;
    *registro = (*registro & (~(1u << bitport))) | (mode << bitport);

}


/*------------------------------------------------- GPIO_ChannelDigAna -----
*  Funcion: GPIO_ChannelDigAna(channel, mode)
*
* Proposito:    Esta función cambia el modo un pin GPIO (Analog/Digital)
*
* Parametros: channel  (IN)  Canal GPIO
              mode:    (IN)  Modo del canal (GPIO_DIG/GPIO_ANA)
*
* Return:      void
*
**********************************************************************/

void GPIO_ChannelDigAna(const GpioChannel_t channel, const GpioDigAna_t mode)
{
    uint8_t port;
    uint8_t bitport;

    //assert((int32_t)channel < 256);

    port = channel >> 4;
    bitport = channel & 0xF;

    if (port == 1)
        FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << bitport))) | (mode << bitport);
    else if (port == 2)
        switch (bitport)
        {
        case 2:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 31))) | (mode << 31);
            break;
        case 3:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 30))) | (mode << 30);
            break;
        case 4:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 29))) | (mode << 29);
            break;
        case 5:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 28))) | (mode << 28);
            break;
        case 7:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 27))) | (mode << 27);
            break;
        case 8:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 26))) | (mode << 26);
            break;
        case 9:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 25))) | (mode << 25);
            break;
        case 0xA:
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << 24))) | (mode << 24);
            break;
        default: ;
            //assert(0);
        }
    else if (port == 0xB)
        {
            FM4_GPIO->ADE = (FM4_GPIO->ADE & (~(1u << (bitport+16)))) | (mode << (bitport+16));
        }
    else ;//assert(0);
}

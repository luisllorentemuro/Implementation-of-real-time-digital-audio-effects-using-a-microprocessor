/*
 * FM4_WM8731.c
 * Cypress FM4 Funciones para acceder al codec WM8731
 *  Created on: 13 jul. 2017
 *  Last modified: 2020/11/12 14:05:11
 */

#include <stdint.h>
#include "mcu.h"
#include "FM4_WM8731.h"
#include "HAL_FM4_i2c.h"
#include "HAL_FM4_i2s.h"

static void DonaldDelay(volatile uint32_t nCount)
{
    for (; nCount > 0; nCount--)
        ;
}

static void Codec_WriteRegister(uint8_t RegisterAddr, uint8_t RegisterValue)
{
    I2C_write(WM8731_I2C_ADDRESS, ((RegisterAddr << 1) & 0xFF), ((RegisterValue)&0xFF));
}

void FM4_WM8731_init(uint8_t fs, uint8_t select_input, uint8_t hp_out_gain, uint8_t line_in_gain)
{
    I2C_init();                                              // initialise I2C peripheral
    DonaldDelay(1000);                                       // before writing to codec registers
    Codec_WriteRegister(WM8731_RESET, 0x00);                 // reset codec
    Codec_WriteRegister(WM8731_LINE_IN_LEFT, line_in_gain);  // set left line in gain
    Codec_WriteRegister(WM8731_LINE_IN_RIGHT, line_in_gain); // set right line in gain
    Codec_WriteRegister(WM8731_HP_OUT_LEFT, hp_out_gain);    // set left headphone out gain
    Codec_WriteRegister(WM8731_HP_OUT_RIGHT, hp_out_gain);   // set right headphone out gain
    Codec_WriteRegister(WM8731_ANALOG_PATH, select_input);   // select line in or microphone input
    Codec_WriteRegister(WM8731_DIGITAL_PATH, 0x00);          // can select de-emphasis, HPF and mute here
    Codec_WriteRegister(WM8731_POWER_DOWN, 0x00);            // disable power down on all parts of codec
    Codec_WriteRegister(WM8731_INTERFACE, 0x53);             // select digital audio interface (I2S) format
    Codec_WriteRegister(WM8731_SAMPLING_RATE, fs);           // sample rate control
    Codec_WriteRegister(WM8731_CONTROL, 0x01);               // activate codec

    I2S_init(fs);
    FM4_I2S0->OPRREG_f.RXENB = 1;
    FM4_I2S0->CNTREG_f.RXDIS = 0;
    FM4_I2S0->OPRREG_f.TXENB = 1;
    FM4_I2S0->CNTREG_f.TXDIS = 0;
    FM4_I2S0->INTCNT_f.RFTH = 0x0F & (0x00);
    FM4_I2S0->INTCNT_f.TFTH = 0x0F & (0x00);
    }



void FM4_WM8731_wr(int16_t datoL, int16_t datoR)
{
    WM8731_data_t dato;
    dato.uint16bit[LEFT]=datoL;
    dato.uint16bit[RIGHT]=datoR;
    I2S_tx(dato.uint32bit);
}


void FM4_WM8731_rd(int16_t *datoL, int16_t *datoR)
{
    WM8731_data_t dato;
    dato.uint32bit=I2S_rx();
    *datoL=dato.uint16bit[LEFT];
    *datoR=dato.uint16bit[RIGHT];
}

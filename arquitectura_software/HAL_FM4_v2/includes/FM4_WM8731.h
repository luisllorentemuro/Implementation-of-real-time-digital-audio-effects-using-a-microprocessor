#ifndef __FM4_WM8731__
#define __FM4_WM8731__

#include <stdint.h>

#define WM8731_I2C_ADDRESS 0x1A // 0011010

#define WM8731_LINE_IN_LEFT (( uint8_t)0x00)
#define WM8731_LINE_IN_RIGHT (( uint8_t)0x01)
#define WM8731_HP_OUT_LEFT (( uint8_t)0x02)
#define WM8731_HP_OUT_RIGHT (( uint8_t)0x03)
#define WM8731_ANALOG_PATH (( uint8_t)0x04)
#define WM8731_DIGITAL_PATH (( uint8_t)0x05)
#define WM8731_POWER_DOWN (( uint8_t)0x06)
#define WM8731_INTERFACE (( uint8_t)0x07)
#define WM8731_SAMPLING_RATE (( uint8_t)0x08)
#define WM8731_CONTROL (( uint8_t)0x09)
#define WM8731_RESET (( uint8_t)0x0F)

#define FS_48000_HZ (( uint8_t)0x00)
#define FS_8000_HZ (( uint8_t)0x0C)
#define FS_16000_HZ (( uint8_t)0x58)
#define FS_24000_HZ (( uint8_t)0x40)
#define FS_32000_HZ (( uint8_t)0x18)
#define FS_96000_HZ (( uint8_t)0x1C)

#define WM8731_MIC_IN (( uint8_t)0x14)
#define WM8731_MIC_IN_BOOST (( uint8_t)0x15)
#define WM8731_LINE_IN (( uint8_t)0x11)

#define IO_METHOD_INTR (( uint8_t)0x00)
#define IO_METHOD_DMA (( uint8_t)0x01)

#define WM8731_LINE_IN_GAIN_0_DB (( uint8_t)0x17)
#define WM8731_LINE_IN_GAIN_3_DB (( uint8_t)0x19)
#define WM8731_LINE_IN_GAIN_6_DB (( uint8_t)0x1B)
#define WM8731_LINE_IN_GAIN_9_DB (( uint8_t)0x1D)
#define WM8731_LINE_IN_GAIN_12_DB (( uint8_t)0x1F)
#define WM8731_LINE_IN_ATTEN_3_DB (( uint8_t)0x15)
#define WM8731_LINE_IN_ATTEN_6_DB (( uint8_t)0x13)
#define WM8731_LINE_IN_ATTEN_9_DB (( uint8_t)0x11)

#define WM8731_HP_OUT_GAIN_0_DB (( uint8_t)0x79)
#define WM8731_HP_OUT_GAIN_3_DB (( uint8_t)0x7C)
#define WM8731_HP_OUT_GAIN_6_DB (( uint8_t)0x7F)
#define WM8731_HP_OUT_ATTEN_3_DB (( uint8_t)0x76)
#define WM8731_HP_OUT_ATTEN_6_DB (( uint8_t)0x73)


#define LEFT  1
#define RIGHT 0

typedef union WM8731_data
{
  int32_t uint32bit;    
  int16_t uint16bit[2];
} WM8731_data_t;


/*------------------------------------------------- FM4_WM8731_init --
 *
 * Funcion: FM4_WM8731_init(fs, select_input, hp_out_gain,line_in_gain);

 *
 * Proposito:  Esta función configura el codec WM8731 de la placa 
 *              FM4-pioneer
 *
 * Parametros: 
 *          fs      (IN): Frecuencia de muestreo, posibles valores:
 *                          FS_8000_HZ, FS_16000_HZ, FS_24000_HZ
 *                          FS_32000_HZ, FS_48000_HZ, FS_96000_HZ
 *          select_input (IN): Selecciona entrada analógica:
 *                                  WM8731_MIC_IN, WM8731_LINE_IN
 *          hp_out_gain (IN): Ganancia de la salida de auriculares:
 *                                  WM8731_HP_OUT_GAIN_0_DB
 *                                  WM8731_HP_OUT_GAIN_3_DB 
 *                                  WM8731_HP_OUT_GAIN_6_DB 
 *                                  WM8731_HP_OUT_ATTEN_3_DB
 *                                  WM8731_HP_OUT_ATTEN_6_DB
 *          line_in_gain (IN): Ganancia de la entrada de línea:
 *                                  WM8731_LINE_IN_GAIN_0_DB 
 *                                  WM8731_LINE_IN_GAIN_3_DB 
 *                                  WM8731_LINE_IN_GAIN_6_DB 
 *                                  WM8731_LINE_IN_GAIN_9_DB 
 *                                  WM8731_LINE_IN_GAIN_12_DB
 *                                  WM8731_LINE_IN_ATTEN_3_DB
 *                                  WM8731_LINE_IN_ATTEN_6_DB
 *                                  WM8731_LINE_IN_ATTEN_9_DB
 *
 * Returns:    void
 *
 * Nota:    Esta función inicia el bus I2C, el codec y el bus I2S
 *
 *-------------------------------------------------------------------*/
 
void FM4_WM8731_init(uint8_t fs, uint8_t select_input, uint8_t hp_out_gain, uint8_t line_in_gain);

/*------------------------------------------------- FM4_WM8731_wr -----
 * Función: FM4_WM8731_Wr(datoL,datoR)
 *
 * Propósito:  Escribe datoL y datoR en WM8731.
 *
 * Parametros:
 *             datoL (IN): Dato canal izquierdo.
 *             datoR (IN): Dato canal derecho.
 *
 * Returns:    void
 *
 * Nota:
 *-------------------------------------------------------------------*/
void FM4_WM8731_wr(int16_t datoL, int16_t datoR);

/*------------------------------------------------- FM4_WM8731_rd -----
 * Función: FM4_WM8731_rd(&datoL,&datoR)
 *
 * Propósito:  Lee datoL y datoR del codec  WM8731.
 *
 * Parametros:
 *             datoL (OUT): Dato canal izquierdo.
 *             datoR (OUT): Dato canal derecho.
 *
 * Returns:    void
 *
 * Nota:
 *-------------------------------------------------------------------*/
void FM4_WM8731_rd(int16_t *datoL, int16_t *datoR);

#endif

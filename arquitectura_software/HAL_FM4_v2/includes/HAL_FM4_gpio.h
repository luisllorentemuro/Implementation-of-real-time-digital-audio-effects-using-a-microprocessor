/*
 * HAL_FM4_gpio.h
 * Cypress FM4 Funciones para acceder a los GPIO:
 *      GPIO_ChannelRead
 *      GPIO_ChannelWrite
 *      GPIO_ChannelToggle
 *      GPIO_ChannelMode
 *      GPIO_ChannelDigAna
 *  Last modified: 2020/09/24 11:07:08
 */

#ifndef INCLUDES_HAL_FM4_GPIO_H_
#define INCLUDES_HAL_FM4_GPIO_H_

/**********************************************************************
* Typedefs
**********************************************************************/
/**
* Defines the possible states for a digital output pin.
*/
typedef enum GpioPinState_enu
{
  GPIO_LOW=0,  /** Defines digital state
              ground */
  GPIO_HIGH=1, /** Defines digital state
               power */
  GPIO_PIN_STATE_MAX=2 /** Defines the maximum
               digital state */
}GpioPinState_t;
/**
* Defines an enumerated list of all the channels (pins) on the MCU
* device. The value of each symbol corresponds with the port number (MSB),
* and the channel (LSB).
*/
typedef enum GpioChannel_enu
{
  P00 = 0x00,    /**< Port:0, Channel:0*/
  P01 = 0x01,    /**< Port:0, Channel:1*/
  P02 = 0x02,    /**< Port:0, Channel:2*/
  P03 = 0x03,    /**< Port:0, Channel:3*/
  P04 = 0x04,    /**< Port:0, Channel:4*/
  P08 = 0x08,    /**< Port:0, Channel:8*/
  P09 = 0x09,    /**< Port:0, Channel:9*/
  P0A = 0x0A,    /**< Port:0, Channel:A*/
  P10 = 0x10,    /**< Port:1, Channel:0*/
  P11 = 0x11,    /**< Port:1, Channel:1*/
  P12 = 0x12,    /**< Port:1, Channel:2*/
  P13 = 0x13,    /**< Port:1, Channel:3*/
  P14 = 0x14,    /**< Port:1, Channel:4*/
  P15 = 0x15,    /**< Port:1, Channel:5*/
  P16 = 0x16,    /**< Port:1, Channel:6*/
  P17 = 0x17,    /**< Port:1, Channel:7*/
  P18 = 0x18,    /**< Port:1, Channel:8*/
  P19 = 0x19,    /**< Port:1, Channel:9*/
  P1A = 0x1A,    /**< Port:1, Channel:A*/
  P1B = 0x1B,    /**< Port:1, Channel:B*/
  P1C = 0x1C,    /**< Port:1, Channel:C*/
  P1D = 0x1D,    /**< Port:1, Channel:D*/
  P1E = 0x1E,    /**< Port:1, Channel:E*/
  P1F = 0x1F,    /**< Port:1, Channel:F*/
  P20 = 0x20,    /**< Port:2, Channel:0*/
  P21 = 0x21,    /**< Port:2, Channel:1*/
  P22 = 0x22,    /**< Port:2, Channel:2*/
  P23 = 0x23,    /**< Port:2, Channel:3*/
  P24 = 0x24,    /**< Port:2, Channel:4*/
  P25 = 0x25,    /**< Port:2, Channel:5*/
  P26 = 0x26,    /**< Port:2, Channel:6*/
  P27 = 0x27,    /**< Port:2, Channel:7*/
  P28 = 0x28,    /**< Port:2, Channel:8*/
  P29 = 0x29,    /**< Port:2, Channel:9*/
  P2A = 0x2A,    /**< Port:2, Channel:A*/
  P30 = 0x30,    /**< Port:3, Channel:0*/
  P31 = 0x31,    /**< Port:3, Channel:1*/
  P32 = 0x32,    /**< Port:3, Channel:2*/
  P33 = 0x33,    /**< Port:3, Channel:3*/
  P34 = 0x34,    /**< Port:3, Channel:4*/
  P35 = 0x35,    /**< Port:3, Channel:5*/
  P36 = 0x36,    /**< Port:3, Channel:6*/
  P37 = 0x37,    /**< Port:3, Channel:7*/
  P38 = 0x38,    /**< Port:3, Channel:8*/
  P39 = 0x39,    /**< Port:3, Channel:9*/
  P3A = 0x3A,    /**< Port:3, Channel:A*/
  P3B = 0x3B,    /**< Port:3, Channel:B*/
  P3C = 0x3C,    /**< Port:3, Channel:C*/
  P3D = 0x3D,    /**< Port:3, Channel:D*/
  P3E = 0x3E,    /**< Port:3, Channel:E*/
  P40 = 0x40,    /**< Port:4, Channel:0*/
  P41 = 0x41,    /**< Port:4, Channel:1*/
  P42 = 0x42,    /**< Port:4, Channel:2*/
  P43 = 0x43,    /**< Port:4, Channel:3*/
  P44 = 0x44,    /**< Port:4, Channel:4*/
  P45 = 0x45,    /**< Port:4, Channel:5*/
  P46 = 0x46,    /**< Port:4, Channel:6*/
  P47 = 0x47,    /**< Port:4, Channel:7*/
  P48 = 0x48,    /**< Port:4, Channel:8*/
  P49 = 0x49,    /**< Port:4, Channel:9*/
  P50 = 0x50,    /**< Port:5, Channel:0*/
  P51 = 0x51,    /**< Port:5, Channel:1*/
  P52 = 0x52,    /**< Port:5, Channel:2*/
  P5D = 0x5D,    /**< Port:5, Channel:D*/
  P5E = 0x5E,    /**< Port:5, Channel:E*/
  P5F = 0x5F,    /**< Port:5, Channel:F*/
  P60 = 0x60,    /**< Port:6, Channel:0*/
  P61 = 0x61,    /**< Port:6, Channel:1*/
  P62 = 0x62,    /**< Port:6, Channel:2*/
  P63 = 0x63,    /**< Port:6, Channel:3*/
  P64 = 0x64,    /**< Port:6, Channel:4*/
  P65 = 0x65,    /**< Port:6, Channel:5*/
  P6E = 0x6E,    /**< Port:6, Channel:E*/
  P70 = 0x70,    /**< Port:7, Channel:0*/
  P71 = 0x71,    /**< Port:7, Channel:1*/
  P72 = 0x72,    /**< Port:7, Channel:2*/
  P73 = 0x73,    /**< Port:7, Channel:3*/
  P74 = 0x74,    /**< Port:7, Channel:4*/
  P75 = 0x75,    /**< Port:7, Channel:5*/
  P76 = 0x76,    /**< Port:7, Channel:6*/
  P77 = 0x77,    /**< Port:7, Channel:7*/
  P78 = 0x78,    /**< Port:7, Channel:8*/
  P79 = 0x79,    /**< Port:7, Channel:9*/
  P7A = 0x7A,    /**< Port:7, Channel:A*/
  P7B = 0x7B,    /**< Port:7, Channel:B*/
  P7C = 0x7C,    /**< Port:7, Channel:C*/
  P7D = 0x7D,    /**< Port:7, Channel:D*/
  P7E = 0x7E,    /**< Port:7, Channel:E*/
  P80 = 0x80,    /**< Port:8, Channel:0*/
  P81 = 0x81,    /**< Port:8, Channel:1*/
  P82 = 0x82,    /**< Port:8, Channel:2*/
  P83 = 0x83,    /**< Port:8, Channel:3*/
  P90 = 0x90,    /**< Port:9, Channel:0*/
  P91 = 0x91,    /**< Port:9, Channel:1*/
  P92 = 0x92,    /**< Port:9, Channel:2*/
  P93 = 0x93,    /**< Port:9, Channel:3*/
  P94 = 0x94,    /**< Port:9, Channel:4*/
  P95 = 0x95,    /**< Port:9, Channel:5*/
  PA0 = 0xA0,    /**< Port:A, Channel:0*/
  PA1 = 0xA1,    /**< Port:A, Channel:1*/
  PA2 = 0xA2,    /**< Port:A, Channel:2*/
  PA3 = 0xA3,    /**< Port:A, Channel:3*/
  PA4 = 0xA4,    /**< Port:A, Channel:4*/
  PA5 = 0xA5,    /**< Port:A, Channel:5*/
  PA6 = 0xA6,    /**< Port:A, Channel:6*/
  PA7 = 0xA7,    /**< Port:A, Channel:7*/
  PA8 = 0xA8,    /**< Port:A, Channel:8*/
  PA9 = 0xA9,    /**< Port:A, Channel:9*/
  PAA = 0xAA,    /**< Port:A, Channel:A*/
  PAB = 0xAB,    /**< Port:A, Channel:B*/
  PAC = 0xAC,    /**< Port:A, Channel:C*/
  PAD = 0xAD,    /**< Port:A, Channel:D*/
  PAE = 0xAE,    /**< Port:A, Channel:E*/
  PAF = 0xAF,    /**< Port:A, Channel:F*/
  PB0 = 0xB0,    /**< Port:B, Channel:0*/
  PB1 = 0xB1,    /**< Port:B, Channel:1*/
  PB2 = 0xB2,    /**< Port:B, Channel:2*/
  PB3 = 0xB3,    /**< Port:B, Channel:3*/
  PB4 = 0xB4,    /**< Port:B, Channel:4*/
  PB5 = 0xB5,    /**< Port:B, Channel:5*/
  PB6 = 0xB6,    /**< Port:B, Channel:6*/
  PB7 = 0xB7,    /**< Port:B, Channel:7*/
  PC0 = 0xC0,    /**< Port:C, Channel:0*/
  PC1 = 0xC1,    /**< Port:C, Channel:1*/
  PC2 = 0xC2,    /**< Port:C, Channel:2*/
  PC3 = 0xC3,    /**< Port:C, Channel:3*/
  PC4 = 0xC4,    /**< Port:C, Channel:4*/
  PC5 = 0xC5,    /**< Port:C, Channel:5*/
  PC6 = 0xC6,    /**< Port:C, Channel:6*/
  PC7 = 0xC7,    /**< Port:C, Channel:7*/
  PC8 = 0xC8,    /**< Port:C, Channel:8*/
  PC9 = 0xC9,    /**< Port:C, Channel:9*/
  PCA = 0xCA,    /**< Port:C, Channel:A*/
  PCB = 0xCB,    /**< Port:C, Channel:B*/
  PCC = 0xCC,    /**< Port:C, Channel:C*/
  PCD = 0xCD,    /**< Port:C, Channel:D*/
  PCE = 0xCE,    /**< Port:C, Channel:E*/
  PCF = 0xCF,    /**< Port:C, Channel:F*/
  PD0 = 0xD0,    /**< Port:D, Channel:0*/
  PD1 = 0xD1,    /**< Port:D, Channel:1*/
  PD2 = 0xD2,    /**< Port:D, Channel:2*/
  PE0 = 0xE0,    /**< Port:E, Channel:0*/
  PE2 = 0xE2,    /**< Port:E, Channel:2*/
  PE3 = 0xE3,    /**< Port:E, Channel:3*/
  PF0 = 0xF0,    /**< Port:F, Channel:0*/
  PF1 = 0xF1,    /**< Port:F, Channel:1*/
  PF2 = 0xF2,    /**< Port:F, Channel:2*/
  PF3 = 0xF3,    /**< Port:F, Channel:3*/
  PF4 = 0xF4,    /**< Port:F, Channel:4*/
  PF5 = 0xF5,    /**< Port:F, Channel:5*/
  PF6 = 0xF6,    /**< Port:F, Channel:6*/
  PF7 = 0xF7,     /**< Port:F, Channel:7*/
  MAXCHANNEL = 0x100
} GpioChannel_t; /**< Port:i, Channel:o*/
/**
* Defines the possible modes of the channel Input/Output
*/
typedef enum GpioDir_enu
{
  GPIO_INPUT,  /*< Used to set channel as input */
  GPIO_OUTPUT, /*< Used to set channel as output */
} GpioDir_t;
/**
* Defines if GPIO is analog input or digital port
*/
typedef enum GpioDigAna_enu
{
  GPIO_DIG,  /*< Used to set channel as digital */
  GPIO_ANA,  /*< Used to set channel as analog */
} GpioDigAna_t;
/**
* Defines the possible states of the channel pull-ups
*/
typedef enum GpioResistor_enu
{
  GPIO_PULLUP_DISABLED, /*< Used to disable the internal pull-ups */
  GPIO_PULLUP_ENABLED,  /*< Used to enable the internal pull-ups */
  GPIO_MAX_RESISTOR     /*< Resistor states should be below this value
*/
} GpioResistor_t;
/**********************************************************************
* Function Prototypes
**********************************************************************/



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
void GPIO_ChannelDigAna(const GpioChannel_t channel, const GpioDigAna_t mode);

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
void GPIO_ChannelMode(const GpioChannel_t channel, const GpioDir_t mode);

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
GpioPinState_t GPIO_ChannelRead(const GpioChannel_t channel);

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
void GPIO_ChannelWrite(const GpioChannel_t channel, const GpioPinState_t pin);


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
void GPIO_ChannelToggle(const GpioChannel_t channel);



#endif /* INCLUDES_HAL_FM4_GPIO_H_*/

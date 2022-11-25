#include "mcu.h"
#include "HAL_FM4_i2c.h"

static void DonaldDelay( volatile uint32_t nCount)
{ 
  for (; nCount > 0; nCount--);
}

void I2C_init(void) 
{   
  bFM4_GPIO_EPFR07_SCK2B1 = 1u;                  // GPIO pin P3B used for I2C clock
  bFM4_GPIO_PFR3_PB = 1u;
  bFM4_GPIO_EPFR07_SOT2B1 = 1u;                  // GPIO pin P3A used for I2C data
  bFM4_GPIO_PFR3_PA = 1u;
  FM4_GPIO->PZR3_f.PA = 1u;                      // I2C data pin pseudo open drain
  FM4_MFS2->BGR  = 100000000ul / 400000ul - 1ul; // I2C mode 400k Bit/s @ 100 MHz
  FM4_MFS2->SMR |= 0x80u;       	               // operate MFS2 in mode 4 (I2C)
  bFM4_MFS2_I2C_SMR_RIE = 0u;	                   // disable receive interrupts
  bFM4_MFS2_I2C_SMR_TIE = 0u;	                   // disable transmit interrupts
  FM4_MFS2->SCR |= 0x80u;                        // reset MFS2 (UPCL = 1)
}


void I2C_write(uint8_t device_address, uint8_t register_address, uint8_t cmd) 
{
  FM4_MFS2->ISBA = 0x00u;	                     // disable slave address detection
  FM4_MFS2->ISMK = 0x00;                         // clear slave mask
  bFM4_MFS2_I2C_ISMK_EN = 0x01; 
  FM4_MFS2->TDR = (device_address << 1)|0x00;    // load codec device address into transmit data register
  FM4_MFS2->IBCR = 0x80u;                        // select master mode
  while(!(bFM4_MFS2_I2C_IBCR_INT)) {}            // wait for interrupt flag, i.e. transmission complete
  FM4_MFS2->TDR = (register_address);            // load codec register address into transmit data register  
  bFM4_MFS2_I2C_IBCR_ACKE = 1u;                  // enable acknowledgment
  bFM4_MFS2_I2C_IBCR_WSEL = 1u;                  // set wait selection bit
  bFM4_MFS2_I2C_IBCR_INT = 0u;                   // clear interrupt flag
  while(!(FM4_MFS2->IBCR & 0x01u)) {}            // wait for interrupt flag, i.e. transmission complete	
  FM4_MFS2->TDR = (cmd);                         // load codec register command into transmit data register
  bFM4_MFS2_I2C_IBCR_ACKE = 1u;                  // enable acknowledgment
  bFM4_MFS2_I2C_IBCR_WSEL = 1u;                  // set wait selection bit
  bFM4_MFS2_I2C_IBCR_INT = 0u;                   // clear interrupt flag
  while(!(FM4_MFS2->IBCR & 0x01u)) {}            // wait for interrupt flag, i.e. transmission complete
  FM4_MFS2->IBCR = 0x20u;                        // enable acknowledge
  DonaldDelay(10000);                            // delay 
}


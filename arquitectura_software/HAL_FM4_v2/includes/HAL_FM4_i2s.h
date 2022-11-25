#ifndef __HAL_FM4_I2S__
#define __HAL_FM4_I2S__

#include <stdint.h>

void I2S_init(char fs);
uint32_t I2S_rx(void);
void I2S_tx(uint32_t c);
void I2S_start(void);

void I2S_loopback_enable (void);
void I2S_loopback_disable (void);


#endif

#ifndef __HAL_FM4_I2C__
#define __HAL_FM4_I2C__

void I2C_init(void);
void I2C_write(uint8_t device_address, uint8_t register_address, uint8_t cmd);



#endif

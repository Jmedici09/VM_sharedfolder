#ifndef I2C0_H
#define I2C0_H

#include <stdbool.h>
#include <stdint.h>

void initialize_i2c0();
_Bool i2c0_read_byte(uint8_t device, uint8_t reg, uint8_t *data);
_Bool i2c0_write_byte(uint8_t device, uint8_t reg, uint8_t data);

#endif
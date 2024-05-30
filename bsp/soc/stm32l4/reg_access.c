#include <stdint.h>

void set_bit(uint32_t *val, uint8_t index)
{
    *val |= (1 << index);
}

void clear_bit(uint32_t *val,uint8_t index)
{
    *val &= (0 << index);
}
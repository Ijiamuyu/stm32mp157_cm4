#ifndef __SOC_REG_ACCESS_H__
#define __SOC_REG_ACCESS_H__

#include <stdint.h>

#define read_mreg64(addr) (*(volatile uint64_t *)(addr))

#define write_mreg64(addr, val) (*(volatile uint64_t *)(addr) = (uint64_t)(val))

#define read_mreg32(addr) (*(volatile uint32_t *)(addr))

#define write_mreg32(addr, val) (*(volatile uint32_t *)(addr) = (uint32_t)(val))

#define read_mreg16(addr) (*(volatile uint16_t *)(addr))

#define write_mreg16(addr, val) (*(volatile uint16_t *)(addr) = (uint16_t)(val))

#define read_mreg8(addr) (*(volatile uint8_t *)(addr))

#define write_mreg8(addr, val) (*(volatile uint8_t *)(addr) = (uint8_t)(val))

#endif /* __SOC_REG_ACCESS_H__ */

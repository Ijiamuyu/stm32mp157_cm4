#ifndef __SOC_INIT_H__
#define __SOC_INIT_H__

#include <stdint.h>
#include "st_uart.h"
#include "soc_map.h"

UartCfg uart0_cfg = {
    .base      = USART1_BASE,
    .baud      = 115200,
    .clk       = 80000000,
    .parity    = UART_PARITY_NONE,
    .data_len  = UART_8BITS,
    .mst_mode  = UART_MSB_FIRST,
    .stop_bits = ONE_STOP_BITS,
};

#endif /* __SOC_INIT_H__ */

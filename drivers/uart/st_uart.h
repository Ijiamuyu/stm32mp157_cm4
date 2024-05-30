#ifndef __ST_UART_H__
#define __ST_UART_H__

#include <stdint.h>

typedef enum UartDateLen {
    UART_9BITS,
    UART_8BITS,
    UART_7BITS,
} UartDateLen;

typedef enum UartParity {
    UART_ODD,
    UART_EVEN,
    UART_PARITY_NONE,
} UartParity;

typedef enum UartStopBits {
    ZERO_POINT_FIVE_STOP_BITS,
    ONE_STOP_BITS,
    ONE_POINT_FIVE_STOP_BITS,
    TWO_STOP_BITS,
} UartStopBits;

typedef enum UartMode {
    UART_MSB_FIRST,
    UART_LSB_FIRST,
} UartMode;

typedef struct UartCfg {
    uint32_t base;
    uint32_t clk;
    uint32_t baud;
    UartDateLen data_len;
    UartParity parity;
    UartStopBits stop_bits;
    UartMode mst_mode;
} UartCfg;

int uart_init(UartCfg *cfg);

void uart_tx_send(UartCfg *cfg, uint8_t *buf, uint32_t size);

#endif /* __ST_UART_H__ */

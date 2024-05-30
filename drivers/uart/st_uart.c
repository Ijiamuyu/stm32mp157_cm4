#include "st_uart.h"
#include "reg_access.h"

#define USART_CR1 0x0
#define USART_CR2 0x4
#define USART_CR3 0x8
#define USART_BRR 0xC
#define USART_GTPR 0x10
#define USART_RTOR 0x14
#define USART_RQR 0x18
#define USART_ISR 0x1C
#define USART_ICR 0x20
#define USART_RDR 0x24
#define USART_TDR 0x28

static void write_reg(UartCfg *cfg, uint32_t off, uint32_t val)
{
    write_mreg32(cfg->base + off, val);
}

static uint32_t read_reg(UartCfg *cfg, uint32_t off)
{
    return read_mreg32(cfg->base + off);
}

static void uart_enable(UartCfg *cfg, uint8_t enable)
{
    volatile uint32_t val = read_reg(cfg, USART_CR1);

    if (enable) {
        set_bit(val, 0);
    } else {
        clear_bit(val, 0);
    }
    write_reg(cfg, USART_CR1, val);
}

static void uart_clk_enable(UartCfg *cfg, uint8_t enable)
{
    volatile uint32_t val = read_reg(cfg, USART_CR2);

    if (enable) {
        set_bit(val, 11);
    } else {
        clear_bit(val, 11);
    }
    write_reg(cfg, USART_CR2, val);
}

static void tx_enable(UartCfg *cfg, uint8_t enable)
{
    volatile uint32_t val = read_reg(cfg, USART_CR1);

    if (enable) {
        set_bit(val, 3);
    } else {
        clear_bit(val, 3);
    }
    write_reg(cfg, USART_CR1, val);
}

static void rx_enable(UartCfg *cfg, uint8_t enable)
{
    volatile uint32_t val = read_reg(cfg, USART_CR1);

    if (enable) {
        set_bit(val, 2);
    } else {
        clear_bit(val, 2);
    }
    write_reg(cfg, USART_CR1, val);
}

static void cfg_data_length(UartCfg *cfg)
{
    volatile uint32_t val = read_reg(cfg, USART_CR1);

    switch (cfg->data_len) {
    case UART_9BITS:
        clear_bit(&val, 28);
        set_bit(&val, 12);
        break;
    case UART_8BITS:
        clear_bit(&val, 28);
        clear_bit(&val, 12);
        break;
    case UART_7BITS:
        set_bit(&val, 28);
        clear_bit(&val, 12);
        break;
    default:
        clear_bit(&val, 28);
        clear_bit(&val, 12);
    }
    write_reg(cfg, USART_CR1, val);
}

static void cfg_parity(UartCfg *cfg)
{
    volatile uint32_t val = read_reg(cfg, USART_CR1);

    switch (cfg->parity) {
    case UART_ODD:
        set_bit(&val, 10);
        set_bit(&val, 9);
        break;
    case UART_EVEN:
        set_bit(&val, 10);
        clear_bit(&val, 9);
        break;
    case UART_PARITY_NONE:
        clear_bit(&val, 10);
        break;
    default:
        clear_bit(&val, 10);
    }
    write_reg(cfg, USART_CR1, val);
}

static void cfg_msb_mode(UartCfg *cfg)
{
    volatile uint32_t val = read_reg(cfg, USART_CR2);

    switch (cfg->mst_mode) {
    case UART_MSB_FIRST:
        set_bit(&val, 19);
        break;
    case UART_LSB_FIRST:
        clear_bit(&val, 19);
        break;
    default:
        clear_bit(&val, 19);
    }
    write_reg(cfg, USART_CR2, val);
}

static void cfg_stop_bits(UartCfg *cfg)
{
    volatile uint32_t val = read_reg(cfg, USART_CR2);

    switch (cfg->stop_bits) {
    case ZERO_POINT_FIVE_STOP_BITS:
        clear_bit(&val, 13);
        set_bit(&val, 12);
        break;
    case ONE_STOP_BITS:
        clear_bit(&val, 13);
        clear_bit(&val, 12);
        break;
    case ONE_POINT_FIVE_STOP_BITS:
        set_bit(&val, 13);
        set_bit(&val, 12);
        break;
    case TWO_STOP_BITS:
        set_bit(&val, 13);
        clear_bit(&val, 12);
        break;
    default:
        clear_bit(&val, 13);
        clear_bit(&val, 12);
    }
    write_reg(cfg, USART_CR2, val);
}

static void cfg_baud(UartCfg *cfg)
{
    volatile uint16_t val = 0;

    val = cfg->clk / cfg->baud;
    write_reg(cfg, USART_BRR, val);
}

static void write_fifo(UartCfg *cfg, uint8_t val)
{
    write_reg(cfg, USART_TDR, val);
}

static uint8_t read_fifo(UartCfg *cfg)
{
    return read_reg(cfg, USART_RDR);
}

static uint8_t tx_empty(UartCfg *cfg)
{
    volatile uint32_t val;

    val = read_reg(cfg, USART_ISR);
    if (val & 0x80)
        return 1;
    else
        return 0;
}

static void uart_send_byte(UartCfg *cfg, uint8_t c)
{
    while (!tx_empty(cfg))
        ;
    write_fifo(cfg, c);
}

void uart_tx_send(UartCfg *cfg, uint8_t *buf, uint32_t size)
{
    while (size--) {
        uart_send_byte(cfg, *buf++);
    }
}

int uart_init(UartCfg *cfg)
{
    int ret = 0;

    cfg_data_length(cfg);
    cfg_msb_mode(cfg);
    cfg_parity(cfg);
    cfg_stop_bits(cfg);
    cfg_baud(cfg);
    tx_enable(cfg, 1);
    rx_enable(cfg, 1);
    uart_clk_enable(cfg, 1);
    uart_enable(cfg, 1);
    return ret;
}

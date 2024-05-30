#include "reg_access.h"
#include "st_gpio.h"
#include "soc_map.h"

#define GPIOX_MODER 0x0
#define GPIOX_OTYPER 0x4
#define GPIOX_OSPEEDR 0x8
#define GPIOX_PUPDR 0xC
#define GPIOX_IDR 0x10
#define GPIOX_ODR 0x14
#define GPIOX_BSRR 0x18
#define GPIOX_LCKR 0x1C
#define GPIOX_AFRL 0x20
#define GPIOX_AFRH 0x24
#define GPIOX_BRR 0x28
#define GPIOX_ASCR 0x2C

// map gpio group to base
static uint32_t gpio_map[9][2] = {
    { GPIOA, GPIOA_BASE }, { GPIOB, GPIOB_BASE }, { GPIOC, GPIOC_BASE },
    { GPIOD, GPIOD_BASE }, { GPIOE, GPIOE_BASE }, { GPIOF, GPIOF_BASE },
    { GPIOG, GPIOG_BASE }, { GPIOH, GPIOH_BASE }, { GPIOI, GPIOI_BASE },
};

static inline void write_reg(GpioGroup group, uint32_t off, uint32_t val)
{
    write_mreg32(gpio_map[group][1] + off, val);
}

static inline uint32_t read_reg(GpioGroup group, uint32_t off)
{
    return read_mreg32(gpio_map[group][1] + off);
}

static void cfg_mode(GpioGroup group, GpioCfg *cfg, uint8_t pin)
{
    volatile uint32_t val = read_reg(group, GPIOX_MODER);

    switch (cfg->mode) {
    case INPUT_MODE:
        clear_bit(&val, pin * 2 + 1);
        clear_bit(&val, pin * 2);
        break;
    case OUTPUT_MODE:
        clear_bit(&val, pin * 2 + 1);
        set_bit(&val, pin * 2);
        break;
    case ALTERNATE_FUNCTION_MODE:
        set_bit(&val, pin * 2 + 1);
        clear_bit(&val, pin * 2);
        break;
    case ANALOG_MODE:
        set_bit(&val, pin * 2 + 1);
        set_bit(&val, pin * 2);
        break;
    default:
        break;
    }
    write_reg(group, GPIOX_MODER, val);
}

static void cfg_output_type(GpioGroup group, GpioCfg *cfg, uint8_t pin)
{
    volatile uint32_t val = read_reg(group, GPIOX_OTYPER);

    if (cfg->mode == INPUT_MODE) {
        return;
    }
    switch (cfg->output_type) {
    case OUTPUT_PP:
        clear_bit(&val, pin);
        break;
    case OUTPUT_OPENDRAIN:
        set_bit(&val, pin);
        break;
    default:
        break;
    }
    write_reg(group, GPIOX_OTYPER, val);
}

static void cfg_input_type(GpioGroup group, GpioCfg *cfg, uint8_t pin)
{
    volatile uint32_t val = read_reg(group, GPIOX_PUPDR);

    if (cfg->mode == OUTPUT_MODE) {
        clear_bit(&val, pin * 2 + 1);
        clear_bit(&val, pin * 2);
    } else {
        switch (cfg->input_typr) {
        case PULL_UP:
            clear_bit(&val, pin * 2 + 1);
            set_bit(&val, pin * 2);
            break;
        case PULL_DOWN:
            set_bit(&val, pin * 2 + 1);
            clear_bit(&val, pin * 2);
            break;
        default:
            break;
        }
    }
    write_reg(group, GPIOX_PUPDR, val);
}

static void cfg_speed(GpioGroup group, GpioCfg *cfg, uint8_t pin)
{
    volatile uint32_t val = read_reg(group, GPIOX_OSPEEDR);

    switch (cfg->speed) {
    case LOW_SPEED:
        clear_bit(&val, pin * 2 + 1);
        clear_bit(&val, pin * 2);
        break;
    case MEDIUM_SPEED:
        clear_bit(&val, pin * 2 + 1);
        set_bit(&val, pin * 2);
        break;
    case HIGH_SPEED:
        set_bit(&val, pin * 2 + 1);
        clear_bit(&val, pin * 2);
        break;
    case VERY_HIGH_SPEED:
        set_bit(&val, pin * 2 + 1);
        set_bit(&val, pin * 2);
        break;
    default:
        break;
    }
    write_reg(group, GPIOX_OSPEEDR, val);
}

int gpio_read(GpioGroup group, uint8_t pin)
{
    volatile uint32_t val = read_reg(group, GPIOX_IDR);

    if (val & (0x1 << pin))
        return 1;
    else
        return 0;
}

void gpio_write(GpioGroup group, uint8_t pin, uint8_t val)
{
    volatile uint32_t origin = read_reg(group, GPIOX_ODR);

    if (val)
        set_bit(&origin, pin);
    else
        clear_bit(&origin, pin);

    write_reg(group, GPIOX_ODR, origin);
}

void gpio_init(GpioGroup group, uint8_t pin, GpioCfg *cfg)
{
    cfg_mode(group,cfg,pin);
    switch(cfg->mode)
    {
        case INPUT_MODE:
            cfg_input_type(group,cfg,pin);
            break;
        case OUTPUT_MODE:
            cfg_input_type(group,cfg,pin);
        default:
            break;
    }
    cfg_speed(group,cfg,pin);
}

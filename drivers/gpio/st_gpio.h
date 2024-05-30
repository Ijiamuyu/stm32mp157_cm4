#ifndef __ST_GPIO_H__
#define __ST_GPIO_H__

#include <stdint.h>

typedef enum GpioGroup {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
    GPIOI,
} GpioGroup;

typedef enum GpioMode {
    INPUT_MODE,
    OUTPUT_MODE,
    ALTERNATE_FUNCTION_MODE, // pinmux
    ANALOG_MODE,
} GpioMode;

typedef enum GpioOutputTyper {
    OUTPUT_PP,
    OUTPUT_OPENDRAIN,
} GpioOutputTyper;

typedef enum GpioInputType {
    PULL_UP,
    PULL_DOWN,
} GpioInputType;

typedef enum GpioSpeed {
    LOW_SPEED,
    MEDIUM_SPEED,
    HIGH_SPEED,
    VERY_HIGH_SPEED,
} GpioSpeed;

typedef struct GpioCfg {
    uint32_t base;
    GpioMode mode;
    GpioOutputTyper output_type;
    GpioInputType input_typr;
    GpioSpeed speed;
} GpioCfg;

int gpio_read(GpioGroup group, uint8_t pin);
void gpio_write(GpioGroup group, uint8_t pin, uint8_t val);
void gpio_init(GpioGroup group, uint8_t pin, GpioCfg *cfg);

#endif /* __ST_GPIO_H__ */

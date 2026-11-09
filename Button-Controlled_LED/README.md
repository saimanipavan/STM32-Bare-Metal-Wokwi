# STM32 Bare-Metal GPIO Button-Controlled LED

## Project Overview

This project demonstrates how to read a digital input from a GPIO pin and control an LED based on the input state using bare-metal C programming.

The STM32 GPIO registers are accessed directly through memory-mapped addresses without using HAL or Arduino libraries.

A button is connected to PA5, and an LED is connected to PA6.

When the button is pressed, the LED turns ON. When the button is released, the LED turns OFF.

## Objectives

- Understand GPIO input and output configuration.
- Enable the GPIOA peripheral clock using RCC.
- Read digital input using the GPIO Input Data Register (IDR).
- Control an LED using the GPIO Bit Set/Reset Register (BSRR).
- Understand bitwise operations and register access.
- Implement button-controlled LED operation.

## Hardware / Simulation

- STM32 microcontroller
- Wokwi simulator
- Push button
- LED
- Current-limiting resistor

## GPIO Pin Configuration

| Pin | Function |
|---|---|
| PA5 | Button input |
| PA6 | LED output |

## Register Configuration

### 1. RCC — GPIO Clock Enable

```c
#define RCC_BASE 0x40021000UL
#define RCC_IOPENR (*(volatile uint32_t*) (RCC_BASE+0x34UL))
```

The RCC peripheral controls the clock supply to GPIO peripherals.

```c
SET_BIT(RCC_IOPENR, 0);
```

This enables the GPIOA peripheral clock.

### 2. GPIOA_MODER — GPIO Mode Register

```c
#define GPIOA_MODER (*(volatile uint32_t*) (GPIOA_BASE+0x00UL))
```

Each GPIO pin uses two bits in the MODER register.

| Mode bits | Configuration |
|---|---|
| 00 | Input |
| 01 | Output |
| 10 | Alternate function |
| 11 | Analog |

PA5 is configured as input, and PA6 is configured as output.

### 3. GPIOA_IDR — Input Data Register

```c
#define GPIOA_IDR (*(volatile uint32_t*) (GPIOA_BASE+0x10UL))
```

The IDR register reads the logic state of the GPIO pins.

```c
READ_BIT(GPIOA_IDR, 5)
```

- Returns `1` when PA5 is HIGH.
- Returns `0` when PA5 is LOW.

### 4. GPIOA_BSRR — Bit Set/Reset Register

```c
#define GPIOA_BSRR (*(volatile uint32_t*) (GPIOA_BASE+0x18UL))
```

The BSRR register is used to control GPIO output pins.

```c
SET_BIT(GPIOA_BSRR, 6);       // PA6 HIGH
SET_BIT(GPIOA_BSRR, 6+16);    // PA6 LOW
```

The lower 16 bits set output pins, and the upper 16 bits reset output pins.

## Program Operation

The firmware continuously monitors PA5.

1. Enable GPIOA clock.
2. Configure PA5 as input.
3. Configure PA6 as output.
4. Read the button state using IDR.
5. If PA5 is HIGH, set PA6 HIGH.
6. If PA5 is LOW, reset PA6 LOW.
7. Repeat continuously.

## Key Concepts Learned

- GPIO input and output configuration
- RCC peripheral clock enable
- Memory-mapped register programming
- GPIO IDR register
- GPIO BSRR register
- Bitwise operations
- Digital input polling
- Bare-metal embedded C

## Future Improvements

- Add internal pull-up and pull-down configuration.
- Implement button debouncing.
- Control multiple LEDs using multiple buttons.
- Implement interrupt-based button detection using EXTI.
- Add UART-based status monitoring.

## Author

Mani

Part of my STM32 Bare-Metal Firmware Development using C and Wokwi learning journey.
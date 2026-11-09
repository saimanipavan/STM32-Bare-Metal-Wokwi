# STM32 Bare-Metal GPIO LED Control using Registers

## Project Overview

This project demonstrates GPIO configuration and LED control on an STM32 microcontroller using bare-metal C programming.

The GPIO peripheral is configured by directly accessing memory-mapped registers without using STM32 HAL or Arduino libraries.

Two GPIO pins, PA5 and PA6, are configured as output pins. The LEDs are controlled using the GPIO Bit Set/Reset Register (BSRR).

## Objectives

- Understand memory-mapped register access.
- Enable the GPIOA peripheral clock using RCC.
- Configure GPIO pins as output.
- Understand `volatile` and register pointers.
- Control GPIO pins using the BSRR register.
- Implement a software delay using a busy-wait loop.

## Hardware / Simulation

- STM32 microcontroller
- Wokwi simulator
- Two LEDs
- Current-limiting resistors
- STM32 GPIO pins PA5 and PA6

## Register Configuration

### 1. RCC — GPIO Clock Enable

```c
#define RCC_BASE 0x40021000UL
#define RCC_IOPENR (*(volatile uint32_t*) (RCC_BASE+0x34UL))
```

The RCC (Reset and Clock Control) peripheral manages the clocks of the microcontroller peripherals.

`RCC_IOPENR` enables the GPIO port clocks.

```c
SET_BIT(RCC_IOPENR, 0);
```

Bit 0 enables the GPIOA peripheral clock.

### 2. GPIOA_MODER — GPIO Mode Register

```c
#define GPIOA_BASE 0x50000000UL
#define GPIOA_MODER (*(volatile uint32_t*) (GPIOA_BASE+0x00UL))
```

Each GPIO pin uses two bits in the MODER register.

| Mode bits | Configuration |
|---|---|
| 00 | Input |
| 01 | General-purpose output |
| 10 | Alternate function |
| 11 | Analog |

For PA5:

```c
CLEAR_BIT(GPIOA_MODER, 11);
CLEAR_BIT(GPIOA_MODER, 10);
SET_BIT(GPIOA_MODER, 10);
```

For PA6:

```c
CLEAR_BIT(GPIOA_MODER, 13);
CLEAR_BIT(GPIOA_MODER, 12);
SET_BIT(GPIOA_MODER, 12);
```

Both pins are configured as general-purpose outputs.

### 3. GPIOA_BSRR — Bit Set/Reset Register

```c
#define GPIOA_BSRR (*(volatile uint32_t*) (GPIOA_BASE+0x18UL))
```

The BSRR register allows GPIO output pins to be set or reset.

| Operation | Register bit |
|---|---|
| Set PA5 | Bit 5 |
| Reset PA5 | Bit 21 |
| Set PA6 | Bit 6 |
| Reset PA6 | Bit 22 |

Example:

```c
GPIOA_BSRR = (1U << 5);       // PA5 HIGH
GPIOA_BSRR = (1U << 6);       // PA6 HIGH
GPIOA_BSRR = (1U << (5+16));  // PA5 LOW
GPIOA_BSRR = (1U << (6+16));  // PA6 LOW
```

## LED Control Sequence

The program continuously executes the following sequence:

1. PA5 LED turns ON.
2. Wait for a software delay.
3. PA6 LED turns ON.
4. Wait for a software delay.
5. PA5 LED turns OFF.
6. Wait for a software delay.
7. PA6 LED turns OFF.
8. Repeat.

## Software Delay

```c
static void wait_time(volatile uint32_t time)
{
    while(time--)
    {
    }
}
```

A simple busy-wait loop is used to create a delay.

The delay duration depends on the CPU clock frequency and compiler optimization settings. This is not a precise timing method.

## Key Concepts Learned

- Memory-mapped I/O
- RCC peripheral clock control
- GPIO register configuration
- Bitwise operators
- Register pointers
- `volatile` keyword
- GPIO BSRR set/reset operations
- Bare-metal embedded C programming

## Future Improvements

- Implement GPIO configuration using reusable functions.
- Add button-controlled LED operation.
- Implement hardware timer-based delays.
- Add interrupt-based GPIO control.
- Develop UART-based LED control.

## Author

Mani

Part of my STM32 Bare-Metal Firmware Development using C and Wokwi learning journey.
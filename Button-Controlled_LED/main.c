#include <stdint.h>

#define RCC_BASE 0x40021000UL
#define RCC_IOPENR (*(volatile uint32_t*) (RCC_BASE+0x34UL))

#define GPIOA_BASE 0x50000000UL
#define GPIOA_MODER (*(volatile uint32_t*) (GPIOA_BASE+0x00UL))
//#define GPIOA_OTYPER (*(volatile uint32_t*) (GPIOA_BASE+0x04UL))
#define GPIOA_IDR (*(volatile uint32_t*) (GPIOA_BASE+0x10UL))
//#define GPIOA_ODR (*(volatile uint32_t*) (GPIOA_BASE+0x14UL))
#define GPIOA_BSRR (*(volatile uint32_t*) (GPIOA_BASE+0x18UL))



#define SET_BIT(REG, BIT)       ((REG) |=  (1U << (BIT)))
#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(1U << (BIT)))
//#define TOGGLE_BIT(REG, BIT)    ((REG) ^=  (1U << (BIT)))
#define READ_BIT(REG, BIT)      (((REG) >> (BIT)) & 1U)

static void wait_time(volatile uint32_t time){
  while(time--){
  }
}

int main(void){
  SET_BIT(RCC_IOPENR, 0);
  CLEAR_BIT(GPIOA_MODER,11);
  CLEAR_BIT(GPIOA_MODER,10);
  CLEAR_BIT(GPIOA_MODER,13);
  CLEAR_BIT(GPIOA_MODER,12);
  SET_BIT(GPIOA_MODER,12);

  while(1){
    if (READ_BIT(GPIOA_IDR,5)){
      SET_BIT(GPIOA_BSRR,6);
    }
    else{
      SET_BIT(GPIOA_BSRR,6+16);
    }
  }
}
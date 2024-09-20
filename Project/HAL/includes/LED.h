
#ifndef HAL_INCLUDES_LED_H_
#define HAL_INCLUDES_LED_H_

#include "Stm32_F103C6_gpio_driver.h"


#define R_LED	GPIO_PIN_0
#define G_LED	GPIO_PIN_11

#define LED_PORT	GPIOA


void LED_Init(void);
void LED_ON(uint32_t LED);
void LED_OFF(uint32_t LED);

#endif /* HAL_INCLUDES_LED_H_ */

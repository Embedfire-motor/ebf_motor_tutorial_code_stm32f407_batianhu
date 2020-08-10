#ifndef __BSP_GENERAL_TIM_H
#define	__BSP_GENERAL_TIM_H

#include "stm32f4xx.h"
/*�궨��*/

#define GENERAL_TIM                        	TIM2
#define GENERAL_TIM_GPIO_AF                 GPIO_AF1_TIM2
#define GENERAL_TIM_CLK_ENABLE()  					__TIM2_CLK_ENABLE()


/*PWM����*/
#define GENERAL_TIM_CH1_GPIO_PORT           GPIOF
#define GENERAL_TIM_CH1_PIN                 GPIO_PIN_6

#define GENERAL_TIM_CH2_GPIO_PORT           GPIOF
#define GENERAL_TIM_CH2_PIN                 GPIO_PIN_7

#define GENERAL_TIM_CH3_GPIO_PORT           GPIOF
#define GENERAL_TIM_CH3_PIN                 GPIO_PIN_8

#define GENERAL_TIM_CH4_GPIO_PORT           GPIOC
#define GENERAL_TIM_CH4_PIN                 GPIO_PIN_3

extern void TIMx_Configuration(void);
extern void TIM2_SetPWM_pulse(int channel,int compare);

#endif


/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-xx-xx
  * @brief   PWM���ƽǶ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./key/bsp_key.h" 
#include "./led/bsp_led.h"
#include "./Encoder/bsp_encoder.h"
#include "./pid/bsp_pid.h"
#include "./tim/bsp_basic_tim.h"
#include "./stepper/bsp_stepper_ctrl.h"

extern _pid pid;
extern int pid_status;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{
	/* ��ʼ��ϵͳʱ��Ϊ168MHz */
	SystemClock_Config();
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
	DEBUG_USART_Config();
	printf("��ӭʹ��Ұ�� ��������� ������� �ٶȱջ����� λ��ʽPID����\r\n");
	printf("���°���1����Ŀ��ֵ������2����Ŀ��ֵ\r\n");	
  printf("����������ʹ��PID��������\r\n");	
  /* ��ʼ��ʱ��� */
  HAL_InitTick(5);
	/*�����жϳ�ʼ��*/
	Key_GPIO_Config();	
	/*led��ʼ��*/
	LED_GPIO_Config();
  /* ��ʼ��������ʱ����ʱ��20ms����һ���ж� */
	TIMx_Configuration();
  /* �������ӿڳ�ʼ�� */
	Encoder_Init();
  /*���������ʼ��*/
	stepper_Init();
  /* �ϵ�Ĭ��ֹͣ��� */
  Set_Stepper_Stop();
  /* PID�㷨������ʼ�� */
  PID_param_init();	

  /* Ŀ��λ��ת��Ϊ����������������ΪpidĿ��ֵ */
  pid.target_val = TARGET_DISP * ENCODER_TOTAL_RESOLUTION;
	Set_Stepper_Start();    
	
#if PID_ASSISTANT_EN
  int Temp = pid.target_val;    // ��λ����Ҫ����������ת��һ��
	set_computer_value(SEED_START_CMD, CURVES_CH1, NULL, 0);// ͬ����λ����������ť״̬
  set_computer_value(SEED_TARGET_CMD, CURVES_CH1, &Temp, 1);// ��ͨ�� 1 ����Ŀ��ֵ
#endif

	while(1)
	{
    /* ɨ��KEY1������Ŀ��λ�� */
    if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
		{
			/* λ������2Ȧ */
      pid.target_val += 4800;
      
    #if PID_ASSISTANT_EN
      int temp = pid.target_val;
      set_computer_value(SEED_TARGET_CMD, CURVES_CH1, &temp, 1);// ��ͨ�� 1 ����Ŀ��ֵ
    #endif
		}
    /* ɨ��KEY2����СĿ��λ�� */
    if( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON  )
		{
			/* λ�ü�С2Ȧ */
      pid.target_val -= 4800;
      
    #if PID_ASSISTANT_EN
      int temp = pid.target_val;
      set_computer_value(SEED_TARGET_CMD, CURVES_CH1, &temp, 1);// ��ͨ�� 1 ����Ŀ��ֵ
    #endif
		}
	}
} 	

/**
  * @brief  ��ʱ�������¼��ص�����
  * @param  ��
  * @retval ��
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* �жϴ����жϵĶ�ʱ�� */
  if(htim->Instance == BASIC_TIM)
  {
    Stepper_Speed_Ctrl();
  }
  else if(htim->Instance == ENCODER_TIM)
  {  
    /* �жϵ�ǰ�������� */
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
      /* ���� */
      encoder_overflow_count--;
    else
      /* ���� */
      encoder_overflow_count++;
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 25
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1) {};
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    while(1) {};
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

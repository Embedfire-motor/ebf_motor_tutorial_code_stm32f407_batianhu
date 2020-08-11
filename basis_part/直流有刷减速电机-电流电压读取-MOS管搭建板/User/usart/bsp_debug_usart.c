/**
  ******************************************************************************
  * @file    bsp_debug_usart.c
  * @author  fire
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   ʹ�ô���1���ض���c��printf������usart�˿ڣ��жϽ���ģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./usart/bsp_debug_usart.h"

UART_HandleTypeDef UartHandle;

//���ڽ�������
unsigned char UART_RxBuffer[UART_RX_BUFFER_SIZE];
//���ڽ�������ָ��
unsigned char UART_RxPtr;
/* ���������� */
uint8_t receive_cmd = 0;

 /**
  * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */  
void DEBUG_USART_Config(void)
{ 
  
  UartHandle.Instance          = DEBUG_USART;
  
  UartHandle.Init.BaudRate     = DEBUG_USART_BAUDRATE;
  UartHandle.Init.WordLength   = USART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = USART_STOPBITS_1;
  UartHandle.Init.Parity       = USART_PARITY_NONE;
//  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = USART_MODE_TX_RX;
  
  HAL_UART_Init(&UartHandle);
    
  /*ʹ�ܴ��ڽ��ն� */
//  __HAL_UART_ENABLE_IT(&UartHandle, USART_IT_RXNE);
//  HAL_USART_Receive_IT(&UartHandle, &data, sizeof(data));
}


/**
  * @brief UART MSP ��ʼ�� 
  * @param huart: UART handle
  * @retval ��
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  DEBUG_USART_CLK_ENABLE();
	
	DEBUG_USART_RX_GPIO_CLK_ENABLE();
  DEBUG_USART_TX_GPIO_CLK_ENABLE();
  
/**USART1 GPIO Configuration    
  PA9     ------> USART1_TX
  PA10    ------> USART1_RX 
  */
  /* ����Tx����Ϊ���ù���  */
  GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = DEBUG_USART_TX_AF;
  HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);
  
  /* ����Rx����Ϊ���ù��� */
  GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
  GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
  HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct); 
 
//  HAL_NVIC_SetPriority(DEBUG_USART_IRQ ,5,0);	//��ռ���ȼ�0�������ȼ�1
//  HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ );		    //ʹ��USART1�ж�ͨ��  
}

//��ս��ջ���
void uart_FlushRxBuffer(void)
{
  UART_RxPtr = 0;
  UART_RxBuffer[UART_RxPtr] = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	if(__HAL_UART_GET_IT_SOURCE(&UartHandle, UART_IT_RXNE) != RESET)
//	{
//    //���Ϊ�˸��
//    if(data == '\b')
//    {
//      //���ָ�벻������Ŀ�ʼλ��
//      if(UART_RxPtr)
//      {
//        Usart_SendByte('\b');
//        Usart_SendByte(' ');
//        Usart_SendByte('\b');
//        UART_RxPtr--;
//        UART_RxBuffer[UART_RxPtr]=0x00;
//      }
//    }
//    //��������˸��
//    else
//    {
//      //��������������UART_RxBuffer
//      //���ҽ������һ��Ԫ�������������������д�����һ��Ԫ��Ϊֹ
//      if(UART_RxPtr < (UART_RX_BUFFER_SIZE - 1))
//      {
//        UART_RxBuffer[UART_RxPtr] = data;
//        UART_RxBuffer[UART_RxPtr + 1]=0x00;
//        UART_RxPtr++;
//      }
//      else
//      {
//        UART_RxBuffer[UART_RxPtr - 1] = data;
//        Usart_SendByte('\b');
//      }
//      //���Ϊ�س�������ʼ����������
//      if(data == 13 || data == 10)
//      {
//        receive_cmd = 1;
//      }
//      else
//      {
//        Usart_SendByte(data);
//      }
//    }
//  }
//  
//  HAL_USART_Receive_IT(&UartHandle, &data, sizeof(data));
}

/*****************  �����ַ� **********************/
void Usart_SendByte(uint8_t str)
{
  HAL_UART_Transmit(&UartHandle, &str, 1, 1000);
}

/*****************  �����ַ��� **********************/
void Usart_SendString(uint8_t *str)
{
	unsigned int k=0;
  do 
  {
      HAL_UART_Transmit(&UartHandle,(uint8_t *)(str + k) ,1,1000);
      k++;
  } while(*(str + k)!='\0');
}

///�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ�����DEBUG_USART */
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 1000);	
	
	return (ch);
}

///�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		
	int ch;
	HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}

/**
  * @brief ����У���
  * @param ptr����Ҫ���������
  * @param len����Ҫ����ĳ���
  * @retval У���
  */
uint8_t check_sum(uint8_t init, uint8_t *ptr, uint8_t len )
{
  uint8_t sum = init;
  
  while(len--)
  {
    sum += *ptr;
    ptr++;
  }
  
  return sum;
}

/**
  * @brief ������λ����ֵ
  * @param cmd������
  * @param ch: ����ͨ��
  * @param data������ָ��
  * @param num����������
  * @retval ��
  */
void set_computer_value(uint8_t cmd, uint8_t ch, void *data, uint8_t num)
{
  uint8_t sum = 0;    // У���
  num *= 4;           // һ������ 4 ���ֽ�
  
  static packet_head_t set_packet;
  
  set_packet.head = PACKET_HEAD;     // ��ͷ 0x59485A53
  set_packet.len  = 0x0B + num;      // ����
  set_packet.ch   = ch;              // ����ͨ��
  set_packet.cmd  = cmd;             // ��������
  
  sum = check_sum(0, (uint8_t *)&set_packet, sizeof(set_packet));       // �����ͷУ���
  sum = check_sum(sum, (uint8_t *)data, num);                           // �������У���
  
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&set_packet, sizeof(set_packet), 0xFFFFF);    // ��������ͷ
  HAL_UART_Transmit(&UartHandle, (uint8_t *)data, num, 0xFFFFF);                          // ���Ͳ���
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&sum, sizeof(sum), 0xFFFFF);                  // ����У���
}

/*********************************************END OF FILE**********************/

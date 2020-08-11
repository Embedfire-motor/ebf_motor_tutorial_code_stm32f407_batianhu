#ifndef __LED_H
<<<<<<< HEAD
#define __LED_H
=======
#define	__LED_H
>>>>>>> 6d0cbd76eed748919b7e4c43885c76194b020775

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
//R ��ɫ��
#define LED1_PIN                  GPIO_PIN_6                
#define LED1_GPIO_PORT            GPIOF                     
#define LED1_GPIO_CLK_ENABLE()    __GPIOF_CLK_ENABLE()

//G ��ɫ��
#define LED2_PIN                  GPIO_PIN_7                 
#define LED2_GPIO_PORT            GPIOF                      
#define LED2_GPIO_CLK_ENABLE()    __GPIOF_CLK_ENABLE()

//B ��ɫ��
#define LED3_PIN                  GPIO_PIN_8               
#define LED3_GPIO_PORT            GPIOF                       
#define LED3_GPIO_CLK_ENABLE()    __GPIOF_CLK_ENABLE()


/************************************************************/


/** ����LED������ĺ꣬
<<<<<<< HEAD
  * LED�͵�ƽ��������ON=0��OFF=1
  * ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
  */

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a) HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,a)


#define LED2(a) HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,a)


#define LED3(a) HAL_GPIO_WritePin(LED2_GPIO_PORT,LED3_PIN,a)
=======
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,a)


#define LED2(a)	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,a)


#define LED3(a)	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED3_PIN,a)
>>>>>>> 6d0cbd76eed748919b7e4c43885c76194b020775




/* ֱ�Ӳ����Ĵ����ķ�������IO */
<<<<<<< HEAD
#define digitalHi(p,i)        {p->BSRR=i;}        //����Ϊ�ߵ�ƽ    
#define digitalLo(p,i)        {p->BSRR=(uint32_t)i << 16;}        //����͵�ƽ
#define digitalToggle(p,i)    {p->ODR ^=i;}     //�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE   digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF      digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON       digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE   digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF      digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON       digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE   digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF      digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON       digitalLo(LED3_GPIO_PORT,LED3_PIN)
=======
#define	digitalHi(p,i)			{p->BSRR=i;}			  //����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)			{p->BSRR=(uint32_t)i << 16;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF		digitalHi(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON			digitalLo(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF		digitalHi(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON			digitalLo(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF		digitalHi(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON			digitalLo(LED3_GPIO_PORT,LED3_PIN)
>>>>>>> 6d0cbd76eed748919b7e4c43885c76194b020775



/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
<<<<<<< HEAD
          LED1_ON;\
          LED2_OFF\
          LED3_OFF

//��
#define LED_GREEN   \
          LED1_OFF;\
          LED2_ON\
          LED3_OFF

//��
#define LED_BLUE  \
          LED1_OFF;\
          LED2_OFF\
          LED3_ON

          
//��(��+��)          
#define LED_YELLOW  \
          LED1_ON;\
          LED2_ON\
          LED3_OFF
//��(��+��)
#define LED_PURPLE  \
          LED1_ON;\
          LED2_OFF\
          LED3_ON

//��(��+��)
#define LED_CYAN \
          LED1_OFF;\
          LED2_ON\
          LED3_ON
          
//��(��+��+��)
#define LED_WHITE \
          LED1_ON;\
          LED2_ON\
          LED3_ON
          
//��(ȫ���ر�)
#define LED_RGBOFF  \
          LED1_OFF;\
          LED2_OFF\
          LED3_OFF
          
=======
					LED1_ON;\
					LED2_OFF\
					LED3_OFF

//��
#define LED_GREEN		\
					LED1_OFF;\
					LED2_ON\
					LED3_OFF

//��
#define LED_BLUE	\
					LED1_OFF;\
					LED2_OFF\
					LED3_ON

					
//��(��+��)					
#define LED_YELLOW	\
					LED1_ON;\
					LED2_ON\
					LED3_OFF
//��(��+��)
#define LED_PURPLE	\
					LED1_ON;\
					LED2_OFF\
					LED3_ON

//��(��+��)
#define LED_CYAN \
					LED1_OFF;\
					LED2_ON\
					LED3_ON
					
//��(��+��+��)
#define LED_WHITE	\
					LED1_ON;\
					LED2_ON\
					LED3_ON
					
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED1_OFF;\
					LED2_OFF\
					LED3_OFF
					
>>>>>>> 6d0cbd76eed748919b7e4c43885c76194b020775




void LED_GPIO_Config(void);

#endif /* __LED_H */

#include "CONFIG.h"

extern u32 real_time;
extern u32 status;
extern float dis;


//�ⲿ�жϷ������
//�ⲿ�ж�0�������
void EXTI4_IRQHandler(void)
{
    TIM2->CR1&=~(0x01);                  // ��ʹ�ܶ�ʱ��3

    real_time = status ;
    dis=(float)real_time*1.7/10-5;             // �������	��ʱ10us��S=Vt/2����2��������

	EXTI->PR=1<<4;  //���LINE0�ϵ��жϱ�־λ  
}


//�ⲿ�жϳ�ʼ������
//��ʼ��PB2Ϊ�ж�����.
void EXTIX_Init(void)
{

  RCC->APB2ENR|=1<<3;      // ʹ��PORTBʱ��    

	GPIOB->CRL&=0XFF00FFFF;  // PB4���ó�����	  
	GPIOB->CRL|=0X00380000;   
	
	GPIOB->ODR|=0<<5;	       // PB5����


	Ex_NVIC_Config(GPIO_B,4,FTIR); //�½��ش���

	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    //��ռ2�������ȼ�2����2	   
}













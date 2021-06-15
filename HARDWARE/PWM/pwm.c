#include "CONFIG.H"



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void PWM_Init(u16 arr,u16 psc)
{		 					 

    RCC->APB1ENR|=1<<2;   	//TIM4 ʱ��ʹ�� 
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ�� 
	
	RCC->APB2ENR|=1<<0;   //ʹ��AFIOʱ��
	
	AFIO->MAPR&=0XF8FFFFFF;
    AFIO->MAPR|=0x02000000;   //�ر�JATG������SW��ʽ

	
	GPIOB->CRH&=0X0000FF00;	//
	GPIOB->CRH|=0X333300BB;	//PB8���PWM1,PB9���PWM2
	
	
	GPIOB->ODR|=1<<8;		//PB8 ����
	GPIOB->ODR|=1<<9;		//PB8 ����
	  
 	TIM4->ARR=arr;  		//�趨�������Զ���װֵ ���10ms���  
	TIM4->PSC=psc;  			//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	 
	
    TIM4->CCMR2|=7<<4;  //CH3 PWM2ģʽ		 
	TIM4->CCMR2|=1<<3; //CH3Ԥװ��ʹ��	
	TIM4->CCER|=1<<8;   //OC3 ���ʹ��
	
	TIM4->CCMR2|=7<<12;  //CH4 PWM2ģʽ		 
	TIM4->CCMR2|=1<<11; //CH4Ԥװ��ʹ��	
	TIM4->CCER|=1<<12;   //OC3 ���ʹ��

	TIM4->CR1=0x80;     //ARPEʹ�� 
	TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��2				
	
}  	 














#include "CONFIG.H"



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void SG_Init(u16 arr,u16 psc)
{		 					 

	RCC->APB1ENR|=1<<1;       //TIM3ʱ��ʹ��   
  RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��
	
  GPIOB->CRL&=0XFFFFFFF0;//PB0���
	GPIOB->CRL|=0X0000000B;//��������,������������	  


	TIM3->ARR=arr;//�趨�������Զ���װֵ 
	TIM3->PSC=psc;//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR2|=6<<4;  //CH3 PWM2ģʽ		 
	TIM3->CCMR2|=1<<3; //CH3Ԥװ��ʹ��	   

	TIM3->CCER|=1<<8;   //OC2 ���ʹ��	   

	TIM3->CR1=0x80;   //ARPEʹ�� 
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��2										  
}  	 














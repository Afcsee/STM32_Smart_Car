#include "CONFIG.h"

extern u32 status;

//��ʱ��3�жϷ������	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{
	 status++; 	  	
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM3ʱ��ʹ��    
 	TIM2->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM2->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM2->DIER|=1<<0;   //��������ж�				
	TIM2->DIER|=1<<6;   //�������ж�	   
	//TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  MY_NVIC_Init(1,3,TIM2_IRQn,2);//��ռ1�������ȼ�3����2
}

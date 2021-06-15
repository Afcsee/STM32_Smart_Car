#include "CONFIG.H"



//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void SG_Init(u16 arr,u16 psc)
{		 					 

	RCC->APB1ENR|=1<<1;       //TIM3时钟使能   
  RCC->APB2ENR|=1<<3;    	//使能PORTB时钟
	
  GPIOB->CRL&=0XFFFFFFF0;//PB0输出
	GPIOB->CRL|=0X0000000B;//浮空输入,不干扰其它的	  


	TIM3->ARR=arr;//设定计数器自动重装值 
	TIM3->PSC=psc;//预分频器不分频
	
	TIM3->CCMR2|=6<<4;  //CH3 PWM2模式		 
	TIM3->CCMR2|=1<<3; //CH3预装载使能	   

	TIM3->CCER|=1<<8;   //OC2 输出使能	   

	TIM3->CR1=0x80;   //ARPE使能 
	TIM3->CR1|=0x01;    //使能定时器2										  
}  	 














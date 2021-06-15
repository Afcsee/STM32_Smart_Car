#include "CONFIG.H"



//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void PWM_Init(u16 arr,u16 psc)
{		 					 

    RCC->APB1ENR|=1<<2;   	//TIM4 时钟使能 
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟 
	
	RCC->APB2ENR|=1<<0;   //使能AFIO时钟
	
	AFIO->MAPR&=0XF8FFFFFF;
    AFIO->MAPR|=0x02000000;   //关闭JATG，开启SW方式

	
	GPIOB->CRH&=0X0000FF00;	//
	GPIOB->CRH|=0X333300BB;	//PB8输出PWM1,PB9输出PWM2
	
	
	GPIOB->ODR|=1<<8;		//PB8 上拉
	GPIOB->ODR|=1<<9;		//PB8 上拉
	  
 	TIM4->ARR=arr;  		//设定计数器自动重装值 最大10ms溢出  
	TIM4->PSC=psc;  			//预分频器,1M的计数频率,1us加1.	 
	
    TIM4->CCMR2|=7<<4;  //CH3 PWM2模式		 
	TIM4->CCMR2|=1<<3; //CH3预装载使能	
	TIM4->CCER|=1<<8;   //OC3 输出使能
	
	TIM4->CCMR2|=7<<12;  //CH4 PWM2模式		 
	TIM4->CCMR2|=1<<11; //CH4预装载使能	
	TIM4->CCER|=1<<12;   //OC3 输出使能

	TIM4->CR1=0x80;     //ARPE使能 
	TIM4->CR1|=0x01;    //使能定时器2				
	
}  	 














#include "CONFIG.h"

extern u8 time,speed,dz;
//static u8 timer_50ms=0;
extern u32 status;

/*//定时器3中断服务程序	 电机测速/延时
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{
		speed = time;
		time = 0;
	  timer_50ms++;
	  if(timer_50ms>3) 
		{	
			dz++;
      timer_50ms=0;		
    }	
    if(dz>5) dz=1;
		
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3时钟使能    
 	TIM3->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东东要同时设置才可以使用中断
	TIM3->DIER|=1<<0;   //允许更新中断				
	TIM3->DIER|=1<<6;   //允许触发中断	   
	TIM3->CR1|=0x01;    //使能定时器3
  MY_NVIC_Init(2,2,TIM3_IRQn,2);//抢占1，子优先级3，组2									 
}
*/


//定时器3中断服务程序	 
void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{
	 status++; 	  	
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM3时钟使能    
 	TIM2->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM2->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东东要同时设置才可以使用中断
	TIM2->DIER|=1<<0;   //允许更新中断				
	TIM2->DIER|=1<<6;   //允许触发中断	   
	//TIM3->CR1|=0x01;    //使能定时器3
  MY_NVIC_Init(1,3,TIM2_IRQn,2);//抢占1，子优先级3，组2
}

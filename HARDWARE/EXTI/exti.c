#include "CONFIG.h"

extern u32 real_time;
extern u32 status;
extern float dis;


//外部中断服务程序
//外部中断0服务程序
void EXTI4_IRQHandler(void)
{
    TIM2->CR1&=~(0x01);                  // 关使能定时器3

    real_time = status ;
    dis=(float)real_time*1.7/10-5;             // 计算距离	定时10us，S=Vt/2（减2是误差补尝）

	EXTI->PR=1<<4;  //清除LINE0上的中断标志位  
}


//外部中断初始化程序
//初始化PB2为中断输入.
void EXTIX_Init(void)
{

  RCC->APB2ENR|=1<<3;      // 使能PORTB时钟    

	GPIOB->CRL&=0XFF00FFFF;  // PB4设置成输入	  
	GPIOB->CRL|=0X00380000;   
	
	GPIOB->ODR|=0<<5;	       // PB5上拉


	Ex_NVIC_Config(GPIO_B,4,FTIR); //下降沿触发

	MY_NVIC_Init(2,2,EXTI4_IRQn,2);    //抢占2，子优先级2，组2	   
}













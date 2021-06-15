#include "CONFIG.H"	 	 

u8 time=0,speed=0,dz=0;
u16 stop=900,run=200;//转不动减小run

#define CSB_TX PBout(5)         // PB5 发送超声波引脚 
float	dis;					// 距离计算值

//寻找距离最大的角度
u16 max_arg=15,max_arg_low,max_arg_high;
float max_dis=20;

u8 mode=0;

u32   real_time;	 				      // 读回值
u32   status=0;						      // 计数值，测距
u8 arg=15,forward=1;            //arg=15中间

//不同模式
void Mode_Go_Straight(void);
void Mode_Turn(void);

//电机部分
void Forward_run(void);   //前进
void Backward_run(void);  //后退
void Turn_Left(u16 turn_time);//左转
void Turn_Right(u16 turn_time);//右转
void Stop(void);          //停止

//超声波测距部分
void tran(void); 					      // 左发生超声波函数

//舵机部分
void Turn_SG(void);
void Find_Director(void);

int main(void)
{		
	Stm32_Clock_Init(9);   //系统时钟设置
	delay_init(72);	       //延时初始化
	uart_init(72,9600);    //串口初始化 
	PWM_Init(900,0);      //不分频。PWM频率=72000/900=80Khz
	SG_Init(199,7199);
	Timerx_Init(10,71);     // 1Mhz的计数频率，计数到10为10us 
	EXTIX_Init();         //外部中断初始化

	SG_PWM_VAL=15;
  while(1)
	{
		if(!mode)//直行
		{
			tran();
			if(dis>80) dis=80;
			Mode_Go_Straight();
			if(dis<30)
			{
				mode=1;
				Stop();
			}
		}
		else Mode_Turn();
		delay_ms(100);
	}	
}

//直行模式
void Mode_Go_Straight(void)
{
	Forward_run();
}

//转向模式
void Mode_Turn(void)
{
	Stop();
	while(1)
	{
		Find_Director();
		if(13<=max_arg&&max_arg<=17) break;
		else if(max_arg<13) Turn_Right((15-max_arg)*50);
		else if(max_arg>17) Turn_Left((max_arg-15)*50);
	}
	mode=0;
	SG_PWM_VAL=15;
}

//10前进，01后退
//前进
 void Forward_run(void)
{
	Pwm_Right=run;
	Pwm_Left=run;

	Right1=1;
	Right2=0;
	Left1=1;
	Left2=0;
}

//后退
void Backward_run(void)
{
	Pwm_Right=run;
    Pwm_Left=run;

	Right1=0;
	Right2=1;
	Left1=0;
	Left2=1;
}

//左转
void Turn_Left(u16 turn_time)
{    
	Pwm_Right=run;
    Pwm_Left=run;

	Right1=1;
	Right2=0;
	Left1=0;
	Left2=1;

	delay_ms(turn_time);
	Stop();
}

//右转
void Turn_Right(u16 turn_time)
{
	Pwm_Right=run;
    Pwm_Left=run;

	Right1=0;
	Right2=1;
	Left1=1;
	Left2=0;

	delay_ms(turn_time);
	Stop();

}

//停止
void Stop(void)
{     
	Pwm_Right=stop;
	Pwm_Left=stop;
	
	Right1=0;
	Right2=0;
	Left1=0;
	Left2=0;
}

//超声波测距
void tran(void)
{ 
	u8 i;
    TIM2->CR1|=0x01;         // 使能定时器3
    TIM2->SR&=~(1<<0);       // 清除中断标志位    
    status  = 0;			       // 定时器清零
    for(i=0;i<8;i++)         // 发送信号
    {
			CSB_TX = 1;            
			delay_us(12);    
			CSB_TX = 0;
			delay_us(12);    
    }
   delay_ms(10);
}

//左右测距
void Turn_SG(void)
{
	if(forward)
	{
		arg-=5;//-为右
		if(arg==5) forward=0;
	}
	else
	{
		arg+=5;
		if(arg==25) forward=1;
	}
	SG_PWM_VAL=arg;
}

//寻找方向
void Find_Director(void)
{
	arg=5;
	SG_PWM_VAL=arg;
	max_dis=20;
	max_arg_low=15,max_arg_high=15;
	while(1)
	{
		tran();
		if(dis>80) dis=80;
		if(dis>max_dis)
		{
			max_dis=dis;
			max_arg_low=arg,max_arg_high=arg;
		}
		else if(dis==max_dis) max_arg_high=arg;
		if(arg==15&&dis==80)
		{
			max_arg=15;
			return ;
		}
		if(arg==25) break;
		arg+=2;
		SG_PWM_VAL=arg;
		delay_ms(300);
	}
	max_arg=(max_arg_high+max_arg_low)/2;
}

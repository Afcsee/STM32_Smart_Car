#include "CONFIG.H"

u16 stop=900,run=150;//转不动减小run

extern u32 status;
extern float dis;

u8 max_arg=15,max_arg_low,max_arg_high,arg=15;
float max_dis=20;

float dis_l,dis_r;

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

    delay_ms(300);
    Stop();
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
void Keep_Balance(void)
{
	SG_PWM_VAL=5;
	delay_ms(200);
	tran();
	if(dis>80) dis=80;
	dis_r=dis;

	SG_PWM_VAL=25;
	delay_ms(200);
	tran();
	if(dis>80) dis=80;
	dis_l=dis;

	if((dis_l-dis_r)<7&&(dis_r-dis_l)<7) return;
	if(dis_l>dis_r)
	{
		if((dis_l-dis_r)>20) Turn_Left(150);
		else Turn_Left(100);
	}
	else
	{
		if((dis_r-dis_l)>20) Turn_Right(150);
		else Turn_Left(100);
	}
}

//寻找方向
u8 Find_Director(void)
{
	arg=5;
	SG_PWM_VAL=arg;
	max_dis=0;
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
		if(arg==15)
		{
			if(dis>60) return 15;
			if(dis<15) return 0;
		}
		if(arg==25) break;
		arg+=2;
		SG_PWM_VAL=arg;
		delay_ms(200);
	}
	max_arg=(max_arg_high+max_arg_low)/2;
	if(max_dis<15) max_arg=0;
    return max_arg;
}

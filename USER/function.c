#include "CONFIG.H"

u16 stop=900,run=200;//转不动减小run

extern u32 status;
extern float dis;

u8 out,i,l_out,l_hit,r_out,r_hit,s_out,s_hit,arg;
float dis_max,d,alldis[12];
u8 arg=15,forward=1;            //arg=15中间

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

    delay_ms(250);
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
	SG_PWM_VAL=10;
	delay_ms(100);
	tran();
	if(dis>80) dis=80;
	dis_r=dis;

	SG_PWM_VAL=20;
	delay_ms(100);
	tran();
	if(dis>80) dis=80;
	dis_l=dis;

	if((dis_l-dis_r)<5&&(dis_r-dis_l)<5) return;
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
	Scan();
    if(s_out&&(!s_hit)) return Max(4,6);
    if(Need_Back()) return 0;
    if(((!r_out)&&(!r_hit)&&l_out&&l_hit)||(r_out&&(!r_hit))||((!l_out)&&l_hit)) return Max(7,10);
    else return Max(0,3);
}

//扫描
void Scan(void)
{
    dis_max=0;
    l_out=0,r_out=0,s_out=0;
	l_hit=0,r_hit=0,s_hit=0;
    for(i=0;i<11;i++)
    {
        SG_PWM_VAL=5+2*i;
        delay_ms(200);
        tran();
		if(dis>80) dis=80;
        alldis[i]=dis;
        if(dis>40)
        {
            if(i<4) r_out++;
            else if(i>6) l_out++;
            else s_out++;
        }
		if(dis<10)
		{
			if(i<4) r_hit++;
			else if(i>6) l_hit++;
			else s_hit++;
		}
        if(dis>dis_max) dis_max=dis;
    }
}

u8 Max(u8 l,u8 r)
{
    float max=0;
    u8 arg_l,arg_r;
    for(i=l;i<=r;i++)
    {
        if(alldis[i]>max)
        {
            max=alldis[i];
            arg_l=arg_r=5+2*i;
        }
        else if(alldis[i]==max) arg_r=5+2*i;
    }
    return (arg_l+arg_r)/2;
}

u8 Need_Back(void)
{
	if((!r_hit)&&(!r_out)&&(!l_hit)&&(!l_out)) return 1;
	if(r_out&&r_hit&&l_out&&l_hit) return 1;
	if(r_out&&(!r_hit)&&l_out&&(!l_hit)) return 1;
	if((!r_out)&&r_hit&&(!l_out)&&l_hit) return 1;
	return 0;
}

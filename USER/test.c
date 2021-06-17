#include "CONFIG.H"

float dis;					// 距离计算值

u8 mode=0,go_arg=15,flag=0,i;

u32 real_time,status=0;	 				      // 读回值;计数值，测距

//不同模式
void Mode_Go_Straight(void);
void Mode_Turn(void);

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
			SG_PWM_VAL=15;
			delay_ms(100);
			tran();
			if(dis>80) dis=80;
			if(dis<30)
			{
				mode=1;
				Backward_run();
				Stop();
			}
			Mode_Go_Straight();
		}
		else Mode_Turn();
		delay_ms(100);
	}	
}

//直行模式
void Mode_Go_Straight(void)
{
	
	if(flag<10)
	{
		Forward_run();
		flag++;
	}
	else
	{
		Stop();
		Keep_Balance();
		Forward_run();
		flag=0;
	}
	/*Forward_run();
	flag++;
	if(flag==10)
	{
		Keep_Balance();
		flag=0;
		Forward_run();
	}*/
}

//转向模式
void Mode_Turn(void)
{
	Stop();
	while(1)
	{
		go_arg=Find_Director();
		if(13<=go_arg&&go_arg<=17) break;
		else if(go_arg<13&&go_arg!=0) Turn_Right((15-go_arg)*50);
		else if(go_arg>17&&go_arg!=0) Turn_Left((go_arg-15)*50);
		else Backward_run();
	}
	mode=0;
	SG_PWM_VAL=15;
	delay_ms(100);
	flag=0;
}


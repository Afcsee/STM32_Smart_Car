#include "CONFIG.H"	 	 

u8 time=0,speed=0,dz=0;
u16 stop=900,run=200;//ת������Сrun

#define CSB_TX PBout(5)         // PB5 ���ͳ��������� 
float	dis;					// �������ֵ

//Ѱ�Ҿ������ĽǶ�
u16 max_arg=15,max_arg_low,max_arg_high;
float max_dis=20;

u8 mode=0;

u32   real_time;	 				      // ����ֵ
u32   status=0;						      // ����ֵ�����
u8 arg=15,forward=1;            //arg=15�м�

//��ͬģʽ
void Mode_Go_Straight(void);
void Mode_Turn(void);

//�������
void Forward_run(void);   //ǰ��
void Backward_run(void);  //����
void Turn_Left(u16 turn_time);//��ת
void Turn_Right(u16 turn_time);//��ת
void Stop(void);          //ֹͣ

//��������ಿ��
void tran(void); 					      // ��������������

//�������
void Turn_SG(void);
void Find_Director(void);

int main(void)
{		
	Stm32_Clock_Init(9);   //ϵͳʱ������
	delay_init(72);	       //��ʱ��ʼ��
	uart_init(72,9600);    //���ڳ�ʼ�� 
	PWM_Init(900,0);      //����Ƶ��PWMƵ��=72000/900=80Khz
	SG_Init(199,7199);
	Timerx_Init(10,71);     // 1Mhz�ļ���Ƶ�ʣ�������10Ϊ10us 
	EXTIX_Init();         //�ⲿ�жϳ�ʼ��

	SG_PWM_VAL=15;
  while(1)
	{
		if(!mode)//ֱ��
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

//ֱ��ģʽ
void Mode_Go_Straight(void)
{
	Forward_run();
}

//ת��ģʽ
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

//10ǰ����01����
//ǰ��
 void Forward_run(void)
{
	Pwm_Right=run;
	Pwm_Left=run;

	Right1=1;
	Right2=0;
	Left1=1;
	Left2=0;
}

//����
void Backward_run(void)
{
	Pwm_Right=run;
    Pwm_Left=run;

	Right1=0;
	Right2=1;
	Left1=0;
	Left2=1;
}

//��ת
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

//��ת
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

//ֹͣ
void Stop(void)
{     
	Pwm_Right=stop;
	Pwm_Left=stop;
	
	Right1=0;
	Right2=0;
	Left1=0;
	Left2=0;
}

//���������
void tran(void)
{ 
	u8 i;
    TIM2->CR1|=0x01;         // ʹ�ܶ�ʱ��3
    TIM2->SR&=~(1<<0);       // ����жϱ�־λ    
    status  = 0;			       // ��ʱ������
    for(i=0;i<8;i++)         // �����ź�
    {
			CSB_TX = 1;            
			delay_us(12);    
			CSB_TX = 0;
			delay_us(12);    
    }
   delay_ms(10);
}

//���Ҳ��
void Turn_SG(void)
{
	if(forward)
	{
		arg-=5;//-Ϊ��
		if(arg==5) forward=0;
	}
	else
	{
		arg+=5;
		if(arg==25) forward=1;
	}
	SG_PWM_VAL=arg;
}

//Ѱ�ҷ���
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

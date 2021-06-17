#include "CONFIG.H"

float dis;					// �������ֵ

u8 mode=0,go_arg=15,flag=0,i;

u32 real_time,status=0;	 				      // ����ֵ;����ֵ�����

//��ͬģʽ
void Mode_Go_Straight(void);
void Mode_Turn(void);

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

//ֱ��ģʽ
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

//ת��ģʽ
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


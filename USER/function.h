#ifndef __FUNCTION_H
    #define __FUNCTION_H

#define CSB_TX PBout(5)         // PB5 ���ͳ���������

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
u8 Find_Director(void);
void Scan(void);

u8 Need_Back(void);
u8 Max(u8 l,u8 r);

#endif

#ifndef __FUNCTION_H
    #define __FUNCTION_H

#define CSB_TX PBout(5)         // PB5 发送超声波引脚

//电机控制
void Forward_run(void);   //前进
void Backward_run(void);  //后退
void Turn_Left(u16 turn_time);//左转
void Turn_Right(u16 turn_time);//右转
void Stop(void);          //停止

//超声波测距部分
void tran(void); 					      // 左发生超声波函数

//舵机部分
void Keep_Balance(void);
u8 Find_Director(void);

#endif
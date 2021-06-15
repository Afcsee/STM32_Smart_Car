#ifndef __SG_H
#define __SG_H


//通过改变TIM5->CCR2的值来改变占空比
#define SG_PWM_VAL TIM3->CCR3 

void SG_Init(u16 arr,u16 psc);

#endif

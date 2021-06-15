#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define Pwm_Right TIM4->CCR3 
#define Pwm_Left TIM4->CCR4

#define Right1 PBout(12)
#define Right2 PBout(13)
#define Left1 PBout(14)
#define Left2 PBout(15)

void PWM_Init(u16 arr,u16 psc);

#endif

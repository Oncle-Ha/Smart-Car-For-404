/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[motor.h] 
* ��  �� ���������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� ���������������
***********************************************************************
*/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 1  //Ϊֱ������š����ܡ��㳵����·����Ԥ��

#include "common.h"
#include "ftm.h"


#define MOTOR_MAX    9600
#define MOTOR_MIN    -9600


#define  MOTOR_FTMN       CFTM2           
#define  MOTOR_FTMCH0     FTM_CH0           //PTC0
#define  MOTOR_FTMCH1     FTM_CH1           //PTC1 
 

#define  MOTOR_FREQ 5           //���Ƶ��   16k
#define  MOTOR_INIT_VAL 0           //�����ʼֵ������1/10000  ��0/10000 0%


void motor_init();

#if !MOTOR_DOUBLE
    void PWMSetMotor(int32 speed_pwm);
#endif

#if MOTOR_DOUBLE
    //#define MOTOR_MAX    10000
    //#define MOTOR_MIN    -10000
    
    //#define  MOTOR_FTMN       CFTM2      
    #define  MOTOR_FTMCH2     FTM_CH2           //PTC2
    #define  MOTOR_FTMCH3     FTM_CH3           //PTC3 
    
    //#define  MOTOR_FREQ 16000           //���Ƶ��   16k
    //#define  MOTOR_INIT_VAL 0           //�����ʼֵ������1/10000  ��0/10000 0%
        
    //void motor_init();
    
    void PWMSetMotor2(int32 speed_pwmL,int32 speed_pwmR);
#endif 

    
    void motorCtrl();
      
#endif
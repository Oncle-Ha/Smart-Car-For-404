/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[motor.h] 
* 描  述 ：电机机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：电机机驱动函数
***********************************************************************
*/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 1  //为直立、电磁、节能、汇车组两路控制预留

#include "common.h"
#include "ftm.h"


#define MOTOR_MAX    9600
#define MOTOR_MIN    -9600


#define  MOTOR_FTMN       CFTM2           
#define  MOTOR_FTMCH0     FTM_CH0           //PTC0
#define  MOTOR_FTMCH1     FTM_CH1           //PTC1 
 

#define  MOTOR_FREQ 5           //电机频率   16k
#define  MOTOR_INIT_VAL 0           //电机初始值，精度1/10000  即0/10000 0%


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
    
    //#define  MOTOR_FREQ 16000           //电机频率   16k
    //#define  MOTOR_INIT_VAL 0           //电机初始值，精度1/10000  即0/10000 0%
        
    //void motor_init();
    
    void PWMSetMotor2(int32 speed_pwmL,int32 speed_pwmR);
#endif 

    
    void motorCtrl();
      
#endif
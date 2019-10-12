/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[motor.c] 
* 描  述 ：电机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：电机驱动函数
***********************************************************************
*/

#include "motor.h"
#include "common.h"
#include "ftm.h"



/********************************************************************
** 函数名称: void steer_init() 
** 功能描述: 设置舵机转向
** 入口：角度值
** 出口：
** 说明:  
*********************************************************************/
void motor_init()         
{
    
    
    //初始化FTM2_CH0输出频率为100HZ,占空比为13%的PWM ：FTM2_CH0对应PTA10口
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH0,MOTOR_FREQ,MOTOR_INIT_VAL); 
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH1,MOTOR_FREQ,MOTOR_INIT_VAL); 
#if MOTOR_DOUBLE
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH2,MOTOR_FREQ,MOTOR_INIT_VAL); 
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH3,MOTOR_FREQ,MOTOR_INIT_VAL); 
#endif
}
#if !MOTOR_DOUBLE
/********************************************************************
** 函数名称: PWMSetMotor
** 功能描述: 设置速度
** 入口：速度
** 出口：
** 说明:  
*********************************************************************/
void PWMSetMotor(int32 speed_pwm)         
{
    if(speed_pwm < MOTOR_MIN)
    {
      speed_pwm = MOTOR_MIN;
    }
    if(speed_pwm > MOTOR_MAX)
    {
      speed_pwm = MOTOR_MAX;
    }
    
    if(speed_pwm > 0) 
    {
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH0,(uint32)speed_pwm);
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH1,0);
    } 
    else 
    {
       speed_pwm = -speed_pwm;
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH1,(uint32)speed_pwm);
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH0,0);
    }
}

/********************************************************************
** 函数名称: motorCtrl
** 功能描述: 速度控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/
void motorCtrl()
{
    /***
  s32 speed_pwm;
    
    speed_pwm = 0;    //去除warning
    
    //自己的速度控制算法
    
    
    
    PWMSetMotor(speed_pwm);
  ***/
}

#endif


#if MOTOR_DOUBLE
/********************************************************************
** 函数名称: PWMSetMotor
** 功能描述: 设置速度
** 入口：左右速度
** 出口：
** 说明:  
*********************************************************************/
void PWMSetMotor2(int32 speed_pwmL,int32 speed_pwmR)         
{
    if(speed_pwmL < MOTOR_MIN)
    {
      speed_pwmL = MOTOR_MIN;
    }
    if(speed_pwmL > MOTOR_MAX)
    {
      speed_pwmL = MOTOR_MAX;
    }
    
    if(speed_pwmR < MOTOR_MIN)
    {
      speed_pwmR = MOTOR_MIN;
    }
    if(speed_pwmR > MOTOR_MAX)
    {
      speed_pwmR = MOTOR_MAX;
    }
    
    if(speed_pwmL > 0) 
    {
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH0,(uint32)speed_pwmL);
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH1,0);
    } 
    else 
    {
       speed_pwmL = -speed_pwmL;
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH1,(uint32)speed_pwmL);
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH0,0);
    }
    
    if(speed_pwmR > 0) 
    {
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH2,(uint32)speed_pwmR);
        FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH3,0);
    } 
    else 
    {
       speed_pwmR = -speed_pwmR;
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH3,(uint32)speed_pwmR);
       FTM_PWM_Duty(MOTOR_FTMN,MOTOR_FTMCH2,0);
    }
}

/********************************************************************
** 函数名称: motorCtrl
** 功能描述: 速度控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/
void motorCtrl()
{
  /***
    s32 speed_pwm;
    
    speed_pwm = 0;    //去除warning
    
    //自己的速度控制算法
    
    
    
    PWMSetMotor2(speed_pwm,speed_pwm);
  ***/
}

#endif




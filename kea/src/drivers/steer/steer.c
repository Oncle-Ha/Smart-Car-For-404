/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[steer.c] 
* 描  述 ：舵机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：舵机驱动函数
***********************************************************************
*/

#include "steer.h"
#include "common.h"
#include "ftm.h"


/********************************************************************
** 函数名称 : void steer_init() 
** 功能描述 : 设置舵机转向
** 入口     ：
** 出口     ：
** 说明     :  初始化PWM波及占空比
*********************************************************************/
void steer_init()         
{
      
    FTM_PWM_init(STEER_FTMN,STEER_FTMCH,STEER_FREQ,STEER_INIT_VAL); 
#if STEER_DOUBLE
    
    FTM_PWM_init(STEER_FTMN,STEER_FTMCH1,STEER_FREQ,STEER_INIT_VAL1); 
#endif
}

/********************************************************************
** 函数名称: void PWMSetSteer(int angle_pwm) 
** 功能描述: 设置舵机转向
** 入口：角度值
** 出口：
** 说明:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //占空比不能超过上限（防止过压）
    //同时防止方向打死  
    //这个保护措施是必要的
    if(angle_pwm < STEER_RIGHT)
         angle_pwm = STEER_RIGHT;
    if(angle_pwm > STEER_LEFT)
         angle_pwm = STEER_LEFT;
        
    FTM_PWM_Duty(STEER_FTMN,STEER_FTMCH,angle_pwm);
}


/********************************************************************
** 函数名称: steerCtrl
** 功能描述: 速度控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/
void steerCtrl()
{
    /*
    int angle_pwm;
    angle_pwm = 0;    //去除warning
    
    //自己的舵机控制算法
    
    
    PWMSetSteer(angle_pwm) ; 
    */ 
}


#if STEER_DOUBLE
void PWMSetSteer1(int angle_pwm)         
{
    //占空比不能超过上限（防止过压）
    //同时防止方向打死  
    //这个保护措施是必要的
    if(angle_pwm < STEER_RIGHT1)
         angle_pwm = STEER_RIGHT1;
    if(angle_pwm > STEER_LEFT1)
         angle_pwm = STEER_LEFT1;
    
    
    FTM_PWM_Duty(STEER_FTMN,STEER_FTMCH1,angle_pwm);
}


/********************************************************************
** 函数名称: steerCtrl
** 功能描述: 速度控制算法
** 入口：
** 出口：
** 说明:  
*********************************************************************/
void steerCtrl1()
{
    /*
    int angle_pwm;
    angle_pwm = 0;    //去除warning
    
    //自己的舵机控制算法
    
    
    
    PWMSetSteer1(angle_pwm) ;  
    */
}

#endif

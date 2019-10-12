/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[motor.c] 
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/

#include "motor.h"
#include "common.h"
#include "ftm.h"



/********************************************************************
** ��������: void steer_init() 
** ��������: ���ö��ת��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:  
*********************************************************************/
void motor_init()         
{
    
    
    //��ʼ��FTM2_CH0���Ƶ��Ϊ100HZ,ռ�ձ�Ϊ13%��PWM ��FTM2_CH0��ӦPTA10��
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH0,MOTOR_FREQ,MOTOR_INIT_VAL); 
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH1,MOTOR_FREQ,MOTOR_INIT_VAL); 
#if MOTOR_DOUBLE
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH2,MOTOR_FREQ,MOTOR_INIT_VAL); 
    FTM_PWM_init(MOTOR_FTMN,MOTOR_FTMCH3,MOTOR_FREQ,MOTOR_INIT_VAL); 
#endif
}
#if !MOTOR_DOUBLE
/********************************************************************
** ��������: PWMSetMotor
** ��������: �����ٶ�
** ��ڣ��ٶ�
** ���ڣ�
** ˵��:  
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
** ��������: motorCtrl
** ��������: �ٶȿ����㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void motorCtrl()
{
    /***
  s32 speed_pwm;
    
    speed_pwm = 0;    //ȥ��warning
    
    //�Լ����ٶȿ����㷨
    
    
    
    PWMSetMotor(speed_pwm);
  ***/
}

#endif


#if MOTOR_DOUBLE
/********************************************************************
** ��������: PWMSetMotor
** ��������: �����ٶ�
** ��ڣ������ٶ�
** ���ڣ�
** ˵��:  
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
** ��������: motorCtrl
** ��������: �ٶȿ����㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void motorCtrl()
{
  /***
    s32 speed_pwm;
    
    speed_pwm = 0;    //ȥ��warning
    
    //�Լ����ٶȿ����㷨
    
    
    
    PWMSetMotor2(speed_pwm,speed_pwm);
  ***/
}

#endif




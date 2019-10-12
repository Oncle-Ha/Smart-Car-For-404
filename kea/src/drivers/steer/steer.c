/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[steer.c] 
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/

#include "steer.h"
#include "common.h"
#include "ftm.h"


/********************************************************************
** �������� : void steer_init() 
** �������� : ���ö��ת��
** ���     ��
** ����     ��
** ˵��     :  ��ʼ��PWM����ռ�ձ�
*********************************************************************/
void steer_init()         
{
      
    FTM_PWM_init(STEER_FTMN,STEER_FTMCH,STEER_FREQ,STEER_INIT_VAL); 
#if STEER_DOUBLE
    
    FTM_PWM_init(STEER_FTMN,STEER_FTMCH1,STEER_FREQ,STEER_INIT_VAL1); 
#endif
}

/********************************************************************
** ��������: void PWMSetSteer(int angle_pwm) 
** ��������: ���ö��ת��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //ռ�ձȲ��ܳ������ޣ���ֹ��ѹ��
    //ͬʱ��ֹ�������  
    //���������ʩ�Ǳ�Ҫ��
    if(angle_pwm < STEER_RIGHT)
         angle_pwm = STEER_RIGHT;
    if(angle_pwm > STEER_LEFT)
         angle_pwm = STEER_LEFT;
        
    FTM_PWM_Duty(STEER_FTMN,STEER_FTMCH,angle_pwm);
}


/********************************************************************
** ��������: steerCtrl
** ��������: �ٶȿ����㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void steerCtrl()
{
    /*
    int angle_pwm;
    angle_pwm = 0;    //ȥ��warning
    
    //�Լ��Ķ�������㷨
    
    
    PWMSetSteer(angle_pwm) ; 
    */ 
}


#if STEER_DOUBLE
void PWMSetSteer1(int angle_pwm)         
{
    //ռ�ձȲ��ܳ������ޣ���ֹ��ѹ��
    //ͬʱ��ֹ�������  
    //���������ʩ�Ǳ�Ҫ��
    if(angle_pwm < STEER_RIGHT1)
         angle_pwm = STEER_RIGHT1;
    if(angle_pwm > STEER_LEFT1)
         angle_pwm = STEER_LEFT1;
    
    
    FTM_PWM_Duty(STEER_FTMN,STEER_FTMCH1,angle_pwm);
}


/********************************************************************
** ��������: steerCtrl
** ��������: �ٶȿ����㷨
** ��ڣ�
** ���ڣ�
** ˵��:  
*********************************************************************/
void steerCtrl1()
{
    /*
    int angle_pwm;
    angle_pwm = 0;    //ȥ��warning
    
    //�Լ��Ķ�������㷨
    
    
    
    PWMSetSteer1(angle_pwm) ;  
    */
}

#endif

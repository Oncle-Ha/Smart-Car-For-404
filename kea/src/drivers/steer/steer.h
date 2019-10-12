/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[steer.h] 
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/
#ifndef __STEER_H__
#define __STEER_H__

#include "common.h"
#include "ftm.h"


//Ϊ˫���Ԥ��������ͷ��͵���������� 0
#define STEER_DOUBLE 0


#define STEER_LEFT      1750     //����ڽ�����  �����ֵ�����ڲ��Եģ���Ҹ����Լ��Ķ������
#define STEER_MIDDLE    1600     //����ڽ���ֵ
#define STEER_RIGHT      1450   //����ڽ��Ҽ���  


#define  STEER_FTMN     CFTM1 
#define  STEER_FTMCH    FTM_CH0   //FTM1_CH0��ӦPTH2��
#define  STEER_FREQ     100    //���Ƶ��   ����һ��FTMģ��ֻ�����һ��Ƶ�ʣ�                               //�����������Ҳֻ����һ��Ƶ�� ����ͳһ100Hz
#define  STEER_INIT_VAL 1200   //�����ʼֵ������1/10000  ��1200/10000  = 12%

void steer_init();

void PWMSetSteer(int angle_pwm);

void steerCtrl();

#if STEER_DOUBLE
    #define STEER_LEFT1      2000     //����ڽ�����
    #define STEER_MIDDLE1    1500     //����ڽ���ֵ
    #define STEER_RIGHT1     1000      //����ڽ��Ҽ���
    
    
    //#define  STEER_FTMN     CFTM1  //�����������
    #define  STEER_FTMCH1    FTM_CH1    //FTM1_CH0��ӦPTE7��
    //#define  STEER_FREQ     100    //���Ƶ��   ����һ��FTMģ��ֻ�����һ��Ƶ�ʣ�                               //�����������Ҳֻ����һ��Ƶ�� ����ͳһ100Hz
    #define  STEER_INIT_VAL1 1200   //�����ʼֵ������1/10000  ��1200/10000  = 12%
    void PWMSetSteer1(int angle_pwm);
    void steerCtrl1();
#endif





#endif
#ifndef _fun_h
#define _fun_h

#include "headfile.h"


void  my_delay(long t);
void  delayms(uint32  ms);
void  delayus(uint32  us);


#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )              //�����ֵ
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )              //����Сֵ
#define ABS(x) ((x)<0?-(x):(x))                            //����ֵ����������x�ľ���ֵ
#define LMT(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))           //��x������a��b֮��

int Sprintf(char * szBuffer, const char * szFormat, ...);    //IAR �Դ���sprintf�޷�ת��%f��%e
int32 A2I(const char *); //�ַ���ת��Ϊ���� C�е�atoi
double A2F(const char *str); //�ַ���ת��Ϊ���� C�е�atof





#endif 
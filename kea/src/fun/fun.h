#ifndef _fun_h
#define _fun_h

#include "headfile.h"


void  my_delay(long t);
void  delayms(uint32  ms);
void  delayus(uint32  us);


#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )              //求最大值
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )              //求最小值
#define ABS(x) ((x)<0?-(x):(x))                            //绝对值函数，返回x的绝对值
#define LMT(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))           //将x限制在a到b之间

int Sprintf(char * szBuffer, const char * szFormat, ...);    //IAR 自带的sprintf无法转换%f和%e
int32 A2I(const char *); //字符串转换为整形 C中的atoi
double A2F(const char *str); //字符串转换为浮点 C中的atof





#endif 
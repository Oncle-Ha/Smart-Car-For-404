#include "fun.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//简单延时
void my_delay(long t)
{
    while(t--);
}

void  delayms(uint32  ms)
{

    uint32  i,j; 
    for(i=0;i<ms;i++)
    {
        for(j=CORE_CLK_KHZ/4;j>0;j--)
        {
        }
    }
}

void  delayus(uint32  us)
{
    uint32  i,j;
    for(i=0;i<us;i++)
    {
        for(j=CORE_CLK_KHZ/4000;j>0;j--)
        {
        }
    }
}
//字符串转换为整形 C中的atoi
int32 A2I(const char * str)
{
  int8 sign;
  int32 n=0;
  while(isspace(*str))str++;//跳过空白符;
  sign=(*str=='-')?-1:1;
  if(*str=='+'||*str=='-') str++;//跳过符号 
  while(isspace(*str))str++;//跳过空白符;
  for(n=0;*str>='0'&&*str<='9';str++)
    n=10*n+(*str-'0');//将数字字符转换成整形数字
  return sign *n;
}
//字符串转换为浮点 C中的atof
double A2F(const char *str)
{
	double s = 0.0;
	double d = 10.0;
	int8 indices = 0, sign = 0;	
	while (isspace(*str))str++;//跳过空白符;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-') str++;//跳过符号 
	if (!(*str >= '0'&&*str <= '9'))//如果一开始非数字则退出，返回0.0
		return s;

	while (*str >= '0'&&*str <= '9'&&*str != '.')//计算小数点前整数部分
	{
		s = s * 10.0 + *str - '0';
		str++;
	}

	if (*str == '.')//以后为小数部分
		str++;

	while (*str >= '0'&&*str <= '9')//计算小数部分
	{
		s = s + (*str - '0') / d;
		d *= 10.0;
		str++;
	}

	if (*str == 'e' || *str == 'E')//考虑科学计数法
	{
		str++;		
		for (indices = A2I(str); indices > 0; --indices)
			s *= 10.0;
		for (; indices < 0; ++indices)
			s /= 10.0;
	}
	return s * sign;
}

//IAR 自带的sprintf无法转换%f和%e
int Sprintf(char * szBuffer, const char * szFormat, ...) 
{
	int iReturn; 
	va_list pArgs; 
	va_start(pArgs, szFormat); 
	iReturn = vsprintf(szBuffer, szFormat, pArgs); 
	va_end(pArgs); 
	return iReturn;
}

#include "fun.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

//����ʱ
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
//�ַ���ת��Ϊ���� C�е�atoi
int32 A2I(const char * str)
{
  int8 sign;
  int32 n=0;
  while(isspace(*str))str++;//�����հ׷�;
  sign=(*str=='-')?-1:1;
  if(*str=='+'||*str=='-') str++;//�������� 
  while(isspace(*str))str++;//�����հ׷�;
  for(n=0;*str>='0'&&*str<='9';str++)
    n=10*n+(*str-'0');//�������ַ�ת������������
  return sign *n;
}
//�ַ���ת��Ϊ���� C�е�atof
double A2F(const char *str)
{
	double s = 0.0;
	double d = 10.0;
	int8 indices = 0, sign = 0;	
	while (isspace(*str))str++;//�����հ׷�;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-') str++;//�������� 
	if (!(*str >= '0'&&*str <= '9'))//���һ��ʼ���������˳�������0.0
		return s;

	while (*str >= '0'&&*str <= '9'&&*str != '.')//����С����ǰ��������
	{
		s = s * 10.0 + *str - '0';
		str++;
	}

	if (*str == '.')//�Ժ�ΪС������
		str++;

	while (*str >= '0'&&*str <= '9')//����С������
	{
		s = s + (*str - '0') / d;
		d *= 10.0;
		str++;
	}

	if (*str == 'e' || *str == 'E')//���ǿ�ѧ������
	{
		str++;		
		for (indices = A2I(str); indices > 0; --indices)
			s *= 10.0;
		for (; indices < 0; ++indices)
			s /= 10.0;
	}
	return s * sign;
}

//IAR �Դ���sprintf�޷�ת��%f��%e
int Sprintf(char * szBuffer, const char * szFormat, ...) 
{
	int iReturn; 
	va_list pArgs; 
	va_start(pArgs, szFormat); 
	iReturn = vsprintf(szBuffer, szFormat, pArgs); 
	va_end(pArgs); 
	return iReturn;
}

#include "isr.h"


//����0�����жϷ�������
void UART0_ISR(void)
{    
  DisableInterrupts ;//�����ж�
  uint8_t Data='0';
  if(UART0->S1 & UART_S1_RDRF_MASK)   //�������ݼĴ�����
  {
    Data=uart_getchar(UARTR0);
    //...
  }
  if(UART0->S1  & UART_S1_TDRE_MASK )  //�������ݼĴ�����
  {
    uart_putchar(UARTR0,Data);
    //...
  }
  EnableInterrupts;   //�����ж�
}


//����1�����жϷ�������
void UART1_ISR(void)
{    
  DisableInterrupts ;//�����ж�
  uint8_t Data='1';
  if(UART1->S1 & UART_S1_RDRF_MASK)   //�������ݼĴ�����
  {
    Data=uart_getchar(UARTR1);
    //...
  }
  if(UART1->S1  & UART_S1_TDRE_MASK )  //�������ݼĴ�����
  {
    uart_putchar(UARTR1,Data);
    //...
  }
  EnableInterrupts;   //�����ж�
}

//����2�����жϷ�������
void UART2_ISR(void)
{    
  DisableInterrupts ;//�����ж�
  uint8_t Data='2';
  if(UART2->S1 & UART_S1_RDRF_MASK)   //�������ݼĴ�����
  {
    Data=uart_getchar(UARTR2);
    //...
  }
  if(UART2->S1  & UART_S1_TDRE_MASK )  //�������ݼĴ�����
  {
    uart_putchar(UARTR2,Data);
    //...
  }
  EnableInterrupts;   //�����ж�
}



int stime = 0;  //ϵͳʱ��
//��ʱ��0�жϺ���

void PIT0_ISR(void)
{
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;//����жϱ�־λ

  stime++;  
  uartPrintf(UARTR2,"hello %d\n",stime);
  
}




/*
Ӧ����PTA0-PTD7���ⲿ�ж�

*/
//KBI0�жϺ���
void KBI0_Isr(void)	
{
  
  KBI0->SC |= KBI_SC_KBACK_MASK;       /* clear interrupt flag */
  KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //����жϱ�־λ
  
  if(!gpio_get(PTD5)) // �ж�PTD5�Ƿ��ǵ͵�ƽ
  {
    uartPrintf(UARTR2,"PTD5 interrupt\n");
  }
  
}


/*
Ӧ����PTE0-PTH7���ⲿ�ж�

*/
//KBI1�жϺ���
void KBI1_Isr(void)	
{
  
  KBI1->SC |= KBI_SC_KBACK_MASK;                /* clear interrupt flag */
  KBI1->SC |= KBI_SC_RSTKBSP_MASK ;             //����жϱ�־λ
}
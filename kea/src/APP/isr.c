#include "isr.h"


//串口0接收中断服务例程
void UART0_ISR(void)
{    
  DisableInterrupts ;//关总中断
  uint8_t Data='0';
  if(UART0->S1 & UART_S1_RDRF_MASK)   //接收数据寄存器满
  {
    Data=uart_getchar(UARTR0);
    //...
  }
  if(UART0->S1  & UART_S1_TDRE_MASK )  //发送数据寄存器空
  {
    uart_putchar(UARTR0,Data);
    //...
  }
  EnableInterrupts;   //开总中断
}


//串口1接收中断服务例程
void UART1_ISR(void)
{    
  DisableInterrupts ;//关总中断
  uint8_t Data='1';
  if(UART1->S1 & UART_S1_RDRF_MASK)   //接收数据寄存器满
  {
    Data=uart_getchar(UARTR1);
    //...
  }
  if(UART1->S1  & UART_S1_TDRE_MASK )  //发送数据寄存器空
  {
    uart_putchar(UARTR1,Data);
    //...
  }
  EnableInterrupts;   //开总中断
}

//串口2接收中断服务例程
void UART2_ISR(void)
{    
  DisableInterrupts ;//关总中断
  uint8_t Data='2';
  if(UART2->S1 & UART_S1_RDRF_MASK)   //接收数据寄存器满
  {
    Data=uart_getchar(UARTR2);
    //...
  }
  if(UART2->S1  & UART_S1_TDRE_MASK )  //发送数据寄存器空
  {
    uart_putchar(UARTR2,Data);
    //...
  }
  EnableInterrupts;   //开总中断
}



int stime = 0;  //系统时间
//定时器0中断函数

void PIT0_ISR(void)
{
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;//清除中断标志位

  stime++;  
  uartPrintf(UARTR2,"hello %d\n",stime);
  
}




/*
应用于PTA0-PTD7的外部中断

*/
//KBI0中断函数
void KBI0_Isr(void)	
{
  
  KBI0->SC |= KBI_SC_KBACK_MASK;       /* clear interrupt flag */
  KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //清除中断标志位
  
  if(!gpio_get(PTD5)) // 判断PTD5是否是低电平
  {
    uartPrintf(UARTR2,"PTD5 interrupt\n");
  }
  
}


/*
应用于PTE0-PTH7的外部中断

*/
//KBI1中断函数
void KBI1_Isr(void)	
{
  
  KBI1->SC |= KBI_SC_KBACK_MASK;                /* clear interrupt flag */
  KBI1->SC |= KBI_SC_RSTKBSP_MASK ;             //清除中断标志位
}
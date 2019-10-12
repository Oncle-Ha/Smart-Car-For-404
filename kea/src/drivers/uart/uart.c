#include "uart.h"
#include <stdarg.h>
#include <stdio.h>



volatile UART_Type *UARTx[3]={UART0,UART1,UART2};


/*************************************************************************
*  函数名称：uart_init
*  功能说明：初始化uart模块
*  函数返回：无
*  参数说明：UARTn  :    通道
*           baud_rate  ：波特率 1200  2400  4800 9600 14400
19200  28800  38400  57600  
*  for example           uart_init(UARTR1,9600);
*************************************************************************/
void uart_init (UARTn uratn,uint32_t baud_rate)
{
  uint8_t temp;
  uint16_t  sbr;
  sbr = (uint16_t)(BUS_CLK_HZ/(16*baud_rate)); 
  switch(uratn)
  {
  case UARTR0:
    SIM->SCGC |=  SIM_SCGC_UART0_MASK;
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;   //PTA3 TX ,PTA2 RX  屏蔽掉后RX--B0 ；TX--B1
    SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK ;
    break;
  case UARTR1:
    SIM->SCGC |=  SIM_SCGC_UART1_MASK;
    //SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK ;  //PTF3 TX ,PTF2 RX 屏蔽掉后RX--C6 ；TX--C7
    break ;
  case UARTR2:
    SIM->SCGC |=  SIM_SCGC_UART2_MASK;
    SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK ;  //PTI1 TX ,PTI0 RX 屏蔽掉后RX--D6 ；TX--D7
    break;
  default:
    break;
  }
  temp = UARTx[uratn]->BDH&~UART_BDH_SBR(0X1F);  
  UARTx[uratn]->BDH = temp|UART_BDH_SBR(((sbr & 0x1F00) >> 8)) ;
  UARTx[uratn]->BDL = (uint8_t)(sbr&UART_BDL_SBR_MASK);
  UARTx[uratn]->C1  = 0 ;
  UARTx[uratn]->C2  = (0
                       |UART_C2_TE_MASK
                         |UART_C2_RE_MASK
                           );
  
}

/*************************************************************************
*  函数名称：uart_putchar
*  功能说明：发送一个字节
*  函数返回：无
*  参数说明：UARTn :模块号（UART0~UART2）
*           send   :发送的数据
*  for example      uart_putchar(UARTR1,1);
*************************************************************************/
void uart_putchar(UARTn uratn,uint8_t send)
{
  while((UARTx[uratn]->S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/							/* Read UART2_S1 register*/
  (void)UARTx[uratn]->S1;					/* Read UART2_S1 register*/
  UARTx[uratn]->D=send;						/* Send data*/
}

/*************************************************************************
*  函数名称：uart_getchar
*  功能说明：接受一个数据
*  函数返回：接受数据
*  参数说明：UARTn  :模块号（UART0~UART2）
*  for example       data = uart_getchar(UART1);
*************************************************************************/
uint8_t uart_getchar(UARTn uratn)
{
  
  uint8_t recieve;
  while(( UARTx[uratn]->S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/								/* Read UART2_S1 register*/
  recieve= UARTx[uratn]->D;								/* Read received data*/
  return recieve;
  
}

/*!
 *  @brief      发送字符串(遇 NULL 停止发送)
 *  @param      UARTn       模块号（UART0~UART5）
 *  @param      str         字符串地址
 *  @since      v5.0
 *  Sample usage:       uart_putstr (UART3,"1234567"); //实际发送了7个字节
 */
void uart_putstr (UARTn uratn, const uint8 *str)
{
    while(*str)
        uart_putchar(uratn, *str++);
}


/*!
 *  @brief      发送指定len个字节长度数组 （包括 NULL 也会发送）
 *  @param      UARTn       模块号（UART0~UART5）
 *  @param      buff        数组地址
 *  @param      len         发送数组的长度
 *  @since      v5.0
 *  Sample usage:       uart_putbuff (UART3,"1234567", 3); //实际发送了3个字节'1','2','3'
 */
void uart_putbuff (UARTn uratn, uint8 *buff, uint32 len)
{
    while(len--)
    {
        uart_putchar(uratn, *buff);
        buff++;
    }
}


/*!
 *  @brief      开串口接收中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_rx_irq_en(UART3);         //开串口3接收中断
 */
void uart_rx_irq_en(UARTn uratn)
{
  UARTx[uratn]->C2 |= UART_C2_RIE_MASK;                          //使能UART接收中断
  if(uratn == UARTR0)
    NVIC_EnableIRQ(UART0_IRQn);                  //使能IRQ中断
  else if(uratn == UARTR1)
    NVIC_EnableIRQ(UART1_IRQn);                  //使能IRQ中断
  else if(uratn == UARTR2)
    NVIC_EnableIRQ(UART2_IRQn);                  //使能IRQ中断
}

/*!
 *  @brief      开串口发送中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_en(UART3);         //开串口3发送中断
 */
void uart_tx_irq_en(UARTn uratn)
{
	UARTx[uratn]->C2 |= UART_C2_TIE_MASK;                          //使能UART发送中断
	if (uratn == UARTR0)
		NVIC_EnableIRQ(UART0_IRQn);                  //使能IRQ中断
	else if (uratn == UARTR1)
		NVIC_EnableIRQ(UART1_IRQn);                  //使能IRQ中断
	else if (uratn == UARTR2)
		NVIC_EnableIRQ(UART2_IRQn);                  //使能IRQ中断
}

/*!
 *  @brief      开串口发送完成中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_en(UART3);         //开串口3发送中断
 */
void uart_txc_irq_en(UARTn uratn)
{
    UARTx[uratn]->C2 |= UART_C2_TCIE_MASK;                         //使能UART发送中断
	if (uratn == UARTR0)
		NVIC_EnableIRQ(UART0_IRQn);                  //使能IRQ中断
	else if (uratn == UARTR1)
		NVIC_EnableIRQ(UART1_IRQn);                  //使能IRQ中断
	else if (uratn == UARTR2)
		NVIC_EnableIRQ(UART2_IRQn);                  //使能IRQ中断
}

/*!
 *  @brief      关串口接收中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_rx_irq_dis(UART3);         //关串口3接收中断
 */
void uart_rx_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_RIE_MASK;                         //禁止UART接收中断

    //如果发送中断还没有关，则不关闭IRQ
    if(!(UARTx[uratn]->C2 & (UART_C2_TIE_MASK | UART_C2_TCIE_MASK)) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //禁用IRQ中断
    }
}

/*!
 *  @brief      关串口发送中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_dis(UART3);         //关串口3发送中断
 */
void uart_txc_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_TCIE_MASK;                        //禁止UART发送完成中断

    //如果接收中断还没有关，则不关闭IRQ
    if(!(UARTx[uratn]->C2 & UART_C2_RIE_MASK) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //禁用IRQ中断
    }
}

/*!
 *  @brief      关串口发送中断
 *  @param      UARTn       模块号（UART0~UART5）
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_dis(UART3);         //关串口3发送中断
 */
void uart_tx_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_TIE_MASK;                         //禁止UART发送中断

    //如果接收中断还没有关，则不关闭IRQ
    if(!(UARTx[uratn]->C2 & UART_C2_RIE_MASK) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //禁用IRQ中断
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //禁用IRQ中断
    }
}

//向虚拟示波器发送一个数据帧
void uart_sendware(UARTn uratn,void *wareaddr, uint32 waresize)
{
#define CMD_WARE     3
    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart_putbuff(uratn, cmdf, sizeof(cmdf));    //先发送前命令
    uart_putbuff(uratn, wareaddr, waresize);    //发送数据
    uart_putbuff(uratn, cmdr, sizeof(cmdr));    //发送后命令

}

void uartPrintf(UARTn uratn,char *pcFmt,...)
{
        va_list ap;
        char pbString[256];

        va_start(ap,pcFmt);
        vsprintf(pbString,pcFmt,ap);
		uart_putstr(uratn,pbString);
        va_end(ap);
}



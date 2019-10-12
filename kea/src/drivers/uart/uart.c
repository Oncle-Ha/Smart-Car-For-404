#include "uart.h"
#include <stdarg.h>
#include <stdio.h>



volatile UART_Type *UARTx[3]={UART0,UART1,UART2};


/*************************************************************************
*  �������ƣ�uart_init
*  ����˵������ʼ��uartģ��
*  �������أ���
*  ����˵����UARTn  :    ͨ��
*           baud_rate  �������� 1200  2400  4800 9600 14400
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
    SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;   //PTA3 TX ,PTA2 RX  ���ε���RX--B0 ��TX--B1
    SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK ;
    break;
  case UARTR1:
    SIM->SCGC |=  SIM_SCGC_UART1_MASK;
    //SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK ;  //PTF3 TX ,PTF2 RX ���ε���RX--C6 ��TX--C7
    break ;
  case UARTR2:
    SIM->SCGC |=  SIM_SCGC_UART2_MASK;
    SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK ;  //PTI1 TX ,PTI0 RX ���ε���RX--D6 ��TX--D7
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
*  �������ƣ�uart_putchar
*  ����˵��������һ���ֽ�
*  �������أ���
*  ����˵����UARTn :ģ��ţ�UART0~UART2��
*           send   :���͵�����
*  for example      uart_putchar(UARTR1,1);
*************************************************************************/
void uart_putchar(UARTn uratn,uint8_t send)
{
  while((UARTx[uratn]->S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/							/* Read UART2_S1 register*/
  (void)UARTx[uratn]->S1;					/* Read UART2_S1 register*/
  UARTx[uratn]->D=send;						/* Send data*/
}

/*************************************************************************
*  �������ƣ�uart_getchar
*  ����˵��������һ������
*  �������أ���������
*  ����˵����UARTn  :ģ��ţ�UART0~UART2��
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
 *  @brief      �����ַ���(�� NULL ֹͣ����)
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @param      str         �ַ�����ַ
 *  @since      v5.0
 *  Sample usage:       uart_putstr (UART3,"1234567"); //ʵ�ʷ�����7���ֽ�
 */
void uart_putstr (UARTn uratn, const uint8 *str)
{
    while(*str)
        uart_putchar(uratn, *str++);
}


/*!
 *  @brief      ����ָ��len���ֽڳ������� ������ NULL Ҳ�ᷢ�ͣ�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @param      buff        �����ַ
 *  @param      len         ��������ĳ���
 *  @since      v5.0
 *  Sample usage:       uart_putbuff (UART3,"1234567", 3); //ʵ�ʷ�����3���ֽ�'1','2','3'
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
 *  @brief      �����ڽ����ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_rx_irq_en(UART3);         //������3�����ж�
 */
void uart_rx_irq_en(UARTn uratn)
{
  UARTx[uratn]->C2 |= UART_C2_RIE_MASK;                          //ʹ��UART�����ж�
  if(uratn == UARTR0)
    NVIC_EnableIRQ(UART0_IRQn);                  //ʹ��IRQ�ж�
  else if(uratn == UARTR1)
    NVIC_EnableIRQ(UART1_IRQn);                  //ʹ��IRQ�ж�
  else if(uratn == UARTR2)
    NVIC_EnableIRQ(UART2_IRQn);                  //ʹ��IRQ�ж�
}

/*!
 *  @brief      �����ڷ����ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_en(UART3);         //������3�����ж�
 */
void uart_tx_irq_en(UARTn uratn)
{
	UARTx[uratn]->C2 |= UART_C2_TIE_MASK;                          //ʹ��UART�����ж�
	if (uratn == UARTR0)
		NVIC_EnableIRQ(UART0_IRQn);                  //ʹ��IRQ�ж�
	else if (uratn == UARTR1)
		NVIC_EnableIRQ(UART1_IRQn);                  //ʹ��IRQ�ж�
	else if (uratn == UARTR2)
		NVIC_EnableIRQ(UART2_IRQn);                  //ʹ��IRQ�ж�
}

/*!
 *  @brief      �����ڷ�������ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_en(UART3);         //������3�����ж�
 */
void uart_txc_irq_en(UARTn uratn)
{
    UARTx[uratn]->C2 |= UART_C2_TCIE_MASK;                         //ʹ��UART�����ж�
	if (uratn == UARTR0)
		NVIC_EnableIRQ(UART0_IRQn);                  //ʹ��IRQ�ж�
	else if (uratn == UARTR1)
		NVIC_EnableIRQ(UART1_IRQn);                  //ʹ��IRQ�ж�
	else if (uratn == UARTR2)
		NVIC_EnableIRQ(UART2_IRQn);                  //ʹ��IRQ�ж�
}

/*!
 *  @brief      �ش��ڽ����ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_rx_irq_dis(UART3);         //�ش���3�����ж�
 */
void uart_rx_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_RIE_MASK;                         //��ֹUART�����ж�

    //��������жϻ�û�йأ��򲻹ر�IRQ
    if(!(UARTx[uratn]->C2 & (UART_C2_TIE_MASK | UART_C2_TCIE_MASK)) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //����IRQ�ж�
    }
}

/*!
 *  @brief      �ش��ڷ����ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_dis(UART3);         //�ش���3�����ж�
 */
void uart_txc_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_TCIE_MASK;                        //��ֹUART��������ж�

    //��������жϻ�û�йأ��򲻹ر�IRQ
    if(!(UARTx[uratn]->C2 & UART_C2_RIE_MASK) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //����IRQ�ж�
    }
}

/*!
 *  @brief      �ش��ڷ����ж�
 *  @param      UARTn       ģ��ţ�UART0~UART5��
 *  @since      v5.0
 *  Sample usage:       uart_tx_irq_dis(UART3);         //�ش���3�����ж�
 */
void uart_tx_irq_dis(UARTn uratn)
{
    UARTx[uratn]->C2 &= ~UART_C2_TIE_MASK;                         //��ֹUART�����ж�

    //��������жϻ�û�йأ��򲻹ر�IRQ
    if(!(UARTx[uratn]->C2 & UART_C2_RIE_MASK) )
    {
		if (uratn == UARTR0)
			NVIC_DisableIRQ(UART0_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR1)
			NVIC_DisableIRQ(UART1_IRQn);                  //����IRQ�ж�
		else if (uratn == UARTR2)
			NVIC_DisableIRQ(UART2_IRQn);                  //����IRQ�ж�
    }
}

//������ʾ��������һ������֡
void uart_sendware(UARTn uratn,void *wareaddr, uint32 waresize)
{
#define CMD_WARE     3
    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_putbuff(uratn, cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    uart_putbuff(uratn, wareaddr, waresize);    //��������
    uart_putbuff(uratn, cmdr, sizeof(cmdr));    //���ͺ�����

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



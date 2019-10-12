#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include "common.h"
  //#include "wdog.h"
#include "derivative.h"
  
  typedef enum  UARTn
  {
    //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
    UARTR0 = 0,    //           
    UARTR1 = 1,    //           
    UARTR2 = 2,    //           
    
  } UARTn;
  
  extern void uart_init (UARTn uratn,uint32_t baud_rate) ;       //uart��ʼ��
  extern void uart_putchar(UARTn uratn,uint8_t send);            //����1���ֽ�
  extern uint8_t uart_getchar(UARTn uratn) ;                     //����1���ֽ�
  
  extern void uart_putbuff   (UARTn , uint8 *buff, uint32 len);//����len���ֽ�buff
  extern void uart_putstr    (UARTn , const uint8 *str);       //�����ַ���
  
  extern void uart_rx_irq_en (UARTn);                          //�����ڽ����ж�
  extern void uart_tx_irq_en (UARTn);                          //�����ڷ����ж�
  extern void uart_txc_irq_en (UARTn);                         //�����ڷ�������ж�

  extern void uart_rx_irq_dis(UARTn);                          //�ش��ڽ����ж�
  extern void uart_tx_irq_dis(UARTn);                          //�ش��ڷ����ж�
  extern void uart_txc_irq_dis(UARTn);                         //�ش��ڷ�������ж�
  
  void uart_sendware(UARTn uratn,void *wareaddr, uint32 waresize);//������ʾ��������һ������֡
  void uartPrintf(UARTn uratn,char *pcFmt,...);    
#endif /* #ifndef _UART_H_ */
  
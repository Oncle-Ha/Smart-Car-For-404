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
    //初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请自行修改 uart_init
    UARTR0 = 0,    //           
    UARTR1 = 1,    //           
    UARTR2 = 2,    //           
    
  } UARTn;
  
  extern void uart_init (UARTn uratn,uint32_t baud_rate) ;       //uart初始化
  extern void uart_putchar(UARTn uratn,uint8_t send);            //发送1个字节
  extern uint8_t uart_getchar(UARTn uratn) ;                     //接收1个字节
  
  extern void uart_putbuff   (UARTn , uint8 *buff, uint32 len);//发送len个字节buff
  extern void uart_putstr    (UARTn , const uint8 *str);       //发送字符串
  
  extern void uart_rx_irq_en (UARTn);                          //开串口接收中断
  extern void uart_tx_irq_en (UARTn);                          //开串口发送中断
  extern void uart_txc_irq_en (UARTn);                         //开串口发送完成中断

  extern void uart_rx_irq_dis(UARTn);                          //关串口接收中断
  extern void uart_tx_irq_dis(UARTn);                          //关串口发送中断
  extern void uart_txc_irq_dis(UARTn);                         //关串口发送完成中断
  
  void uart_sendware(UARTn uratn,void *wareaddr, uint32 waresize);//向虚拟示波器发送一个数据帧
  void uartPrintf(UARTn uratn,char *pcFmt,...);    
#endif /* #ifndef _UART_H_ */
  
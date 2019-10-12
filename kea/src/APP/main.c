// 流水灯

#include "headfile.h"

/*
  ADC_CHANNEL_AD0 -------------- A0   
  ADC_CHANNEL_AD1 -------------- A1
  ADC_CHANNEL_AD2 -------------- A6 
  ADC_CHANNEL_AD3 -------------- A7
  ADC_CHANNEL_AD4 -------------- B0
  ADC_CHANNEL_AD5 -------------- B1  
  ADC_CHANNEL_AD6 -------------- B2
  ADC_CHANNEL_AD7 -------------- B3
  ADC_CHANNEL_AD8 -------------- C0
  ADC_CHANNEL_AD9 -------------- C1 
  ADC_CHANNEL_AD10 ------------- C2
  ADC_CHANNEL_AD11 ------------- C3
  ADC_CHANNEL_AD12 ------------- F4
  ADC_CHANNEL_AD13 ------------- F5 
  ADC_CHANNEL_AD14 ------------- F6
  ADC_CHANNEL_AD15 ------------- F7

*/
int LED_state[4] = {1, 0, 0, 0};





//#if -#elif -#endif 
#if 1
void main()
{
    DisableInterrupts;
    PIT_Init(PIT_CHANNEL0, 1);
    uart_init(UARTR0, 9600);
    gpio_init(PTG0, 1, 1);
    gpio_init(PTG1, 1, 0);
    gpio_init(PTG2, 1, 0);
    gpio_init(PTG3, 1, 0);

    PIT_IRQ_EN(PIT_CHANNEL0);
    uart_rx_irq_en(UARTR0);
    EnableInterrupts;
    while(1) ;

    return;
）
#elif 0
void main(){
    DisableInterrupts;


    EnableInterrupts;

    return;
}





















  

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
s
*/
int LED_state[4] = {1, 0, 0, 0};
int SW_Opt = 0;//拨码开关的01表示
double systime=0, sin_systime;


void main_0()
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
}

void main_1()
{
  DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 100);
  uart_init(UARTR1, 115200);

  PIT_IRQ_EN(PIT_CHANNEL0);
  uart_rx_irq_en(UARTR1);

  EnableInterrupts;

  while(1){
    uart_sendware(UARTR0,&sin_systime,sizeof(sin_systime));
  }
}

void main_2()
{
	DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 1);//初始化中断计时器PIT0
  uart_init(UARTR0, 9600);//初始化串口UARTR0
  FTM_PWM_init(CFTM0, FTM_CH0, 50, 10);//初始化CFTM0输出PWM的参数，通道为FTM_CH0
  ftm_count_init(CFTM1);//初始化用于测PWM波的CFTM1
  PIT_IRQ_EN(PIT_CHANNEL0);//启动PIT0
	EnableInterrupts; 
  while(1) ;
}

void main_3()
{
  DisableInterrupts;
  uart_init(UARTR0, 9600);
  ADC_Init(ADC_CHANNEL_AD6,ADC_12BIT);
  EnableInterrupts;

  while(1){
    int val = adc_once(ADC_CHANNEL_AD6);
    uart_sendware(UARTR0, &val, sizeof(val));
  }
}

//#if -#elif -#endif 
#if 1
void main()
{
    SW_Opt |= (gpio_get(PTF4));
    SW_Opt |= (gpio_get(PTF5)) << 1;
    SW_Opt |= (gpio_get(PTF6)) << 2;
    SW_Opt |= (gpio_get(PTF7)) << 3;
    switch (SW_Opt)
    {
    case 0:
      main_0();
      break;
    case 1:
      main_1();
      break;
    case 2:
      main_2();
      break;
    case 3:
      main_3();
      break;  
    default:
      break;
    }
    return;
}
#elif 
 

void main(){
    DisableInterrupts;


    EnableInterrupts;

    return;
}



#endif


















  

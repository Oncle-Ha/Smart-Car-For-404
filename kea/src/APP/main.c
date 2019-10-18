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
int LED_state[4] = {0, 0, 0, 0};
int SW_Opt = 0; //拨码开关的01表示
int bupt = 0, Key = 0;
double systime = 0, sin_systime;

void main_0()
{
  DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 1);
  uart_init(UARTR0, 9600);
  PIT_IRQ_EN(PIT_CHANNEL0);
  uart_rx_irq_en(UARTR0);
  EnableInterrupts;
  while (1)
  {
    if (SW_Opt != 0)
      break;
  }
  PIT_IRQ_DIS(PIT_CHANNEL0);
  uart_rx_irq_dis(UARTR0);
}

void main_1_0()
{
  DisableInterrupts;
  uart_init(UARTR0, 115200);

  uart_rx_irq_en(UARTR0);
  EnableInterrupts;

  while (LED_state[0] == 1)
  {}
  
  uart_rx_irq_dis(UARTR0);
}
void main_1_1()
{
  DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 100);
  uart_init(UARTR0, 9600);

  PIT_IRQ_EN(PIT_CHANNEL0);
  uart_rx_irq_en(UARTR0);
  EnableInterrupts;

  while (LED_state[1] == 1){}

  PIT_IRQ_DIS(PIT_CHANNEL0);
  uart_rx_irq_dis(UARTR0);
}
void main_1_2()
{
  DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 100);
  uart_init(UARTR0, 9600);

  PIT_IRQ_EN(PIT_CHANNEL0);
  uart_rx_irq_en(UARTR0);
  EnableInterrupts;

  while (LED_state[2] == 1)
  {
    uart_sendware(UARTR0, &sin_systime, sizeof(sin_systime));
  }
  PIT_IRQ_DIS(PIT_CHANNEL0);
  uart_rx_irq_dis(UARTR0);
}
void main_1_3()
{
  DisableInterrupts;
  uart_init(UARTR0, 9600);
  uart_rx_irq_en(UARTR0);
  EnableInterrupts;
  while (LED_state[3] == 1)
  {}
  
  uart_rx_irq_dis(UARTR0);
}
void main_1()
{
  while (1)
  {
    if (SW_Opt != 1)
      break;
    if (LED_state[0])
    {
      main_1_0();
    }
    else if (LED_state[1])
    {
      main_1_1();
    }
    else if (LED_state[2])
    {
      main_1_2();
    }
    else if (LED_state[3])
    {
      main_1_3();
    }
  }
}

void main_2()
{
  DisableInterrupts;
  PIT_Init(PIT_CHANNEL0, 1);            //初始化中断计时器PIT0
  uart_init(UARTR0, 9600);              //初始化串口UARTR0
  FTM_PWM_init(CFTM0, FTM_CH0, 50, 10); //初始化CFTM0输出PWM的参数，通道为FTM_CH0
  ftm_count_init(CFTM1);                //初始化用于测PWM波的CFTM1

  uart_rx_irq_en(UARTR0);
  PIT_IRQ_EN(PIT_CHANNEL0); //启动PIT0
  EnableInterrupts;
  while (1)
  {
    if (SW_Opt != 2)
      break;
  }
  PIT_IRQ_DIS(PIT_CHANNEL0);
  uart_rx_irq_dis(UARTR0);
}

void main_3()
{
  DisableInterrupts;
  uart_init(UARTR0, 9600);
  ADC_Init(ADC_CHANNEL_AD6, ADC_12BIT);

  uart_rx_irq_en(UARTR0);
  EnableInterrupts;

  while (1)
  {
    if (SW_Opt != 3)
      break;
    int val = adc_once(ADC_CHANNEL_AD6);
    uart_sendware(UARTR0, &val, sizeof(val));
  }
  uart_rx_irq_dis(UARTR0);
}

//#if -#elif -#endif

PTxn KBI_USE_PT1[8] = {PTF0, PTF1, PTF2, PTF3, PTF4, PTF5, PTF6, PTF7};
PTxn LED_USE_PT[4] = {PTG0, PTG1, PTG2, PTG3};
void main()
{
  DisableInterrupts;

  for (int i = 0; i < 8; ++i)
    gpio_init(KBI_USE_PT1[i], 0, 0);
  for (int i = 0; i < 4; ++i)
    gpio_init(LED_USE_PT[i], 1, 0);
  KBI_Init(KBIX0, PTD4, KBI_FALLING_LOW);
  for (int i = 0; i < 4; ++i)
    KBI_Init(KBIX1, KBI_USE_PT1[i] - 32, KBI_FALLING_LOW);
  // for(int i = 4; i < 8; ++i)
  //   KBI_Init(KBIX1 , KBI_USE_PT1[i] - 32, KBI_RISING__HIGH);
  for (int i = 0; i < 4; ++i)
    KBI_Enable(KBIX1, KBI_USE_PT1[i] - 32);
  KBI_Enable(KBIX0, PTD4);

  EnableInterrupts;

  SW_Opt = 0;
  SW_Opt |= (gpio_get(PTF4));
  SW_Opt |= (gpio_get(PTF5)) << 1;
  SW_Opt |= (gpio_get(PTF6)) << 2;
  SW_Opt |= (gpio_get(PTF7)) << 3;
  while (1)
  {
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
  }
  return;
}

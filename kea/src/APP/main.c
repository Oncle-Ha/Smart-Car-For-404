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






//#if -#elif -#endif 
#if 0
//串口打印 “Hello world!”
void main()
{
  DisableInterrupts;  
  uart_init(UARTR2,38400); 
  EnableInterrupts; 
  while(1)
  {
    uartPrintf(UARTR2,"hello world\n");
    delayus(1000000);
  }
}
#elif 0       

void main()
{
  int result;
  DisableInterrupts;  
  uart_init(UARTR2,38400);
  uartPrintf(UARTR2,"GPIO\n");
 
  //GPO
  gpio_init (PTF3, GPO,HIGH);      
  //GPI
  gpio_init (PTC5, GPI, LOW);    
  
  result = gpio_get(PTC5);        
  uartPrintf(UARTR2,"result=%d\n",result);
  
  EnableInterrupts;
  while(1)                              
  {
     gpio_turn(PTF3);
     delayms(100);
  } 
}
#elif 0

void main()
{
  int32 adResult8[5] = 0;
  DisableInterrupts;  
  uart_init(UARTR2,38400);
  uartPrintf(UARTR2,"AD\n");
  ADC_Init(ADC_CHANNEL_AD1,ADC_8BIT); //PTA0 
  
  EnableInterrupts;
  while(1)
  {
    int i;
      for(i=0;i<5;i++)
    adResult8[i] = adc_once(ADC_CHANNEL_AD1);
    
    for(i=0;i<5;i++)
      uartPrintf(UARTR2,"(0~255): %d ",adResult8[i]);
    uartPrintf(UARTR2,"\n");

    delayms(1000);
;
  }
}
#elif 0

void main()
{  
  DisableInterrupts;  
  uart_init(UARTR2,38400);
  uartPrintf(UARTR2,"FTM\n");
  FTM_PWM_init(CFTM2, FTM_CH0, 10000, 2000);//PWM2 PTC0 10khz,20%占空比
  EnableInterrupts;
  while(1)
  {
  }
}
#elif 0

void main()
{
  int i = 0;
  DisableInterrupts;  
  uart_init(UARTR2, 38400);
  gpio_init (PTF3, GPO,HIGH);
  uartPrintf(UARTR2,"EXTI \n");
  KBI_Init(KBIX0, 29, KBI_FALLING_LOW);//PTD5     
  
  EnableInterrupts;
  while(1)
  {
    gpio_turn(PTF3);
    delayms(1000);
  }
}
#elif 0

void main()
{
  DisableInterrupts;  
  uart_init(UARTR2, 38400);
  uartPrintf(UARTR2,"PIT定时中断\n");
  PIT_Init(PIT_CHANNEL0, 100);    //PIT0 内部中断 每秒执行100次            
  PIT_IRQ_EN(PIT_CHANNEL0);
  EnableInterrupts;
  
  while(1)
  {
    
  }
}

#elif 0
void main()
{
  DisableInterrupts;
  uart_init(UARTR2, 38400);
  uart_rx_irq_en(UARTR2);    //开启串口2的接收中断服务函数
  EnableInterrupts;
  while(1)
  {}
}


#elif 0
void main()
{
  DisableInterrupts;

  steer_init();  //  初始化舵机     H2管脚
  PWMSetSteer(1500);  //设置占空比 改变舵机角度
  EnableInterrupts;
  while(1)
  {}
}


#elif 1
void main()
{
  DisableInterrupts;

  motor_init();    //初始化电机
  PWMSetMotor2(5000,5000);  //设置两个电机的pwm波占空比 
  EnableInterrupts;
  while(1)
  {}
}


#elif 0


void main()
{
  uint32 temp1=0,temp2=0;
  int speedl,speedr;
  DisableInterrupts;
  uart_init(UARTR2,38400);
  ftm_count_init(CFTM0);   //E0管脚为测速管脚               E0接编码器LSB 
  gpio_init(PTC6,GPI,0);    //用于判断方向                  C6接编码器DIR 
  port_pull(PTC6);          //IO上拉
    
  ftm_count_init(CFTM1);    //E7管脚为测速管脚              E7接编码器LSB
  gpio_init(PTC7,GPI,0);    //用于判断方向                  C7接编码器DIR
  port_pull(PTC7);          //IO上拉

  EnableInterrupts;
  while(1)
  {
    temp1 = ftm_count_get(CFTM0);  
    ftm_count_clean(CFTM0);
    temp2 = ftm_count_get(CFTM1);
    ftm_count_clean(CFTM1);
    
    //根据方向信号判断正负，假设方向信号是高电平时为反转
    if(gpio_get(PTC6))    
      speedl = -((int16)(temp1));//速度取负
    else                
      speedl = temp1;             
    if(gpio_get(PTC7))    
      speedr = -((int16)(temp2));//速度取负
    else                
      speedr = temp2;
    
    uartPrintf(UARTR2,"%d  %d\n",speedl,speedr);
    delayms(1000);
  }
}



#endif 




















  

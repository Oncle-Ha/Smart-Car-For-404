#include "isr.h"
extern int LED_state[4];
extern int bupt;
extern int Key;
extern int SW_Opt; //拨码开关的01表示
int stime = 0;     //系统时间
//串口0接收中断服务例程
void UART0_ISR_0(void)
{
    DisableInterrupts; //关总中断
    uint8_t Data = '0';
    if (UART0->S1 & UART_S1_RDRF_MASK) //接收数据寄存器满
    {
        Data = uart_getchar(UARTR0);
        if (Data == 's')
        {
            uart_putchar(UARTR0, 's');
            PIT_IRQ_EN(PIT_CHANNEL0);
        }
        else if (Data == 'p')
        {
            uart_putchar(UARTR0, 'p');
            PIT_IRQ_DIS(PIT_CHANNEL0);
        }
    }
    EnableInterrupts; //开总中断
}
// 回环测试用开关1， 波特率115200
void UART0_ISR_1(void)
{
    DisableInterrupts; //关总中断
    uint8_t Data = '1';
    if(LED_state[0] == 1)
    {
        Data = uart_getchar(UARTR0);  
        uart_putchar(UARTR0, Data);
    }
    else if(LED_state[3] == 1) {
        Data = uart_getchar(UARTR0);
        if(!Key)
        {
            uart_putchar(UARTR0, Data);
        }
        else
        {
            uint8_t d = (Data - 'a' + 2) % 26;
            uart_putchar(UARTR0, 'a' + d);
        }
        if(Data == 'b'){
            bupt = 1;
        }
        else if(bupt == 1 && Data == 'u'){
            bupt = 2;
        }
        else if(bupt == 2 && Data == 'p'){
            bupt = 3;
        }
        else if(bupt == 3 && Data == 't'){
            bupt = 0;
            Key ^= 1;
        }
        else{
            bupt = 0;
        }
    }
   

    EnableInterrupts; //开总中断
}
//
void UART0_ISR_2(void)
{
    DisableInterrupts; //关总中断
    

    EnableInterrupts; //开总中断
}

void UART0_ISR(void)
{
    switch (SW_Opt)
    {
    case 0:
        UART0_ISR_0();
        break;
    case 1:
        UART0_ISR_1();
        break;
    default:
        break;
    }
}

//串口1接收中断服务例程
void UART1_ISR(void)
{
    DisableInterrupts; //关总中断
    uint8_t Data = '1';
    if (UART1->S1 & UART_S1_RDRF_MASK) //接收数据寄存器满
    {
        Data = uart_getchar(UARTR1);
        //...
    }
    if (UART1->S1 & UART_S1_TDRE_MASK) //发送数据寄存器空
    {
        uart_putchar(UARTR1, Data);
        //...
    }
    EnableInterrupts; //开总中断
}

//串口2接收中断服务例程
void UART2_ISR(void)
{
    DisableInterrupts; //关总中断
    uint8_t Data = '2';
    if (UART2->S1 & UART_S1_RDRF_MASK) //接收数据寄存器满
    {
        Data = uart_getchar(UARTR2);
        //...
    }
    if (UART2->S1 & UART_S1_TDRE_MASK) //发送数据寄存器空
    {
        uart_putchar(UARTR2, Data);
        //...
    }
    EnableInterrupts; //开总中断
}

void PIT0_ISR_0(void)
{
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; //清除中断标志位

    // stime++;
    // uartPrintf(UARTR2,"hello %d\n",stime);
    int temp = LED_state[0];
    LED_state[0] = LED_state[3];
    LED_state[3] = LED_state[2];
    LED_state[2] = LED_state[1];
    LED_state[1] = temp;
    gpio_set(PTG0, LED_state[0]);
    gpio_set(PTG1, LED_state[1]);
    gpio_set(PTG2, LED_state[2]);
    gpio_set(PTG3, LED_state[3]);

}

extern double systime, sin_systime;
int Upper = -1;
extern uint8_t To_Matrix[128][8];

void PIT0_ISR_1(void)
{
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;

    if(LED_state[1])
    {
        systime += 0.01;
        sin_systime = sin(systime);
        uartPrintf(UARTR0, "%.6lf\n", sin_systime);
    }else if(LED_state[4])
    {
        systime += 0.1;
        sin_systime = sin(systime);
        if(Upper < 127) ++Upper;
        uint8_t x, y;
        Transform(Upper, sin_systime, &x, &y);
        if(Upper == 127){
            for(int i = 0; i < Upper; ++i){
                for(int j = 0; j < 8; ++j){
                    To_Matrix[i][j] = To_Matrix[i + 1][j];
                }
            }
        }
        for(int j = 0; j < 8; ++j)
            To_Matrix[Upper][j] = 0;

        Evaluate(x, y, 1);
        Show_Matrix();

    }
    //预计加个OLED显示Sint函数 LED_state[4]

}

void PIT0_ISR_2(void)
{
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
    uartPrintf(UARTR0, "%d\n", ftm_count_get(CFTM1));
    ftm_count_clean(CFTM1);
}

uint8_t time_8 = 0;//PIT0_8进了几次，即多少ms
uint16_t cnt_8 = 0;//PWM的占空比
void PIT0_ISR_8(void){
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
    ++time_8; 
    if(cnt_8 < 1000 && time_8 % 1 == 0){
        ++cnt_8;
        FTM_PWM_Duty(CFTM0, FTM_CH0, cnt_8);
    }
    if(time_8 % 10 == 0){
        int val = adc_once(ADC_CHANNEL_AD6);
        uart_sendware(UARTR0, &val, sizeof(val));
    }
}
//定时器0中断函数

void PIT0_ISR(void)
{
    switch (SW_Opt)
    {
    case 0:
        PIT0_ISR_0();
        break;
    case 1:
        PIT0_ISR_1();
        break;
    case 2:
        PIT0_ISR_2();
        break;
    case 8:
        PIT0_ISR_8();
        break;
    default:
        break;
    }
}


/*
应用于PTA0-PTD7的外部中断

*/
//KBI0中断函数

// void KBI0_Isr(void)
// {

//     KBI0->SC |= KBI_SC_KBACK_MASK;   /* clear interrupt flag */
//     KBI0->SC |= KBI_SC_RSTKBSP_MASK; //清除中断标志位

//     if (!gpio_get(PTD5)) // 判断PTD5是否是低电平
//     {
//         uartPrintf(UARTR2, "PTD5 interrupt\n");
//     }
// }

extern int num_16_base;
extern PTxn LED_USE_PT[4];
const int time_10_ms = 10 * CORE_CLK_KHZ / 4;

int Button_Balance(PTxn ptxn){//按键消抖，返回是否为正常按下
    int low_level_time = 0;
    while(!gpio_get(ptxn)) ++low_level_time;//消抖
    return low_level_time > time_10_ms;
}

void KBI0_Isr_1(){
    if (Button_Balance(PTD4))
    {
        LED_state[4] ^= 1;
        // gpio_set(PTG3, LED_state[3]);
    }
}

void KBI0_Isr_4(){//16进制显示
    
    if(Button_Balance(PTD4)){//
        if(num_16_base == 15){
            num_16_base = 0;

            gpio_set(PTH6, 1);
            delayms(1000);//享受1s的尖叫
            gpio_set(PTH6, 0);
        }
        else ++num_16_base;
        for(int i = 0; i < 4; ++i){
            LED_state[i] = ( (num_16_base & (1 << i) )> 0);
            gpio_set(LED_USE_PT[i], LED_state[i]);
        }
    }

}

void KBI0_Isr_5(){//OLED清屏
    if(Button_Balance(PTD4)){
        OLED_CLS();
        OLED_Set_Pos(0, 0);
    }
}

void KBI0_Isr(void)
{

    KBI0->SC |= KBI_SC_KBACK_MASK;   /* clear interrupt flag */
    KBI0->SC |= KBI_SC_RSTKBSP_MASK; //清除中断标志位
    switch (SW_Opt) {
        case 1:
            KBI0_Isr_1();
            break;
        case 4 :
            KBI0_Isr_4();
            break;
        case 5 :
            KBI0_Isr_5();
            break;
        default:
            break;
    }
    // if (!gpio_get(PTD5)) // 判断PTD5是否是低电平
    // {
    //     uartPrintf(UARTR2, "PTD5 interrupt\n");
    // }
    //按键开关，按一下即改变对应LED灯状态
}

/*
应用于PTE0-PTH7的外部中断

*/
//KBI1中断函数

void Change_LED(){//选择小题号，哪个灯亮就哪个
    if (Button_Balance(PTF0))
    {
        LED_state[0] ^= 1;
        gpio_set(PTG0, LED_state[0]);
    }
    if (Button_Balance(PTF1))
    {
        LED_state[1] ^= 1;
        gpio_set(PTG1, LED_state[1]);
    }
    if (Button_Balance(PTF2))
    {
        LED_state[2] ^= 1;
        gpio_set(PTG2, LED_state[2]);
    }
    if (Button_Balance(PTF3))
    {
        LED_state[3] ^= 1;
        gpio_set(PTG3, LED_state[3]);
    }
}

void KBI1_Isr_5(){//指定灯亮

}


void KBI1_Isr(void)
{

    KBI1->SC |= KBI_SC_KBACK_MASK;   /* clear interrupt flag */
    KBI1->SC |= KBI_SC_RSTKBSP_MASK; //清除中断标志位
    Change_LED();
    // gpio_set(PTG0, 1); gpio_set(PTG1, 1); gpio_set(PTG2, 1); gpio_set(PTG3, 1);
    switch (SW_Opt){
        case 5:
            KBI1_Isr_5();
            break;
        default:
            break;
    }

    //由于拨码开关与按键开关不能同时触发KBI1
    // SW_Opt = 0;
    // SW_Opt |= (gpio_get(PTF4));
    // SW_Opt |= (gpio_get(PTF5)) << 1;
    // SW_Opt |= (gpio_get(PTF6)) << 2;
    // SW_Opt |= (gpio_get(PTF7)) << 3;
}
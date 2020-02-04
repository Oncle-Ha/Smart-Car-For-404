
// GPIO题目 PIT
void PIT0_ISR_GPIO(void)
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
// Uart题目 PIT
void PIT0_ISR_UART(void){
    PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
    systime += 0.01;
    sin_systime = sin(systime);
    uartPrintf(UARTR1, "%.6lf\n", sin_systime);
}
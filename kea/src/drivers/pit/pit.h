#ifndef PIT_H_
#define PIT_H_
#ifdef __cplusplus
extern "C" {
#endif

  
typedef enum
{
    PIT_CHANNEL0 = 0,       /*!< PIT channel 0 */
    PIT_CHANNEL1            /*!< PIT channel 1 */
} PITn;
void       PIT_Init(uint8_t u8Channel_No,uint16_t freq) ;                                        //��ʼ��PITn�������ö�ʱʱ��(��λΪbusʱ������)
void PIT_IRQ_EN(uint8_t u8Channel_No);
void PIT_IRQ_DIS(uint8_t u8Channel_No);
#define     pit_init_ms(PITn,ms)          PIT_Init(PITn,ms * BUS_CLK_KHZ);                      //��ʼ��PITn�������ö�ʱʱ��(��λΪ ms)
#define     pit_init_us(PITn,us)          PIT_Init(PITn,us * BUS_CLK_KHZ/100);                  //��ʼ��PITn�������ö�ʱʱ��(��λΪ 10us)
#define     PITENDINTERRUPT(PITn)         PIT->CHANNEL[PITn].TCTRL |= PIT_TCTRL_TIE_MASK        //ʹ��PIT�ж�
#define     PITDIENDINTERRUPT(PITn)       PIT->CHANNEL[PITn].TCTRL &= ~PIT_TCTRL_TIE_MASK       //��ֹPIT�ж�


#endif 
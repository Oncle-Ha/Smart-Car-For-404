#include "common.h"
#include "pit.h"

/*************************************************************************
*  �������ƣ�PIT_Init
*  ����˵������ʼ���ж϶�ʱ��
*  �������أ���
*  ����˵����u8Channel_No��PITͨ���˿ں�  ģ��ţ�PIT_CHANNEL0~PIT_CHANNEL1��
*           freq  ����ʱ��Ƶ��
*  for example     PIT_Init(PIT_CHANNEL0,100);
*************************************************************************/
void PIT_Init(uint8_t u8Channel_No,uint16_t freq)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;    
    PIT->CHANNEL[u8Channel_No].LDVAL = BUS_CLK_HZ/freq-1 ;//u32loadvalue;   //��ʼ��ʱ��                                  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TIE_MASK;  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[u8Channel_No].TFLG  |= PIT_TFLG_TIF_MASK;
  
    
}





   
/*************************************************************************
*  �������ƣ�PIT_IRQ_EN
*  ����˵����PITn��ʱ�ж�ʹ��
*  ����˵����PITn        ģ��ţ�PIT_CHANNEL0~PIT_CHANNEL1��
*  �������أ���
*  �޸�ʱ�䣺2012-3-24
*  ��    ע��
*************************************************************************/
void PIT_IRQ_EN(uint8_t u8Channel_No)
{
  
     if (u8Channel_No)
    {  
      NVIC_EnableIRQ(PIT_CH1_IRQn);      
      PITENDINTERRUPT(1);
    }
    else
    {  
      NVIC_EnableIRQ(PIT_CH0_IRQn);
      PITENDINTERRUPT(0);
    }  
}

/*************************************************************************
*  �������ƣ�PIT_IRQ_DIS
*  ����˵����PITn��ʱ�жϹر�
*  ����˵����PITn        ģ��ţ�PIT_CHANNEL0~PIT_CHANNEL1��
*  �������أ���
*  �޸�ʱ�䣺2012-3-24
*  ��    ע��
*************************************************************************/
void PIT_IRQ_DIS(uint8_t u8Channel_No)
{
     if (u8Channel_No)
    {  
      NVIC_DisableIRQ(PIT_CH1_IRQn);   
      PITDIENDINTERRUPT(1);
    }
    else
    {  
      NVIC_DisableIRQ(PIT_CH0_IRQn);
      PITDIENDINTERRUPT(0);
    }
}


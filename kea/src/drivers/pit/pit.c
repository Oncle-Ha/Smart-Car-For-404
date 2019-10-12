#include "common.h"
#include "pit.h"

/*************************************************************************
*  函数名称：PIT_Init
*  功能说明：初始化中断定时器
*  函数返回：无
*  参数说明：u8Channel_No：PIT通道端口号  模块号（PIT_CHANNEL0~PIT_CHANNEL1）
*           freq  ：定时器频率
*  for example     PIT_Init(PIT_CHANNEL0,100);
*************************************************************************/
void PIT_Init(uint8_t u8Channel_No,uint16_t freq)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;    
    PIT->CHANNEL[u8Channel_No].LDVAL = BUS_CLK_HZ/freq-1 ;//u32loadvalue;   //初始化时间                                  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TIE_MASK;  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[u8Channel_No].TFLG  |= PIT_TFLG_TIF_MASK;
  
    
}





   
/*************************************************************************
*  函数名称：PIT_IRQ_EN
*  功能说明：PITn定时中断使能
*  参数说明：PITn        模块号（PIT_CHANNEL0~PIT_CHANNEL1）
*  函数返回：无
*  修改时间：2012-3-24
*  备    注：
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
*  函数名称：PIT_IRQ_DIS
*  功能说明：PITn定时中断关闭
*  参数说明：PITn        模块号（PIT_CHANNEL0~PIT_CHANNEL1）
*  函数返回：无
*  修改时间：2012-3-24
*  备    注：
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


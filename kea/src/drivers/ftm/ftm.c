#include "ftm.h"
#include "GPIO_icf.h"
#include "GPIO.h"

/*
  通道名       默认引脚    重映射引脚
  FTM0_CH0      PTA0         PTB2
  FTM0_CH1      PTA1         PTB3
  FTM1_CH0      PTC4         PTH2           舵机1 （现在用的是C4）
  FTM1_CH1      PTC5         PTE7           舵机2   （现在用的是E7）
  FTM2_CH0      PTC0         PTH0 , PTF0    电机1
  FTM2_CH1      PTC1         PTH1 , PTF1    电机1
  FTM2_CH2      PTC2         PTD0 , PTG4    电机2
  FTM2_CH3      PTC3         PTD1 , PTG5    电机2
  FTM2_CH4      PTB4         PTG6           舵机1
  FTM2_CH5      PTB5         PTG7           舵机2
*/

FTM_Type * FTMx[3] = { FTM0,FTM1,FTM2};

/*************************************************************************
*  函数名称：FTM_PWM_init
*  功能说明：pwm初始化
*  函数返回：无
*  参数说明：ftm：   PWM模块
             ch:     通道
*            freq  ：频率
             duty  ：占空比 0-1000    可以调节FTM_PRECISON这个系数来改变精度
   for example       FTM_PWM_init(CFTM0, FTM_CH1, 10000, 10);//PWM1 PTA1       
*************************************************************************/
void FTM_PWM_init(FTMn_e ftm, FTM_CHn_e ch, uint32_t freq, uint32_t duty)
{
    uint32 clk_hz ;
    uint16 mod;
    uint8  ps;
    uint16 cv;
    uint8_t   channels;
    clk_hz = CORE_CLK_HZ ;
    
    mod = (clk_hz >> (16+4) ) / freq ;     
        ps = 0;
    while((mod >> ps) >= 1)             // 等 (mod >> ps) < 1 才退出 while 循环 ，即求 PS 的最小值
    {
        ps++;
    }
    //ASSERT(ps <= 0x07);                // 断言， PS 最大为 0x07 ，超过此值，则 PWM频率设置过低，或 Bus 频率过高
    if(ps)
    {
      mod = 0xffff ;
    }
    else
    {
      mod = (clk_hz >> (ps+4)) / freq; // 求 MOD 的值
    }
    cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;  //系数
    
    switch(ftm)
    {
    case CFTM0:
      channels = 2;
      SIM->SCGC |= SIM_SCGC_FTM0_MASK;
      SIM->PINSEL &=~SIM_PINSEL_FTM0PS0_MASK ;  // PWM0 PTA0
      SIM->PINSEL &=~SIM_PINSEL_FTM0PS1_MASK ;  // PWM1 PTA1
//      SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK ;  // PWM0 PTB2
//      SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK ;  // PWM1 PTB3
      break ;
    case CFTM1:
      channels = 2;
      SIM->SCGC |= SIM_SCGC_FTM1_MASK;
      //SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTC4 （无信号）
      //SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK ;  // PWM1 PTC5
      SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTH2
      SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK ;  // PWM1 PTE7
      
      break ;
    case CFTM2:
      channels = 6;
      SIM->SCGC  |= SIM_SCGC_FTM2_MASK;
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0); //PWM0 PTC0
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0); //PWM1 PTC1
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1); //PWM0 PTH0
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1); //PWM1 PTH1
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2); //PWM0 PTF0
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2); //PWM1 PTF1
 
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0); //PWM2 PTC2
      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0); //PWM3 PTC3
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1); //PWM2 PTD0
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1); //PWM3 PTD1
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2); //PWM2 PTG4
//      SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2); //PWM3 PTG5
      
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTB4
      SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTB5 
      //SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTG6
      //SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTG7


      break ;
    default:
        break;
    }
    FTMx[ftm]->SC = 0 ;
    FTMx[ftm]->CONTROLS[ch].CnSC = 0 ;
    ASSERT(ch <= channels);          // 断言， ch 最大为 channels ，超过此值，则无通道
    //边沿对齐，正极性PWM
    FTMx[ftm]->CONTROLS[ch].CnSC |= (0
                                  //  |FTM_CnSC_ELSA_MASK
                                    |FTM_CnSC_ELSB_MASK  
                                 //   |FTM_CnSC_MSA_MASK
                                    |FTM_CnSC_MSB_MASK
                                 //   |FTM_CnSC_CHIE_MASK
                                //    |FTM_CnSC_CHF_MASK
                                     );
    FTMx[ftm]->SC &= ~FTM_SC_CPWMS_MASK;
    //********************
    //freq = MOD - CNTIN + 0x0001
    //duty = CnV - CNTIN ;
    //********************
//    FTMx[ftm]->CNTIN = 0 ;
    FTMx[ftm]->MOD = mod ;
    FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
    FTMx[ftm]->SC = FTM_SC_CLKS(1)|FTM_SC_PS(4) ;//系统时钟，16分频  2.5M
   
}
/*************************************************************************
*  函数名称：FTM_PWM_Duty
*  功能说明：pwm赋值
*  函数返回：无
*  参数说明：FTMn_e： PWM模块
             ch    :  通道
             duty  ： 占空比 0-10000    可以调节FTM_PRECISON这个系数来改变精度
   for axample         FTM_PWM_Duty(CFTM0, FTM_CH1, 20);       
*************************************************************************/

void FTM_PWM_Duty(FTMn_e ftm, FTM_CHn_e ch, uint32_t duty)
{
    uint32_t cv;
    uint32_t mod = 0;
    uint8_t   channels;
    
    ASSERT(duty <= FTM_PRECISON); 
    switch(ftm)
    {
    case CFTM0:
      channels = 2;
      break ;
    case CFTM1:
      channels = 2;
      break ;
    case CFTM2:
      channels = 6;
      break ;
    default:
        break;
    }
     ASSERT(ch <= channels);                     // 断言， ch 最大为 channels ，超过此值，则无通道
   mod = FTMx[ftm]->MOD  ;
   cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;   //系数
   FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
}

void ftm_count_init(FTMn_e ftmn)
{
    ftm_count_mux(ftmn);                                    //引脚复用 开启上拉 开启对应外设时钟
    
    FTMx[ftmn]->SC |= FTM_SC_PS(0);	                        //分频系数	
    FTMx[ftmn]->SC |= FTM_SC_CLKS(3);                       //选择外部时钟作为FTM输入时钟
              
    FTMx[ftmn]->CNT = 0;                                    //加载初始化值
}



void ftm_count_mux(FTMn_e ftmn)
{
    
    switch(ftmn)
    {
        case CFTM0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //开启FTM外设时钟
            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //清除外部时钟引脚选择
            
            port_pull(PTE0);
            SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //选择外部时钟输入引脚 E0
            
          
        }break;
        
        case CFTM1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //开启FTM外设时钟
            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //清除外部时钟引脚选择
            
            port_pull(PTE7);
            SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //选择外部时钟输入引脚 E7
            
        }break;
        
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取计数值      用于编码器测速，无法识别方向只能计数，建议使用带方向输出的编码器
//  @param      ftmn            选择模块
//  @return     uint16          返回计数值
//  @since      v2.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
uint16 ftm_count_get(FTMn_e ftmn)
{
    return FTMx[ftmn]->CNT ;
}


void ftm_count_clean(FTMn_e ftmn)
{
    FTMx[ftmn]->CNT = 0;
}








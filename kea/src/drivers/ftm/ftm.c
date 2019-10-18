#include "ftm.h"
#include "GPIO_icf.h"
#include "GPIO.h"

/*
  ͨ����       Ĭ������    ��ӳ������
  FTM0_CH0      PTA0         PTB2
  FTM0_CH1      PTA1         PTB3
  FTM1_CH0      PTC4         PTH2           ���1 �������õ���C4��
  FTM1_CH1      PTC5         PTE7           ���2   �������õ���E7��
  FTM2_CH0      PTC0         PTH0 , PTF0    ���1
  FTM2_CH1      PTC1         PTH1 , PTF1    ���1
  FTM2_CH2      PTC2         PTD0 , PTG4    ���2
  FTM2_CH3      PTC3         PTD1 , PTG5    ���2
  FTM2_CH4      PTB4         PTG6           ���1
  FTM2_CH5      PTB5         PTG7           ���2
*/

FTM_Type * FTMx[3] = { FTM0,FTM1,FTM2};

/*************************************************************************
*  �������ƣ�FTM_PWM_init
*  ����˵����pwm��ʼ��
*  �������أ���
*  ����˵����ftm��   PWMģ��
             ch:     ͨ��
*            freq  ��Ƶ��
             duty  ��ռ�ձ� 0-1000    ���Ե���FTM_PRECISON���ϵ�����ı侫��
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
    while((mod >> ps) >= 1)             // �� (mod >> ps) < 1 ���˳� while ѭ�� ������ PS ����Сֵ
    {
        ps++;
    }
    //ASSERT(ps <= 0x07);                // ���ԣ� PS ���Ϊ 0x07 ��������ֵ���� PWMƵ�����ù��ͣ��� Bus Ƶ�ʹ���
    if(ps)
    {
      mod = 0xffff ;
    }
    else
    {
      mod = (clk_hz >> (ps+4)) / freq; // �� MOD ��ֵ
    }
    cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;  //ϵ��
    
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
      //SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTC4 �����źţ�
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
    ASSERT(ch <= channels);          // ���ԣ� ch ���Ϊ channels ��������ֵ������ͨ��
    //���ض��룬������PWM
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
    FTMx[ftm]->SC = FTM_SC_CLKS(1)|FTM_SC_PS(4) ;//ϵͳʱ�ӣ�16��Ƶ  2.5M
   
}
/*************************************************************************
*  �������ƣ�FTM_PWM_Duty
*  ����˵����pwm��ֵ
*  �������أ���
*  ����˵����FTMn_e�� PWMģ��
             ch    :  ͨ��
             duty  �� ռ�ձ� 0-10000    ���Ե���FTM_PRECISON���ϵ�����ı侫��
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
     ASSERT(ch <= channels);                     // ���ԣ� ch ���Ϊ channels ��������ֵ������ͨ��
   mod = FTMx[ftm]->MOD  ;
   cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;   //ϵ��
   FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
}

void ftm_count_init(FTMn_e ftmn)
{
    ftm_count_mux(ftmn);                                    //���Ÿ��� �������� ������Ӧ����ʱ��
    
    FTMx[ftmn]->SC |= FTM_SC_PS(0);	                        //��Ƶϵ��	
    FTMx[ftmn]->SC |= FTM_SC_CLKS(3);                       //ѡ���ⲿʱ����ΪFTM����ʱ��
              
    FTMx[ftmn]->CNT = 0;                                    //���س�ʼ��ֵ
}



void ftm_count_mux(FTMn_e ftmn)
{
    
    switch(ftmn)
    {
        case CFTM0:
        {
            SIM->SCGC |= SIM_SCGC_FTM0_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;      //����ⲿʱ������ѡ��
            
            port_pull(PTE0);
            SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);     //ѡ���ⲿʱ���������� E0
            
          
        }break;
        
        case CFTM1:
        {
            SIM->SCGC |= SIM_SCGC_FTM1_MASK;                //����FTM����ʱ��
            SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;      //����ⲿʱ������ѡ��
            
            port_pull(PTE7);
            SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);     //ѡ���ⲿʱ���������� E7
            
        }break;
        
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ֵ      ���ڱ��������٣��޷�ʶ����ֻ�ܼ���������ʹ�ô���������ı�����
//  @param      ftmn            ѡ��ģ��
//  @return     uint16          ���ؼ���ֵ
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








#include "common.h"
#include "adc.h"


/*************************************************************************
*  �������ƣ�ADC_Init
*  ����˵����AD��ʼ��
*  �������أ���
*  ����˵����ch  :�ɼ�ͨ��
*           bit ���ɼ�λ��
*  for example  : ADC_Init(ADC_CHANNEL_AD4,ADC_12BIT);
*************************************************************************/
void ADC_Init( ADCHn  ch,ADC_nbit bit)
{
        SIM->SCGC |= SIM_SCGC_ADC_MASK;   //����ʱ��ԭ
        
        ADC->SC3  = (0
                      |ADC_SC3_ADICLK(BUS_CLOCK_DIVIDE_2)   //ѡ��ϵͳʱ��
                      |ADC_SC3_MODE(bit)      //bitλAD�ɼ�
                      //|ADC_SC3_ADLSMP_MASK         //������ʱ��
                      |ADC_SC3_ADIV(ADC_ADIV_1)      //��ƵΪ1
                      //|ADC_SC3_ADLPC_MASK          //�͹��Ĳɼ�  
                    ) ;
        ADC->SC2  = (0
                     // |ADC_SC2_ADTRG_MASK             //1Ӳ������,0�������
                    //  |ADC_SC2_ACFE_MASK            //�ɼ��Ƚ�
                    //  |ADC_SC2_ACFGT_MASK           //���ڱȽ�ֵ���Ƚϴ���
                     |  ADC_SC2_REFSEL(0)     //ʹ���ⲿ�ο���ѹ VREFH/VREFL
                    ) ;
       ADC->APCTL1 = ADC_APCTL1_ADPC(1<< ch) ;
}

/*************************************************************************
*  �������ƣ�adc_init
*  ����˵������ȡADC����ֵ(��֧��Bͨ��)
*  ����˵����adcn_ch      ADCͨ��
*  for example           adc_once(ADC_CHANNEL_AD4);
*************************************************************************/
uint16_t adc_once(ADCHn adcn_ch) //�ɼ�ĳ·ģ������ADֵ
{
  uint16_t result = 0;
  ADC->SC1= (0                         //����ADCת��
           //| ADC_SC1_AIEN_MASK        // ת������ж�,0Ϊ��ֹ��1Ϊʹ��
           //| ADC_SC1_DIFF_MASK        // ���ģʽʹ��,0Ϊ���ˣ�1Ϊ���
           | ADC_SC1_ADCH( adcn_ch )
           );    
  while ((ADC->SC1 & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);   //�ȴ�ת�����
  result = ADC->R;
  return result;
}
/*************************************************************************
*  �������ƣ�ad_ave
*  ����˵������β�����ȡƽ��ֵ
*  ����˵���� adcn_ch ͨ����
*            N       ��ֵ�˲�����(��Χ:0~255)
*  for example       adc_once(ADC_CHANNEL_AD4,10);
*************************************************************************/
uint16_t adc_ave(ADCHn adcn_ch, uint8_t N) //��ֵ�˲�
{
    uint32_t tmp = 0;
    uint8_t  i;
    for(i = 0; i < N; i++)
        tmp += adc_once(adcn_ch);
    tmp = tmp / N;
    return (uint16_t)tmp;
}

/*************************************************************************
*  �������ƣ�adc_sum
*  ����˵������β��������
*  ����˵����adcn_ch      ͨ����
*            N           ��ʹ���(��Χ:0~255)
*  for example           adc_sum(ADC_CHANNEL_AD4,10);
*************************************************************************/
uint16_t adc_sum(ADCHn adcn_ch, uint8_t N)
{
    uint32_t tmp = 0;
    uint8_t  i;
    for(i = 0; i < N; i++)
        tmp += adc_once(adcn_ch);
    return (uint16_t)tmp;
}














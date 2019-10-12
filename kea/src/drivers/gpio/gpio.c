#include "gpio.h"   //����������ͷ�ļ�
#include "common.h"
volatile struct GPIO_Type *GPIOx[3]={GPIOA,GPIOB,GPIOC};

/*************************************************************************
*  �������ƣ�gpio_init
*  ����˵������ʼ��IO
*  �������أ���
*  ����˵����port���˿ں�
*           dir��  ���ŷ���0=���룬1=�����
*           state�����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
*  for axample     gpio_init(PTG0,1,0);
*************************************************************************/
void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state)
{	 
  //����dir����������Ϊ�����������
  if (1 == dir)   //���
  {
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) |= (1 << PTn(ptxn));  //���ö˿ڷ���Ϊ���
    gpio_set(ptxn , state);   //����gpio_set�������趨�������״̬
  }
  else 
  {
    //����
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //���ö˿ڷ���Ϊ����
    GPIO_PIDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //���ö˿ڷ���Ϊ����
  }

}

/*************************************************************************
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  �������أ���
*  ����˵����ptxn�� �˿ں�
*            state�������ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ
*  for example      gpio_set(PTG0, 1);
*************************************************************************/
void gpio_set(PTxn ptxn, uint8_t state)
{        
  if(state)
  {
     GPIO_SET(PTX(ptxn), PTn(ptxn), 1);
  }
  else 
  {
    GPIO_SET(PTX(ptxn), PTn(ptxn), 0);
  }
}
/*************************************************************************
*  �������ƣ�gpio_get
*  ����˵����������ŵ�״̬
*  �������أ���
*  ����˵����ptxn���˿ں�
*  for example     gpio_get(PTG0);
*************************************************************************/
uint8_t gpio_get(PTxn ptxn)
{	
  return GPIO_Get(PTX(ptxn),PTn(ptxn)) ;
}

/*************************************************************************
*  �������ƣ�gpio_turn
*  �������أ���
*  ����˵����      ��ת��ƽ
*  ����˵����ptxn���˿ں�
*  for example     gpio_turn(PTG0);
*************************************************************************/
void gpio_turn(PTxn ptxn)
{
  GPIO_TURN(PTX(ptxn), PTn(ptxn));
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      IO����
//  @param      ptx_n           ѡ��˿�
//  @return     void
//  @since      v2.0
//  Sample usage:               port_pull(E0);			//E0 �������迪��
//-------------------------------------------------------------------------------------------------------------------
void port_pull(PTxn ptx_n)
{
    uint8 ptx,ptn;
    ptx = PTX(ptx_n);//��¼ģ���    //A,B......
    ptn = PTn(ptx_n);//��¼���ź�    //0,1,2,3......
    
    switch(ptx)
    {
        case 0:
        {
            PORT->PUE0 |= (uint32)(1<<ptn);
        }break;
        
        case 1:
        {
            PORT->PUE1 |= (uint32)(1<<ptn);
        }break;
        
        case 2:
        {
            PORT->PUE2 |= (uint32)(1<<ptn);
        }break;
    }
}



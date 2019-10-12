#ifndef _KBI_H_
#define _KBI_H_
#ifdef __cplusplus
extern "C" {
#endif

extern volatile KBI_Type * KBIx[2] ;
/*!
* @brief KBI MODE select enum.
*
*/
typedef enum
{
    KBI_MODE_EDGE_ONLY = 0,             /*!< select  edge only mode  */         
    KBI_MODE_EDGE_LEVEL                 /*!< select  both edge and level  mode */
}KBI_ModeType;

typedef enum
{
    KBIX0 = 0,             /*!< select  edge only mode  */         
    KBIX1                 /*!< select  both edge and level  mode */
}KBIn_e;



 /*!
 * @brief KBI Edge select enum.
 *
 */
typedef enum
{
    KBI_FALLING_LOW  = 0,     /*!< select falling edge and/or low level  */
    KBI_RISING__HIGH         /*!< select rising edge and/or high level  */
}KBI_Edge;


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Global functions
******************************************************************************/
void KBI_Init(KBIn_e kbix,uint8_t kbich,KBI_Edge RiFal) ;
void KBI_Disable(KBIn_e kbix,uint8_t kbich) ;
void KBI_Enable(KBIn_e kbix,uint8_t kbich) ;

#endif 

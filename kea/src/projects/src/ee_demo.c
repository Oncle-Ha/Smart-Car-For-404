
#include "ee_emulation.h"
#include "ee_callback.h"
#include "ee_demo.h"


/* buffer to store data for read eeprom emulation */
uint8_t dataBuf[EE_DATA_VALUE_SIZE];
/* source buffer to write data */
uint8_t sourceBuf[EE_DATA_VALUE_SIZE];
/* seed used to initialize souce data to make different time to time*/
uint16_t seed[EE_MAX_RECORD_NUMBER];

/* array __ram_func_callback used to copy callback funtion to ram */
uint16_t __ram_func_callback[CALLBACK_SIZE >> 1U];

/*******************************************************************************
*
*  Function Name    : FillBuf
*  Description      : To fill buffer with expected data. This function is to generate 
*                    different data for different record ID and different order.
*  Arguments        : 
*                    - buf: buffer to store data;
*                    - start_val: start value of buffer.
*                    - order: the order to be present for this data.
*  Return Value     : n/a
*
*******************************************************************************/
void FillBuf(uint32_t buf, uint32_t start_val, uint16_t seed)
{
    uint32_t i;
    uint8_t* pBuf = (uint8_t*)(buf);
    
    for (i = 0; i < EE_DATA_VALUE_SIZE; i++)
    {
        pBuf[i] = start_val + i + seed;
    }
}

int main()
{
    EEPROM_CONFIG eepromConfig;  
    uint32_t i;
    uint32_t rec_addr;
    uint32_t old_val;
    uint16_t data_id;
    uint8_t demo_result = DEMO_PASS;
    uint8_t ret_val;
    
    /* relocate flash command sequence if neccessary*/
#if (COPY_TO_RAM)
    Eed_CopyLaunchCmdToRam();
    #if EE_CALLBACK_ENABLE
    g_EECallBack = (PEE_CALLBACK)Eed_RelocFunction((uint32_t)__ram_func_callback,CALLBACK_SIZE,
            (uint32_t)EECallBack);
    #endif
#else
    #if EE_CALLBACK_ENABLE
    g_EECallBack = EECallBack;
    #endif 
#endif
    

    /*Initialize flash clock*/
    Eed_InitFlashClock();
    
    /* Intialize start address for Eeprom configuration*/
    /* this is user configurable and it will depend on which sector was selected for emulation*/
    /* user needs to keep the same intialization for different calls and always initialize it
    before calling Eed_InitEeprom()*/
    for (i = 0; i < EE_ALLOTED_SECTORS; i++)
    {
        eepromConfig.startSecAddr[i] = EE_START_ADDRESS + i*EE_SECTOR_SIZE;
    }
    
    /* Need to clean up flash before using Eeprom emulation */
    /* This function need to be called just once at the first 
    time in entire EEPROM emulation life cylce to clean up entire EEPROM before using*/
    /* so, user needs to design his application code to not call this function later on*/
    ret_val = Eed_DeinitEeprom(&eepromConfig);
    if (ret_val != EE_OK)
    {
        demo_result |= DEMO_FAIL;
    }
    /*initialize all buffer*/
    for (i = 0x0U; i < EE_MAX_RECORD_NUMBER; i++)
    {
        seed[i] = 0x0U;
    }

    /* Initialize Eeprom emulation */
    ret_val = Eed_InitEeprom(&eepromConfig);
    if (ret_val != EE_OK)
    {
        demo_result |= DEMO_FAIL;
    }
    /*Write some records */
    for (data_id = 0x0; data_id < EE_MAX_RECORD_NUMBER/2; data_id ++)
    {
        seed[data_id] ++;
        FillBuf((uint32_t) sourceBuf, data_id, seed[data_id]);
        ret_val = Eed_WriteEeprom(&eepromConfig, data_id, (uint32_t)sourceBuf);
        if (ret_val != EE_OK)
        {
            demo_result |= DEMO_FAIL;
        }
    }
    /* write until swapping for serveral times */
    data_id = 0x0;
    while(eepromConfig.eraseCycValue <= SWAPPING_NUMBER)
    {
        /* prepare buffer to write*/
        seed[data_id] ++;
        FillBuf((uint32_t)sourceBuf, data_id, seed[data_id]);
        /* write data to Eeprom */
        ret_val = Eed_WriteEeprom(&eepromConfig, data_id, (uint32_t)sourceBuf);
        if (ret_val != EE_OK)
        {
            demo_result |= DEMO_FAIL;
        }
        data_id ++;
        if (data_id >= EE_MAX_RECORD_NUMBER)
        {
            data_id = 0x0;
        }
    }
    /* read Eeprom data */
    for (data_id = 0x0; data_id < EE_MAX_RECORD_NUMBER; data_id ++)
    {
        /* re-prepare source buffer */
        FillBuf((uint32_t)sourceBuf, data_id, seed[data_id]);
        ret_val = Eed_ReadEeprom(&eepromConfig, data_id, &rec_addr);
        if (ret_val != EE_OK)
        {
            demo_result |= DEMO_FAIL;
        }
        /* at this time, make sure all valid record ID are written to Eeprom emulation. So, expected returnCode is EE_OK*/
        
        /* verify the data */
        for (i = 0; i < EE_DATA_VALUE_SIZE; i ++)
        {
            EEDisableCache(&old_val);
            if (READ8((uint32_t)sourceBuf + i) != READ8(rec_addr + i))
            {
                demo_result |= DEMO_FAIL;
                break;
            }
            EERestoreCache(old_val);
        }
        if (demo_result != DEMO_PASS)
        {
            data_id ++; 
            break;
                        
        }
        
    }
    /* if don't want to use Eeprom any more, just remove it */
    ret_val = Eed_DeinitEeprom(&eepromConfig);
    if (ret_val != EE_OK)
    {
        demo_result |= DEMO_FAIL;
    }

    return (demo_result);
}


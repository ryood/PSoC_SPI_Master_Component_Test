/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

// ERROR CODE
#define ERR_DAC_CHANNEL_OUT_OF_RANGE 0x01

void DACSetVoltage(uint16 value)
{
    uint8 txDataH, txDataL;
    
    // Highバイト(0x30=OUTA/BUFなし/1x/シャットダウンなし)
    txDataH = 0x30 | (value >> 8);
    txDataL = (value & 0x00ff); 
    
    Pin_LDAC_Write(1u);
    SPIM_1_WriteTxData(txDataH);
    SPIM_1_WriteTxData(txDataL);
    
    CyDelayUs(10);
        
    Pin_LDAC_Write(0u);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    SPIM_1_Start();
    
    for(;;)
    {
        DACSetVoltage(512);
        CyDelay(1);
    }
}

/* [] END OF FILE */

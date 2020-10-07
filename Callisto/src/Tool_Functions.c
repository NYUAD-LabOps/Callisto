#include <Callisto.h>

void toolHandler(struct toolBlock *toolBlock)
{
    int i;
    int debtmp = 0;
    adc_data_size_t adc_data;
    double voltage;
    double tmpTemp, temp;

    ioport_level_t level;
    ssp_err_t err;

    temp = 0;
//    for (i = 0; i < 10; i++)
//    {
//        g_adc1.p_api->read (g_adc1.p_ctrl, ADC_REG_CHANNEL_2, &adc_data);
//        voltage = 3.3;
//        voltage = voltage / 4095.0;
//        voltage *= adc_data;
//        tmpTemp = (voltage - 1.25) / .005;
//        temp += tmpTemp;
//        //            printf ("\nADC102: %f", voltage);
//        tx_thread_sleep (10);
//    }

    g_adc1.p_api->read (g_adc1.p_ctrl, ADC_REG_CHANNEL_2, &adc_data);
    voltage = 3.3;
    voltage = voltage / 4095.0;
    voltage *= adc_data;
    tmpTemp = (voltage - 1.25) / .005;
    toolBlock->tempRead = tmpTemp;
//    temp += tmpTemp;

//    toolBlock->tempRead = temp / 10.0;
    if (debtmp)
    {
        if (DEBUGGER)
            printf ("\nTemperature Set: %f", toolBlock->tempSet);
        if (DEBUGGER)
            printf ("\nTemperature Read: %f", toolBlock->tempRead);
    }

    if (toolBlock->tempRead < toolBlock->tempSet)
    {
        err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_05, IOPORT_LEVEL_HIGH); //heater

        //    err = g_ioport.p_api->pinWrite (IOPORT_PORT_03_PIN_14, IOPORT_LEVEL_LOW);
        err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_06, IOPORT_LEVEL_HIGH); //fan
        if (debtmp)
        {
            if (DEBUGGER)
                printf ("\nHeating...");
        }
    }
    else if (toolBlock->tempRead > toolBlock->tempSet)
    {
        err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_05, IOPORT_LEVEL_LOW); //heater

        //    err = g_ioport.p_api->pinWrite (IOPORT_PORT_03_PIN_14, IOPORT_LEVEL_LOW);
        err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_06, IOPORT_LEVEL_HIGH); //fan
        if (debtmp)
        {
            if (DEBUGGER)
                printf ("\nCooling...");
        }
    }

}


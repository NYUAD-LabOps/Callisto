#include <Callisto.h>
#include "ToolA.h"

/* ToolA entry function */
void ToolA_entry(void)
{
//    ssp_err_t err;
//    UINT status;
//    ///ADC setup goes here
//    /// Initialize ADC Driver
//    status = g_adc1.p_api->open (g_adc1.p_ctrl, g_adc1.p_cfg);
//    if (status == SSP_SUCCESS)
//    {
//        if (DEBUGGER)
//            printf ("\nADC1 open success.");
//    }
//
//    //Configure ADC Channel
//    status = g_adc1.p_api->scanCfg (g_adc1.p_ctrl, g_adc1.p_channel_cfg);
//    if (status == SSP_SUCCESS)
//    {
//        if (DEBUGGER)
//            printf ("\nADC1 scanCfg success.");
//    }
//
//    //Start the ADC scan
//    status = g_adc1.p_api->scanStart (g_adc1.p_ctrl);
//    if (status == SSP_SUCCESS)
//    {
//        if (DEBUGGER)
//            printf ("\nADC1 scan start success.");
//    }
//
//    g_timer1.p_api->start (g_timer1.p_ctrl);
//
//    err = g_timer1.p_api->periodSet (g_timer1.p_ctrl, 1, TIMER_UNIT_PERIOD_SEC);

    while (1)
    {
        motorHandler (toolBlockA->motorBlock);
        tx_thread_relinquish ();
    }
}

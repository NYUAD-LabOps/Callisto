#include <Callisto.h>
#include "MotorC.h"

/* MotorC entry function */
void MotorC_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockC);
        //        tx_thread_sleep (1);
                tx_thread_suspend (tx_thread_identify ());
    }
}

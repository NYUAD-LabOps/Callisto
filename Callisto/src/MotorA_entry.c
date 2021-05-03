#include <Callisto.h>
#include "MotorA.h"

/* MotorA entry function */
void MotorA_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockA);
//        tx_thread_sleep (1);
        tx_thread_suspend (tx_thread_identify ());
    }
}

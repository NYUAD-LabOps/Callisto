#include <Callisto.h>
#include "MotorB.h"

/* MotorB entry function */
void MotorB_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockB);
        tx_thread_sleep (1);
    }
}

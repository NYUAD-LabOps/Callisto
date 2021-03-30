#include <Callisto.h>
#include "MotorD.h"

/* MotorD entry function */
void MotorD_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockD);
        tx_thread_sleep (1);
    }
}

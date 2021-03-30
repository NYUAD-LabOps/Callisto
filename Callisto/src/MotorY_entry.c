#include <Callisto.h>
#include "MotorY.h"

/* MotorY entry function */
void MotorY_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockY);
        tx_thread_sleep (1);
    }
}

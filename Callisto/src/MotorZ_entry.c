#include <Callisto.h>
#include "MotorZ.h"

/* MotorZ entry function */
void MotorZ_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        motorHandler (motorBlockZ);
        tx_thread_relinquish ();
    }
}

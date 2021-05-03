#include <Callisto.h>
#include "MotorX.h"

/* MotorX entry function */
void MotorX_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        //run motor handler for motor 2
        motorHandler(motorBlockX);
        //allow next waiting thread(s) to run
        tx_thread_relinquish ();
    }
}

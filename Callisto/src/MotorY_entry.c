#include "MotorY.h"
#include "Helix.h"

/* MotorY entry function */
void MotorY_entry(void)
{
    /* TODO: add your own code here */
    //Motor Init Sequence
    //wait for motor block allocation
    while(motorBlockY->init != 1) tx_thread_sleep (1);

    while (1)
    {
        //run motor handler for motor 2
        motorHandler(motorBlockY);

        //allow next waiting thread(s) to run
        tx_thread_sleep (1);
    }
}

#include <Callisto.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CallistoMain.h"
#include "math.h"
//#include "hal_data.h"
//#include <GPT_HAL_MG.h>

struct node *head = NULL;
struct node *tail = NULL;
struct node *current = NULL;
struct node *currentPrint = NULL;
TX_BLOCK_POOL my_pool;
TX_BLOCK_POOL my_pool2;
TX_BLOCK_POOL my_pool3;
TX_BLOCK_POOL my_pool4;
TX_BYTE_POOL USB_Byte_Pool;
TX_BYTE_POOL USB_Byte_PoolB;

void initMotors()
{
    ssp_err_t err;
    motorInitX ();

    motorBlockY->dirPin = IOPORT_PORT_04_PIN_11;
    motorBlockY->stepPin = IOPORT_PORT_04_PIN_15;
    motorBlockY->limit0Pin = IOPORT_PORT_04_PIN_08;
    motorBlockY->start = g_timer_gpt_7.p_api->start;
    motorBlockY->stop = g_timer_gpt_7.p_api->stop;
    motorBlockY->dutyCycleSet = g_timer_gpt_7.p_api->dutyCycleSet;
    motorBlockY->periodSet = g_timer_gpt_7.p_api->periodSet;
    motorBlockY->g_timer_gpt_x = g_timer_gpt_7;
    err = g_external_irqY.p_api->open (g_external_irqY.p_ctrl, g_external_irqY.p_cfg);
    genericMotorInit (motorBlockY);

    motorBlockA->dirPin = IOPORT_PORT_08_PIN_04;
    motorBlockA->stepPin = IOPORT_PORT_08_PIN_03;
    motorBlockA->limit0Pin = IOPORT_PORT_04_PIN_08;
    motorBlockA->start = g_timerA.p_api->start;
    motorBlockA->stop = g_timerA.p_api->stop;
    motorBlockA->dutyCycleSet = g_timerA.p_api->dutyCycleSet;
    motorBlockA->periodSet = g_timerA.p_api->periodSet;
    motorBlockA->g_timer_gpt_x = g_timerA;
    genericMotorInit (motorBlockA);

    motorBlockZ->dirPin = IOPORT_PORT_04_PIN_10;
    motorBlockZ->stepPin = IOPORT_PORT_04_PIN_14;
    motorBlockZ->limit0Pin = IOPORT_PORT_02_PIN_03;
    motorBlockZ->start = g_timer_gpt_3.p_api->start;
    motorBlockZ->stop = g_timer_gpt_3.p_api->stop;
    motorBlockZ->dutyCycleSet = g_timer_gpt_3.p_api->dutyCycleSet;
    motorBlockZ->periodSet = g_timer_gpt_3.p_api->periodSet;
    motorBlockZ->g_timer_gpt_x = g_timer_gpt_3;
    err = g_external_irqZ.p_api->open (g_external_irqZ.p_ctrl, g_external_irqZ.p_cfg);
    genericMotorInit (motorBlockZ);

    motorBlockB->dirPin = IOPORT_PORT_03_PIN_04;
    motorBlockB->stepPin = IOPORT_PORT_03_PIN_03;
    motorBlockB->limit0Pin = IOPORT_PORT_02_PIN_03;
    motorBlockB->start = g_timerB.p_api->start;
    motorBlockB->stop = g_timerB.p_api->stop;
    motorBlockB->dutyCycleSet = g_timerB.p_api->dutyCycleSet;
    motorBlockB->periodSet = g_timerB.p_api->periodSet;
    motorBlockB->g_timer_gpt_x = g_timerB;
    genericMotorInit (motorBlockB);

    motorBlockC->dirPin = IOPORT_PORT_03_PIN_06;
    motorBlockC->stepPin = IOPORT_PORT_03_PIN_05;
    motorBlockC->limit0Pin = IOPORT_PORT_02_PIN_03;
    motorBlockC->start = g_timerC.p_api->start;
    motorBlockC->stop = g_timerC.p_api->stop;
    motorBlockC->dutyCycleSet = g_timerC.p_api->dutyCycleSet;
    motorBlockC->periodSet = g_timerC.p_api->periodSet;
    motorBlockC->g_timer_gpt_x = g_timerC;
    genericMotorInit (motorBlockC);

    motorBlockD->dirPin = IOPORT_PORT_03_PIN_09;
    motorBlockD->stepPin = IOPORT_PORT_03_PIN_07;
    motorBlockD->limit0Pin = IOPORT_PORT_02_PIN_03;
    motorBlockD->start = g_timerD.p_api->start;
    motorBlockD->stop = g_timerD.p_api->stop;
    motorBlockD->dutyCycleSet = g_timerD.p_api->dutyCycleSet;
    motorBlockD->periodSet = g_timerD.p_api->periodSet;
    motorBlockD->g_timer_gpt_x = g_timerD;
    genericMotorInit (motorBlockD);

    motorBlockT->dirPin = IOPORT_PORT_04_PIN_09;
    motorBlockT->stepPin = IOPORT_PORT_04_PIN_13;
    motorBlockT->start = g_timerT.p_api->start;
    motorBlockT->stop = g_timerT.p_api->stop;
    motorBlockT->dutyCycleSet = g_timerT.p_api->dutyCycleSet;
    motorBlockT->periodSet = g_timerT.p_api->periodSet;
    motorBlockT->g_timer_gpt_x = g_timerT;
    genericMotorInit (motorBlockT);

    machineGlobalsBlock->motorsInit = 1;
}

void initTools()
{
    toolInitA ();
}

///Motor Block initialization process.
void initMotorBlocks()
{
    UINT status;
    unsigned char *memory_ptr;

    status = tx_block_pool_create(&my_pool2, "mtrblocks", sizeof(struct motorController), (VOID *) 0x20040000, 10000);

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockX = (struct motorController *) memory_ptr;

    motorBlockX->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockY = (struct motorController *) memory_ptr;

    motorBlockY->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockA = (struct motorController *) memory_ptr;
    motorBlockA->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockZ = (struct motorController *) memory_ptr;

    motorBlockZ->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockB = (struct motorController *) memory_ptr;
    motorBlockB->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockC = (struct motorController *) memory_ptr;

    motorBlockC->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockD = (struct motorController *) memory_ptr;

    motorBlockD->init = 1;

    status = tx_block_allocate (&my_pool2, (VOID **) &memory_ptr, TX_NO_WAIT);
    motorBlockT = (struct motorController *) memory_ptr;
    motorBlockT->init = 1;
}

///Tool block initialization process.
void initToolBlocks()
{
    UINT status;
    unsigned char *memory_ptr;

    status = tx_block_pool_create(&my_pool4, "toolblocks", sizeof(struct toolBlock), (VOID *) 0x20045000, 1000);

    status = tx_block_allocate (&my_pool4, (VOID **) &memory_ptr, TX_NO_WAIT);
    toolBlockA = (struct toolBlock *) memory_ptr;
}

void initGlobalsBlock()
{
    //init memory pool and block for retaining machine status information
    UINT status;
    ssp_err_t err;
    unsigned char *memory_ptr;

    status = tx_block_pool_create(&my_pool3, "status", sizeof(struct machineGlobals), (VOID *) 0x20050000, 1000);

    status = tx_block_allocate (&my_pool3, (VOID **) &memory_ptr, TX_NO_WAIT);
    machineGlobalsBlock = (struct machineGlobals *) memory_ptr;
    machineGlobalsBlock->receivingMsg = 0;
    machineGlobalsBlock->calibRunning = 0;
    machineGlobalsBlock->targetSpeed = DEFAULTSPEED;
    ///Default to relative positioning.
    machineGlobalsBlock->relativePositioningEN = 0;
    machineGlobalsBlock->motorsInit = 0;

    machineGlobalsBlock->idlePin = IOPORT_PORT_06_PIN_00;

    machineGlobalsBlock->ethIP = 0;
    machineGlobalsBlock->reportIP = 0;
    machineGlobalsBlock->UDPRXReady = 0;
    memset (machineGlobalsBlock->UDPBuffer, 0, 15);

    machineGlobalsBlock->relay0 = IOPORT_PORT_09_PIN_01;
    machineGlobalsBlock->relay1 = IOPORT_PORT_09_PIN_00;
    machineGlobalsBlock->relay2 = IOPORT_PORT_03_PIN_15;
    machineGlobalsBlock->relay3 = IOPORT_PORT_03_PIN_14;

    ///Relay init
    err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_03, IOPORT_LEVEL_HIGH);
    err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_03, IOPORT_LEVEL_HIGH);
    err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_03, IOPORT_LEVEL_HIGH);
    err = g_ioport.p_api->pinWrite (IOPORT_PORT_02_PIN_03, IOPORT_LEVEL_HIGH);

    err = g_ioport.p_api->pinWrite (IOPORT_PORT_06_PIN_00, IOPORT_LEVEL_LOW);
    machineGlobalsBlock->globalsInit = 1;

}

///This function is responsible for monitoring motor activity during a
/// calibration routine.
void calRoutine(struct motorController *motorBlock)
{
    long int tmpTargetPosSteps;
    tmpTargetPosSteps = motorBlock->posSteps;

    ///Reset the motor position to zero
    motorBlock->posSteps = 0;
    motorBlock->pos = 0;

    motorBlock->freqSet = 1;

    ///At this point the motor should begin moving.
    ///Now, we must monitor the position of the axis and stop its movement
    /// as soon as it gets within range of the target position.
    if (motorBlock->targetDir == motorBlock->fwdDir)
    {
        while (motorBlock->posSteps < motorBlock->targetPosSteps)
        {
            tx_thread_sleep (1);
        }
    }
    else
    {
        while (motorBlock->posSteps > motorBlock->targetPosSteps)
        {
            tx_thread_sleep (1);
        }
    }
    ///Axis has reached target position. Stop it immediately.
    stopMotor (motorBlock);

}

/**Can be used to return the percent error between a target and current float.
 Useful when determing the percent error of positioning.*/
double percentError(double target, double actual)
{
    double diff = fabs (actual - target);
    double error = fabs (diff / target);
    error *= 100.0;
    return error;
}

char isInRange(char in)
{
    if ((in > 44 && in < 58) || (in > 64 && in < 91) || (in > 96 && in < 123))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

///This function will check if a motor is set for the correct target direction.
/// The "fwd" argument indicates if the direction should be forward, or reverse, given a
/// positive or negative input.
void checkSetMotorDir(struct motorController *motorBlock, double fwd)
{
    if (fwd > 0 && motorBlock->targetDir != motorBlock->fwdDir)
    {
        motorBlock->targetDir = motorBlock->fwdDir;
    }
    else if (fwd < 0)
    {
        if (motorBlock->targetDir == motorBlock->fwdDir && motorBlock->fwdDir == IOPORT_LEVEL_HIGH)
        {
            motorBlock->targetDir = IOPORT_LEVEL_LOW;
        }
        else if (motorBlock->targetDir == motorBlock->fwdDir && motorBlock->fwdDir == IOPORT_LEVEL_LOW)
        {
            motorBlock->targetDir = IOPORT_LEVEL_HIGH;
        }
    }
}

void reportIP()
{
    machineGlobalsBlock->UDPTxBuff[0] = 'a';
    machineGlobalsBlock->UDPTxBuff[1] = 'b';

    UDPSend ();
}

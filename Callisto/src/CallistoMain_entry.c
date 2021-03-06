#include <Callisto.h>
#include "CallistoMain.h"
#include <GPT_HAL_MG.h>

/* Helix Main entry function */
void CallistoMain_entry(void)
{
    double lastX, lastY, lastZ, lastT, lastSpeed;
    int endReached = 0;
    int endX, endY, endZ;
    double lineVector[3], newLineVector[3];
    double lineVectorMag, newLineVectorMag;
    double newUnitVector[3];
    double targetVelocityVector[3], targetVelocityVectorMag;
    double startPos[3], newPos[3], targetPos[3];
    //    double targetSpeed;
    double tmpData, tmpTargetSpeed;
    double extruderSpeed;
    double time;
    double tmpPercentError;
    if (DEBUGGER)
        initialise_monitor_handles ();
    /* TODO: add your own code here */
    ssp_err_t err = init_timers ();

    if (DEBUGGER)
    {
        printf ("\nHelix slave initializing...");
    }
    initGlobalsBlock ();

    initMotorBlocks ();
    initToolBlocks ();
    initMotors ();
    initTools ();

    while (machineGlobalsBlock->motorsInit != 1 || machineGlobalsBlock->globalsInit != 1)
        tx_thread_sleep (1);

    while (1)
    {

        if (machineGlobalsBlock->newTarget)
        {
            machineGlobalsBlock->newTarget = 0;
            tmpTargetSpeed = (2 * machineGlobalsBlock->targetSpeed); ///Temporarily doubling the speed.

            if (machineGlobalsBlock->targetPosX != ~0)
            {
                targetPos[0] = machineGlobalsBlock->targetPosX;
            }
            else
            {
                targetPos[0] = motorBlockX->pos;
            }

            if (machineGlobalsBlock->targetPosY != ~0)
            {
                targetPos[1] = machineGlobalsBlock->targetPosY;
            }
            else
            {
                targetPos[1] = motorBlockY->pos;
            }

            if (machineGlobalsBlock->targetPosZ != ~0)
            {
                targetPos[2] = machineGlobalsBlock->targetPosZ;
            }
            else
            {
                targetPos[2] = motorBlockZ->pos;
            }

            ///We now have the target position and can calculate the line vector.
            lineVector[0] = (targetPos[0] - motorBlockX->pos);
            lineVector[1] = (targetPos[1] - motorBlockY->pos);
            lineVector[2] = (targetPos[2] - motorBlockZ->pos);

            ///Calculate magnitude.
            lineVectorMag = sqrt (pow (lineVector[0], 2) + pow (lineVector[1], 2) + pow (lineVector[2], 2));

            ///Calculate the latest unit vector.
            if (lineVectorMag != 0)
            {
                newUnitVector[0] = (lineVector[0] / lineVectorMag);
                newUnitVector[1] = (lineVector[1] / lineVectorMag);
                newUnitVector[2] = (lineVector[2] / lineVectorMag);
            }
            else
            {
                newUnitVector[0] = 0;
                newUnitVector[1] = 0;
                newUnitVector[2] = 0;
            }

            ///The unit vector will provide the appropriate direction of each motor. Multiplying
            /// the unit vector by the target speed will provide the target velocity vector.
            ///Calculate the velocity vector.
            targetVelocityVector[0] = (tmpTargetSpeed * newUnitVector[0]);
            targetVelocityVector[1] = (tmpTargetSpeed * newUnitVector[1]);
            targetVelocityVector[2] = (tmpTargetSpeed * newUnitVector[2]);

            if (fabs (targetVelocityVector[2]) > 110.0)
            {
                ///The z-axis movement speed is too high. Calculate the reduction factor and recalculate
                /// the velocity vector based on this.
                double reductionFactor = fabs ((110.0 / targetVelocityVector[2]));
                tmpTargetSpeed *= reductionFactor;
                targetVelocityVector[0] *= reductionFactor;
                targetVelocityVector[1] *= reductionFactor;
                targetVelocityVector[2] *= reductionFactor;
            }

            ///Redundant
            motorBlockX->freqSet = 0;
            motorBlockY->freqSet = 0;
//            motorBlockA->freqSet = 0;
            motorBlockZ->freqSet = 0;
//            motorBlockB->freqSet = 0;
//            motorBlockC->freqSet = 0;
//            motorBlockD->freqSet = 0;
            motorBlockT->freqSet = 0;

            ///Get the movement time in minutes.
            time = lineVectorMag / tmpTargetSpeed;

            ///Sync the motors before starting the movement.
//            if (fabs (motorBlockA->pos - motorBlockY->pos) > .05)
//            {
//                if (motorBlockA->pos < motorBlockY->pos)
//                {
//                    motorBlockA->targetSpeed = machineGlobalsBlock->targetSpeed;
//                    while (motorBlockA->pos < motorBlockY->pos)
//                    {
//                        tx_thread_relinquish ();
//                    }
//                }
//                else
//                {
//                    motorBlockA->targetSpeed = 0;
//                    motorBlockA->targetSpeed -= machineGlobalsBlock->targetSpeed;
//                    while (motorBlockA->pos > motorBlockY->pos)
//                    {
//                        tx_thread_relinquish ();
//                    }
//                }
//                stopMotor (motorBlockA);
//            }
            ///Set motor velocities and wait until target is reached.
            motorBlockX->targetSpeed = targetVelocityVector[0];
            motorBlockY->targetSpeed = targetVelocityVector[1];
//            motorBlockA->targetSpeed = targetVelocityVector[1];
//            motorBlockA->targetSpeed = (targetPos[1] - motorBlockA->pos) / time;

            motorBlockZ->targetSpeed = targetVelocityVector[2];
//            motorBlockB->targetSpeed = targetVelocityVector[2];
//            motorBlockC->targetSpeed = targetVelocityVector[2];
//            motorBlockD->targetSpeed = targetVelocityVector[2];

            if (machineGlobalsBlock->targetPosT != ~0)
            {
                if (lineVectorMag > 0)
                {
                    ///Perform extruder calculations.
                    if (time != 0)
                    {
                        extruderSpeed = ((machineGlobalsBlock->targetPosT - motorBlockT->pos) / time);
                    }
                    else
                    {
                        extruderSpeed = 0;
                    }
                    if (fabs (extruderSpeed) > 10000)
                    {
                        ///Skip extrusion if speed is beyond upper limit
//                        motorBlockT->targetSpeed = tmpTargetSpeed / 2;
                    }
                    else
                    {
                        motorBlockT->targetSpeed = (extruderSpeed / 2);
                    }

                }
                else
                {
                    ///There's no toolhead movement. This is just an extruder movement, probably a retraction.
                    extruderSpeed = 0;
                    if (machineGlobalsBlock->targetPosT > motorBlockT->pos)
                    {
                        extruderSpeed = (tmpTargetSpeed / 2);
                    }
                    else
                    {
                        extruderSpeed -= (tmpTargetSpeed / 2);
                    }
                    motorBlockT->targetSpeed = extruderSpeed;
                    while (fabs (motorBlockT->pos - machineGlobalsBlock->targetPosT) > .1)
                    {
                        tx_thread_relinquish ();
                    }
                }
            }

            ///Here the controller will need continuously check the current position against the target and re-calculate the motor speeds.
            /// This will allow the controller to respond to missed steps by adjusting the speed of the motors up or down to ensure the target position
            /// is reached by all axes at the same time, and the tolerance level is adhered to.

            ///Convert time from min to ms
//            time *= 60;
//            time *= 1000;
//            tx_thread_sleep (2 * time);

            do
            {
                tx_thread_relinquish ();

//                if (fabs (motorBlockA->pos - motorBlockY->pos) > .05)
//                {
//                    stopMotor (motorBlockX);
//                    stopMotor (motorBlockY);
//                    stopMotor (motorBlockA);
//                    stopMotor (motorBlockZ);
//                    stopMotor (motorBlockB);
//                    stopMotor (motorBlockC);
//                    stopMotor (motorBlockD);
//                    if (motorBlockA->pos < motorBlockY->pos)
//                    {
//                        motorBlockA->targetSpeed = machineGlobalsBlock->targetSpeed;
//                        while (motorBlockA->pos < motorBlockY->pos)
//                        {
//                            tx_thread_relinquish ();
//                        }
//                    }
//                    else
//                    {
//                        motorBlockA->targetSpeed = 0;
//                        motorBlockA->targetSpeed -= machineGlobalsBlock->targetSpeed;
//                        while (motorBlockA->pos > motorBlockY->pos)
//                        {
//                            tx_thread_relinquish ();
//                        }
//                    }
//                    stopMotor (motorBlockA);
//                }

                lineVector[0] = (targetPos[0] - motorBlockX->pos);
                lineVector[1] = (targetPos[1] - motorBlockY->pos);
                lineVector[2] = (targetPos[2] - motorBlockZ->pos);

                ///Calculate magnitude.
                lineVectorMag = sqrt (pow (lineVector[0], 2) + pow (lineVector[1], 2) + pow (lineVector[2], 2));

                ///Calculate the latest unit vector.
                if (lineVectorMag != 0)
                {
                    newUnitVector[0] = (lineVector[0] / lineVectorMag);
                    newUnitVector[1] = (lineVector[1] / lineVectorMag);
                    newUnitVector[2] = (lineVector[2] / lineVectorMag);
                }
                else
                {
                    newUnitVector[0] = 0;
                    newUnitVector[1] = 0;
                    newUnitVector[2] = 0;
                }

                ///The unit vector will provide the appropriate direction of each motor. Multiplying
                /// the unit vector by the target speed will provide the target velocity vector.
                ///Calculate the velocity vector.
                targetVelocityVector[0] = (tmpTargetSpeed * newUnitVector[0]);
                targetVelocityVector[1] = (tmpTargetSpeed * newUnitVector[1]);
                targetVelocityVector[2] = (tmpTargetSpeed * newUnitVector[2]);

                if (fabs (targetVelocityVector[2]) > 110.0)
                {
                    ///The z-axis movement speed is too high. Calculate the reduction factor and recalculate
                    /// the velocity vector based on this.
                    double reductionFactor = fabs ((110.0 / targetVelocityVector[2]));
                    tmpTargetSpeed *= reductionFactor;
                    targetVelocityVector[0] *= reductionFactor;
                    targetVelocityVector[1] *= reductionFactor;
                    targetVelocityVector[2] *= reductionFactor;
                }

                ///Set motor velocities and wait until target is reached.
                motorBlockX->targetSpeed = targetVelocityVector[0];
                motorBlockY->targetSpeed = targetVelocityVector[1];
//                motorBlockA->targetSpeed = targetVelocityVector[1];

//                time = lineVectorMag / tmpTargetSpeed;
//                if (machineGlobalsBlock->targetPosT != ~0)
//                {
//
//                    ///Perform extruder calculations.
//                    extruderSpeed = ((machineGlobalsBlock->targetPosT - motorBlockT->pos) / time);
//                    motorBlockT->targetSpeed = (extruderSpeed / 2.0);
//                }
//                motorBlockA->targetSpeed = ((targetPos[1] - motorBlockA->pos) / time);

                motorBlockZ->targetSpeed = targetVelocityVector[2];
//                motorBlockB->targetSpeed = targetVelocityVector[2];
//                motorBlockC->targetSpeed = targetVelocityVector[2];
//                motorBlockD->targetSpeed = targetVelocityVector[2];

            }
            while (lineVectorMag > .05);

            stopMotor (motorBlockX);
            stopMotor (motorBlockY);
//            stopMotor (motorBlockA);
            stopMotor (motorBlockZ);
//            stopMotor (motorBlockB);
//            stopMotor (motorBlockC);
//            stopMotor (motorBlockD);
            stopMotor (motorBlockT);

            if (machineGlobalsBlock->targetPosT != ~0)
            {
                motorBlockT->pos = machineGlobalsBlock->targetPosT;
            }
//            machineGlobalsBlock->UDPTxBuff[0] = 'R';
//            machineGlobalsBlock->UDPTxBuff[1] = 'D';
//            machineGlobalsBlock->UDPTxBuff[2] = 'Y';
//            UDPSend ();
            machineGlobalsBlock->idle = 1;
        }

//        if (DEBUG)
//        {
//            printf ("\nWaiting...");
//        }
//        tx_thread_sleep (3000);
        tx_thread_relinquish ();
    }
}

void ext_irqX_callback(external_irq_callback_args_t *p_args)
{
    limitHit (motorBlockX);

}

void ext_irqY_callback(external_irq_callback_args_t *p_args)
{
    limitHit (motorBlockY);
    limitHit (motorBlockA);
}
void ext_irqZ_callback(external_irq_callback_args_t *p_args)
{
    ///Debounce and set flag
//    ioport_level_t level;
//    ssp_err_t err;
//    R_BSP_SoftwareDelay (DEBOUNCE_TIME, BSP_DELAY_UNITS_MILLISECONDS);
//
//    err = g_ioport.p_api->pinRead (motorBlockZ->limit0Pin, &level);
//    if (level == IOPORT_LEVEL_LOW)
//    {
//        machineGlobalsBlock->reportIP = 1;
//    }

    limitHit (motorBlockZ);
//    limitHit (motorBlockB);
//    limitHit (motorBlockC);
//    limitHit (motorBlockD);

}

void g_external_irqXA_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockX);
}

void g_external_irqXB_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockX);
}

void g_external_irqYA_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockY);
}

void g_external_irqYB_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockY);
}

void g_external_irqAA_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockZ);
}

void g_external_irqAB_callback(external_irq_callback_args_t *p_args)
{
    encoderHandler (motorBlockZ);
}

void gpt_4_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockX);
}

void gpt_7_callback(timer_callback_args_t *p_args)
{

    stepHandler (motorBlockY);
}

void gpt_3_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockZ);

}

void gpt_0_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockT);
}

void gpt_1_callback(timer_callback_args_t *p_args)
{
    toolHandler (toolBlockA);
}

void gpt_MotorA_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockA);
}

void gpt_MotorB_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockB);
}

void gpt_MotorC_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockC);
}

void gpt_MotorD_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockD);
}

void gpt_MotorT_callback(timer_callback_args_t *p_args)
{
    stepHandler (motorBlockT);
}
void motorInitX()
{
    ssp_err_t err;
    err = g_external_irqX.p_api->open (g_external_irqX.p_ctrl, g_external_irqX.p_cfg);
    motorBlockX->homing = 0;
    motorBlockX->dirPin = IOPORT_PORT_04_PIN_12;
    motorBlockX->start = g_timer_gpt_4.p_api->start;
    motorBlockX->stop = g_timer_gpt_4.p_api->stop;
    motorBlockX->dutyCycleSet = g_timer_gpt_4.p_api->dutyCycleSet;
    motorBlockX->periodSet = g_timer_gpt_4.p_api->periodSet;
    motorBlockX->g_timer_gpt_x = g_timer_gpt_4;
    motorBlockX->stepsPerMM = STEPX;
    motorBlockX->stepPin = IOPORT_PORT_11_PIN_00;
    motorBlockX->stepState = IOPORT_LEVEL_LOW;
    motorBlockX->limit0Pin = IOPORT_PORT_02_PIN_02;
    motorBlockX->defaultDir = IOPORT_LEVEL_LOW;
    motorBlockX->targetDir = motorBlockX->defaultDir;
    motorBlockX->targetJerkSpeed = DEFAULTJERKSPEEDX;
    g_ioport.p_api->pinWrite (motorBlockX->dirPin, motorBlockX->defaultDir);
    motorBlockX->dir = motorBlockX->defaultDir;
    motorBlockX->fwdDir = IOPORT_LEVEL_LOW;
    motorBlockX->homeSpeed = HOMEVX;
    motorBlockX->rapidSpeed = HOMEVX;
    motorBlockX->limit0State = IOPORT_LEVEL_HIGH;
    motorBlockX->intervalSteps = 0;
    motorBlockX->freqSet = 0;
    motorBlockX->setPosSteps = 0;
    motorBlockX->pos = 0;
    motorBlockX->posSteps = 0;
    motorBlockX->posAbs = 0;
    motorBlockX->posStepsAbs = 0;
    motorBlockX->offsetSteps = 0;
    motorBlockX->targetSpeed = 0;
    motorBlockX->targetFreq = 0;
    motorBlockX->targetPosSteps = 0;
    motorBlockX->speed = 0;
    motorBlockX->frequency = 0;
}

void motorInitY()
{
    ssp_err_t err;
    err = g_external_irqY.p_api->open (g_external_irqY.p_ctrl, g_external_irqY.p_cfg);
    motorBlockY->homing = 0;
    motorBlockY->dirPin = IOPORT_PORT_04_PIN_11;
    motorBlockY->start = g_timer_gpt_7.p_api->start;
    motorBlockY->stop = g_timer_gpt_7.p_api->stop;
    motorBlockY->dutyCycleSet = g_timer_gpt_7.p_api->dutyCycleSet;
    motorBlockY->periodSet = g_timer_gpt_7.p_api->periodSet;
    motorBlockY->g_timer_gpt_x = g_timer_gpt_7;
    motorBlockY->stepsPerMM = STEPY;
    motorBlockY->stepPin = IOPORT_PORT_04_PIN_15;
    motorBlockY->stepState = IOPORT_LEVEL_LOW;
    motorBlockY->limit0Pin = IOPORT_PORT_04_PIN_08;
    motorBlockY->defaultDir = IOPORT_LEVEL_HIGH;
    motorBlockY->targetDir = motorBlockY->defaultDir;
    motorBlockY->targetJerkSpeed = DEFAULTJERKSPEEDY;
    g_ioport.p_api->pinWrite (motorBlockY->dirPin, motorBlockY->defaultDir);
    motorBlockY->dir = motorBlockY->defaultDir;
    motorBlockY->fwdDir = IOPORT_LEVEL_HIGH;
    motorBlockY->homeSpeed = HOMEVY;
    motorBlockY->rapidSpeed = HOMEVY;
    motorBlockY->limit0State = IOPORT_LEVEL_HIGH;
    motorBlockY->intervalSteps = 0;
    motorBlockY->freqSet = 0;
    motorBlockY->setPosSteps = 0;
    motorBlockY->pos = 0;
    motorBlockY->posSteps = 0;
    motorBlockY->posAbs = 0;
    motorBlockY->posStepsAbs = 0;
    motorBlockY->offsetSteps = 0;
    motorBlockY->targetSpeed = 0;
    motorBlockY->targetFreq = 0;
    motorBlockY->targetPosSteps = 0;
    motorBlockY->speed = 0;
    motorBlockY->frequency = 0;
}

void motorInitZ()
{
    ssp_err_t err;
    err = g_external_irqZ.p_api->open (g_external_irqZ.p_ctrl, g_external_irqZ.p_cfg);
    motorBlockZ->homing = 0;
    motorBlockZ->dirPin = IOPORT_PORT_04_PIN_10;
    motorBlockZ->start = g_timer_gpt_3.p_api->start;
    motorBlockZ->stop = g_timer_gpt_3.p_api->stop;
    motorBlockZ->dutyCycleSet = g_timer_gpt_3.p_api->dutyCycleSet;
    motorBlockZ->periodSet = g_timer_gpt_3.p_api->periodSet;
    motorBlockZ->g_timer_gpt_x = g_timer_gpt_3;
    motorBlockZ->stepsPerMM = STEPZ;
    motorBlockZ->stepPin = IOPORT_PORT_04_PIN_14;
    motorBlockZ->stepState = IOPORT_LEVEL_LOW;
    motorBlockZ->limit0Pin = IOPORT_PORT_02_PIN_03;
    motorBlockZ->defaultDir = IOPORT_LEVEL_LOW;
    motorBlockZ->targetDir = motorBlockZ->defaultDir;
    motorBlockZ->targetJerkSpeed = DEFAULTJERKSPEEDZ;
    g_ioport.p_api->pinWrite (motorBlockZ->dirPin, motorBlockZ->defaultDir);
    motorBlockZ->dir = motorBlockZ->defaultDir;
    motorBlockZ->fwdDir = IOPORT_LEVEL_HIGH;
    motorBlockZ->posSteps = 0;
    motorBlockZ->targetPosSteps = 0;
    motorBlockZ->offsetSteps = 0;
    motorBlockZ->homeSpeed = HOMEVZ;
    motorBlockZ->rapidSpeed = HOMEVZ;
    motorBlockZ->limit0State = IOPORT_LEVEL_HIGH;
    motorBlockZ->intervalSteps = 0;
    motorBlockZ->freqSet = 0;
    motorBlockZ->setPosSteps = 0;
    motorBlockZ->pos = 0;
    motorBlockZ->posSteps = 0;
    motorBlockZ->posAbs = 0;
    motorBlockZ->posStepsAbs = 0;
    motorBlockZ->offsetSteps = 0;
    motorBlockZ->targetSpeed = 0;
    motorBlockZ->targetFreq = 0;
    motorBlockZ->targetPosSteps = 0;
    motorBlockZ->speed = 0;
    motorBlockZ->frequency = 0;
}

void motorInitT()
{
    motorBlockT->homing = 0;
    motorBlockT->dirPin = IOPORT_PORT_04_PIN_09;
    motorBlockT->start = g_timer0.p_api->start;
    motorBlockT->stop = g_timer0.p_api->stop;
    motorBlockT->dutyCycleSet = g_timer0.p_api->dutyCycleSet;
    motorBlockT->periodSet = g_timer0.p_api->periodSet;
    motorBlockT->g_timer_gpt_x = g_timer0;
    motorBlockT->stepsPerMM = STEPX;
    motorBlockT->stepPin = IOPORT_PORT_04_PIN_13;
    motorBlockT->stepState = IOPORT_LEVEL_LOW;
    motorBlockT->limit0Pin = IOPORT_PORT_02_PIN_02;
    motorBlockT->defaultDir = IOPORT_LEVEL_LOW;
    motorBlockT->targetDir = motorBlockT->defaultDir;
    motorBlockT->targetJerkSpeed = DEFAULTJERKSPEEDX;
    g_ioport.p_api->pinWrite (motorBlockT->dirPin, motorBlockT->defaultDir);
    motorBlockT->dir = motorBlockT->defaultDir;
    motorBlockT->fwdDir = IOPORT_LEVEL_LOW;
    motorBlockT->homeSpeed = HOMEVX;
    motorBlockT->rapidSpeed = HOMEVX;
    motorBlockT->limit0State = IOPORT_LEVEL_HIGH;
    motorBlockT->intervalSteps = 0;
    motorBlockT->freqSet = 0;
    motorBlockT->setPosSteps = 0;
    motorBlockT->pos = 0;
    motorBlockT->posSteps = 0;
    motorBlockT->posAbs = 0;
    motorBlockT->posStepsAbs = 0;
    motorBlockT->offsetSteps = 0;
    motorBlockT->targetSpeed = 0;
    motorBlockT->targetFreq = 0;
    motorBlockT->targetPosSteps = 0;
    motorBlockT->speed = 0;
    motorBlockT->frequency = 0;
}

void toolInitA()
{
    toolBlockA->motorBlock = motorBlockT;
}

void genericMotorInit(struct motorController *motorBlock)
{
    ssp_err_t err;
    motorBlock->homing = 0;
    motorBlock->stepsPerMM = STEPZ;
    motorBlock->stepSize = (1.0 / STEPZ);
    motorBlock->stepState = IOPORT_LEVEL_LOW;
    motorBlock->defaultDir = IOPORT_LEVEL_LOW;
    motorBlock->targetDir = motorBlock->defaultDir;
    motorBlock->targetJerkSpeed = DEFAULTJERKSPEEDZ;
    g_ioport.p_api->pinWrite (motorBlock->dirPin, motorBlock->defaultDir);
    motorBlock->dir = motorBlock->defaultDir;
    motorBlock->fwdDir = IOPORT_LEVEL_HIGH;
    motorBlock->posSteps = 0;
    motorBlock->targetPosSteps = 0;
    motorBlock->offsetSteps = 0;
    motorBlock->homeSpeed = HOMEVZ;
    motorBlock->rapidSpeed = HOMEVZ;
    motorBlock->limit0State = IOPORT_LEVEL_HIGH;
    motorBlock->intervalSteps = 0;
    motorBlock->freqSet = 0;
    motorBlock->setPosSteps = 0;
    motorBlock->pos = 0;
    motorBlock->posSteps = 0;
    motorBlock->posAbs = 0;
    motorBlock->posStepsAbs = 0;
    motorBlock->offsetSteps = 0;
    motorBlock->targetSpeed = 0;
    motorBlock->targetFreq = 0;
    motorBlock->targetPosSteps = 0;
    motorBlock->speed = 0;
    motorBlock->frequency = 0;
    motorBlock->encoderActive = 0;
}

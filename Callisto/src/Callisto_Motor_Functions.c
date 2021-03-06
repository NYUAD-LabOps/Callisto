#include <Callisto.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math.h"

///The motor handler function makes speed and direction adjustments, and tracks position. Position is
/// calculated based on number of steps taken and the step size.
void motorHandler(struct motorController *motorBlock)
{
    int i;
    int prevTargetDir;
    int targetFreq, backOffSteps;
    double prevTargetSpeed, origSpeed;

    ///If the frequency adjustment flag is active, set the motor speed accordingly,
    /// else calculate and set frequency according to target speed and step size.
    ///if (motorBlock->limit0State == IOPORT_LEVEL_HIGH && motorBlock->homing == 0)
    if (motorBlock->homing == 0)
    {
        ///First check if it's to be set per frequency or speed
        if (motorBlock->freqSet == 1)
        {
            ///Check and set the direction.
            if (motorBlock->dir != motorBlock->targetDir)
            {
                ///The direction is wrong. Set it.
                setDir (motorBlock, motorBlock->targetDir);
            }
            if (motorBlock->frequency != motorBlock->targetFreq)
            {
                if (motorBlock->targetFreq == 0)
                {
                    stopMotor (motorBlock);
                }
                else
                {
                    targetFreq = motorBlock->targetFreq;
                    setSpeed (motorBlock, 1, 0, targetFreq);
                }
            }
            else
            {
                ///Motor is already running at correct frequency.
                /// Do nothing.
            }

        }
        else
        {
            if (motorBlock->dir != motorBlock->targetDir)
            {
                setDir (motorBlock, motorBlock->targetDir);

//                if (motorBlock->speed > motorBlock->targetJerkSpeed)
//                {
//                    ///The motor is moving too fast for a direction change.
//                    //                motorBlock->accelStepSize = (0.0 - motorBlock->speed) * 1.0;
//                    setSpeed (motorBlock, 0, motorBlock->targetJerkSpeed, 0);
//                }
//                else
//                {
//                    ///The motor is moving slow enough for a direction change.
//
//                }
            }
            else
            {
                if (motorBlock->targetSpeed == 0 && motorBlock->speed != 0)
                {
                    stopMotor (motorBlock);
                }
                else if (motorBlock->targetSpeed != motorBlock->speed)
                {
                    ///The current speed is too far off target.



//                    motorBlock->accelStepSize = (motorBlock->targetSpeed - motorBlock->speed) * 1.0;

                    ///Set the direction based on the sign of the speed
                    /// Currently this is highly redundant.
                    if (motorBlock->targetSpeed > 0)
                    {
                        motorBlock->targetDir = motorBlock->fwdDir;
                    }
                    else if (motorBlock->targetSpeed < 0)
                    {
                        if (motorBlock->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlock->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlock->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }

                    if(fabs(motorBlock->targetSpeed - motorBlock->speed) <= ACCELPERTICK){
                        setSpeed (motorBlock, 0, motorBlock->targetSpeed, 0);
                    } else{
                        /// Step it up or down by ACCELPERTICK and wait 1 tick
                        if(motorBlock->speed < motorBlock->targetSpeed){
                            setSpeed (motorBlock, 0, (motorBlock->speed + ACCELPERTICK), 0);
                        } else{
                            setSpeed (motorBlock, 0, (motorBlock->speed - ACCELPERTICK), 0);
                        }
                        tx_thread_sleep(1);
                    }
                }
            }
        }

    }
    else if (motorBlock->homing == 1)
    {
        ///The homing routine has been initiated.
        ///Set the direction and speed.
        setDir (motorBlock, motorBlock->defaultDir);
        setSpeed (motorBlock, 0, motorBlock->homeSpeed, 0);

        ///Let the motor run as long as the limit is inactive
        while (motorBlock->limit0State == IOPORT_LEVEL_HIGH)
            tx_thread_relinquish ();

        ///Reverse direction and let the motor run as long as the limit
        /// remains active.
        if (motorBlock->defaultDir == IOPORT_LEVEL_HIGH)
        {
            setDir (motorBlock, IOPORT_LEVEL_LOW);
        }
        else
        {
            setDir (motorBlock, IOPORT_LEVEL_HIGH);
        }
        while (motorBlock->limit0State == IOPORT_LEVEL_LOW)
            tx_thread_relinquish ();

        motorBlock->posSteps = 0;
        motorBlock->pos = 0;

        while (fabs (motorBlock->pos) < HOME_BACKOFF_DISTANCE)
        {
            tx_thread_relinquish ();
        }

        ///Stop the motor, reset position counter and homing flag.
        stopMotor (motorBlock);
        motorBlock->posSteps = 0;
        motorBlock->pos = 0;
        motorBlock->homing = 0;
    }

}

void setSpeed(struct motorController *motorBlock, int freqSet, double targetSpeed, int targetFreq)
{
    ssp_err_t err;
    int tmpTargetFreq;
    double tmp, tmpTargetSpeed;

    if (!freqSet)
    {
        ///Calculate timer frequency.
        tmp = targetSpeed;
        tmp /= 60; //Convert to mm/min to mm/s
        tmp *= motorBlock->stepsPerMM; //(mm/s) * (steps/mm) = steps/s = frequency
        tmpTargetFreq = (int) fabs (tmp);
        tmpTargetSpeed = targetSpeed;
    }
    else
    {
        tmpTargetFreq = targetFreq;
        ///To calculate the speed based on the frequency. We divide by the step size
        /// in order to obtain the speed in mm/s. Here our step size is steps/mm, not mm/step.
        tmpTargetSpeed = targetFreq;
        tmpTargetSpeed /= motorBlock->stepsPerMM;
    }

    ///Check if the motor GPT is already running. If not, it must be started.
    if (tmpTargetFreq > 0)
    {
        ///Start motor GPT
        motorBlock->start (motorBlock->g_timer_gpt_x.p_ctrl);
        err = motorBlock->periodSet (motorBlock->g_timer_gpt_x.p_ctrl, (2 * tmpTargetFreq), TIMER_UNIT_FREQUENCY_HZ);
    } else{
        motorBlock->stop (motorBlock->g_timer_gpt_x.p_ctrl);
    }



//    timer_info_t
    motorBlock->frequency = tmpTargetFreq;
    motorBlock->speed = tmpTargetSpeed;

    //    err = motorBlock->dutyCycleSet (motorBlock->g_timer_gpt_x.p_ctrl, 50, TIMER_PWM_UNIT_PERCENT, 0);
}

void setDir(struct motorController *motorBlock, ioport_level_t targetDir)
{
    ssp_err_t err;
    int targetFreq;
    double tmp;

    g_ioport.p_api->pinWrite (motorBlock->dirPin, targetDir);
    motorBlock->dir = targetDir;
}

///This function will stop a motor by stopping its GPT timer. It will also
/// reset the speed and frequency information to zero.
void stopMotor(struct motorController *motorBlock)
{
    ssp_err_t err;

    err = motorBlock->stop (motorBlock->g_timer_gpt_x.p_ctrl); // Stop timer
    motorBlock->targetSpeed = 0;
    motorBlock->targetFreq = 0;
    motorBlock->speed = 0;
    motorBlock->frequency = 0;

}

/**Handles behavior when limit switch is activated*/
void limitHit(struct motorController *motorBlock)
{
    ioport_level_t level;
    ssp_err_t err;
    R_BSP_SoftwareDelay (DEBOUNCE_TIME, BSP_DELAY_UNITS_MILLISECONDS);

    err = g_ioport.p_api->pinRead (motorBlock->limit0Pin, &level);
    motorBlock->limit0State = level;

    ///If the limit has been activated, and the motor is not in a homing routine,
    /// stop the motor.
    if (level == IOPORT_LEVEL_LOW && motorBlock->homing == 0)
    {
        stopMotor (motorBlock);
    }
}

///Handles counting steps, stopping the motor when target position is reached, and toggling the STEP pin.
void stepHandler(struct motorController *motorBlock)
{
    ioport_level_t level;
    ssp_err_t err;
    if (motorBlock->stepState == IOPORT_LEVEL_HIGH)
    {
        err = g_ioport.p_api->pinWrite (motorBlock->stepPin, IOPORT_LEVEL_LOW);
        motorBlock->stepState = IOPORT_LEVEL_LOW;
    }
    else
    {
        err = g_ioport.p_api->pinWrite (motorBlock->stepPin, IOPORT_LEVEL_HIGH);
        motorBlock->stepState = IOPORT_LEVEL_HIGH;

        if (motorBlock->encoderActive != 1)
        {
            ///Without an active encoder, position must be tracked open-loop, via the step output.
            ///Increment or decrement the motor position by the stepSize
            if (motorBlock->dir == motorBlock->fwdDir)
            {
                motorBlock->posSteps++;
                motorBlock->pos += motorBlock->stepSize;
            }
            else
            {
                motorBlock->posSteps--;
                motorBlock->pos -= motorBlock->stepSize;
            }
        }

    }
}

void encoderHandler(struct motorController *motorBlock)
{
    ioport_level_t levelA, levelB;
    ssp_err_t err;

    err = g_ioport.p_api->pinRead (motorBlock->encoderAPin, &levelA);
    err = g_ioport.p_api->pinRead (motorBlock->encoderBPin, &levelB);

    if (levelA == IOPORT_LEVEL_LOW && levelB == IOPORT_LEVEL_LOW)
    {
        if (motorBlock->encoderAState == IOPORT_LEVEL_HIGH && motorBlock->encoderBState == IOPORT_LEVEL_LOW)
        {
            ///CW
            if (motorBlock->encoderCWFWD)
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
        else if (motorBlock->encoderAState == IOPORT_LEVEL_LOW && motorBlock->encoderBState == IOPORT_LEVEL_HIGH)
        {
            ///CCW
            if (!(motorBlock->encoderCWFWD))
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
    }
    else if (levelA == IOPORT_LEVEL_LOW && levelB == IOPORT_LEVEL_HIGH)
    {
        if (motorBlock->encoderAState == IOPORT_LEVEL_LOW && motorBlock->encoderBState == IOPORT_LEVEL_LOW)
        {
            ///CW
            if (motorBlock->encoderCWFWD)
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
        else if (motorBlock->encoderAState == IOPORT_LEVEL_HIGH && motorBlock->encoderBState == IOPORT_LEVEL_HIGH)
        {
            ///CCW
            if (!(motorBlock->encoderCWFWD))
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
    }
    else if (levelA == IOPORT_LEVEL_HIGH && levelB == IOPORT_LEVEL_LOW)
    {
        if (motorBlock->encoderAState == IOPORT_LEVEL_HIGH && motorBlock->encoderBState == IOPORT_LEVEL_HIGH)
        {
            ///CW
            if (motorBlock->encoderCWFWD)
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
        else if (motorBlock->encoderAState == IOPORT_LEVEL_LOW && motorBlock->encoderBState == IOPORT_LEVEL_LOW)
        {
            ///CCW
            if (!(motorBlock->encoderCWFWD))
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
    }
    else if (levelA == IOPORT_LEVEL_HIGH && levelB == IOPORT_LEVEL_HIGH)
    {
        if (motorBlock->encoderAState == IOPORT_LEVEL_LOW && motorBlock->encoderBState == IOPORT_LEVEL_HIGH)
        {
            ///CW
            if (motorBlock->encoderCWFWD)
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
        else if (motorBlock->encoderAState == IOPORT_LEVEL_HIGH && motorBlock->encoderBState == IOPORT_LEVEL_LOW)
        {
            ///CCW
            if (!(motorBlock->encoderCWFWD))
            {
                motorBlock->pos += motorBlock->encoderMMPerPulse;
                motorBlock->posSteps += motorBlock->stepsPerEncoderPulse;
            }
            else
            {
                motorBlock->pos -= motorBlock->encoderMMPerPulse;
                motorBlock->posSteps -= motorBlock->stepsPerEncoderPulse;
            }
        }
    }

    motorBlock->encoderAState = levelA;
    motorBlock->encoderBState = levelB;
}

#include <Callisto.h>
#include "UDP.h"
#define APP_UDP_PORT_BASE       5000
#define APP_UDP_INSTANT_RX      1
#define APP_UDP_RTT_LOG         (1)
static NX_UDP_SOCKET g_udp_sck;

static void g_udp_sck_receive_cb(NX_UDP_SOCKET *);

/* UDP entry function */
void UDP_entry(void)
{
    UINT status;
    ULONG link_status;
    ULONG currentIP;
    ULONG currentMask;
    /* Create all sockets and bind them to their respective ports */
    /* Wait for the IP stack and network hardware
     * to get initialized.
     */
    ip_init0 ();
    tx_thread_sleep (50);
    while (machineGlobalsBlock->globalsInit != 1)
        tx_thread_sleep (1);

    status = nx_ip_status_check (&g_ip0, NX_IP_INITIALIZE_DONE, &link_status, NX_WAIT_FOREVER);
    /* Check for error.  */
    if (NX_SUCCESS != status)
    {
        if (DEBUGGER)
            printf ("\nFail.");
    }
    else
    {
        if (DEBUGGER)
            printf ("\nLink enabled.");
    }

    if (DEBUGGER)
    {
        printf ("\nIP initialization complete. IP:%s", IPADDSTRING);
    }

    //    status = nx_udp_socket_create(&g_ip0, &machineGlobalsBlock->g_udp_sck, "UDP Socket", NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE,
    //                                  512);
    status = nx_udp_socket_create(&g_ip0, &machineGlobalsBlock->g_udp_sck, "UDP Socket", NX_IP_NORMAL, NX_DONT_FRAGMENT,
                                  NX_IP_TIME_TO_LIVE, 512);
    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nFail.");
        }
        else
        {
            printf ("\nUDP socket creation sucessful.");
        }
    }

    status = nx_udp_socket_bind (&machineGlobalsBlock->g_udp_sck, APP_UDP_PORT_BASE, NX_NO_WAIT);

    if (DEBUGGER)
    {

        if (NX_SUCCESS != status)
        {
            printf ("\nFail.");
        }
        else
        {
            printf ("\nUDP socket binding successful.");
        }
    }

    status = nx_udp_socket_receive_notify (&machineGlobalsBlock->g_udp_sck, g_udp_sck_receive_cb);
    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nFail.");
        }
        else
        {
            printf ("\nUDP receive interrupt setup successful. Bound to port:%d",
                    machineGlobalsBlock->g_udp_sck.nx_udp_socket_port);
        }
    }

    if (DEBUGGER)
    {
        printf ("\nUDP initialization complete.");
    }

    while (machineGlobalsBlock->motorsInit != 1)
    {
        tx_thread_sleep (10);
    }

//    tx_thread_sleep(500);
//    memset(machineGlobalsBlock->UDPTxBuff, 0, UDPMSGLENGTH);
//    machineGlobalsBlock->UDPTxBuff[0] = 'I';
//    machineGlobalsBlock->UDPTxBuff[1] = 'N';
//    machineGlobalsBlock->UDPTxBuff[2] = 'I';
//    UDPSend ();
//    memset(machineGlobalsBlock->UDPTxBuff, 0, UDPMSGLENGTH);

    while (1)
    {
        tx_thread_suspend (tx_thread_identify ());
    }

}

void UDPSend()
{
    UINT status;
    ioport_level_t level;
    NX_PACKET *my_packet;
    status = nx_packet_allocate (&g_packet_pool0, &my_packet, NX_UDP_PACKET, 500);
    if (status != NX_SUCCESS)
    {
        printf ("\nAllocate Fail.");
    }
    nx_packet_data_append (my_packet, &machineGlobalsBlock->UDPTxBuff, UDPMSGLENGTH, &g_packet_pool0,
    NX_WAIT_FOREVER);
    if (DEBUG)
    {
        printf ("\nSending:%s...", machineGlobalsBlock->UDPTxBuff);
    }
    status = nx_udp_socket_send(&machineGlobalsBlock->g_udp_sck, my_packet, PRIMARY_IP, PRIMARY_PORT);
//    if (NX_SUCCESS == status)
//    {
//        printf ("\nSend success.");
//    }
    if (status != NX_SUCCESS)
    {
        status = nx_packet_release(my_packet);
        if (status != NX_SUCCESS)
        {
            printf ("\nRelease Fail b.");
        }
    }
    else
    {

    }
    if (DEBUG)
    {
        if (NX_SUCCESS == status)
        {
            printf ("\nSend success.");
        }
        else
        {
            printf ("\nSend fail.");
        }
    }

}

void UDPSendRDY()
{
    machineGlobalsBlock->UDPTxBuff[0] = 'R';
    machineGlobalsBlock->UDPTxBuff[1] = 'D';
    UDPSend ();
}

void processUDP(char *UDPRx)
{
    double data;
    int dataInt;
    ioport_level_t level;
    ULONG newIP;
    switch (UDPRx[0])
    {
        case '0':
            ///Set axis Steps per MM.
            switch (UDPRx[1])
            {
                case 'x':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockX->stepsPerMM = data;
                    motorBlockX->stepSize = (1.0 / data);

                    motorBlockX->encoderMMPerPulse = ((STEPSPERREVOLUTION / motorBlockX->stepsPerMM)
                            / (ENCODERPULSESPERREVOLUTION));
                    motorBlockX->stepsPerEncoderPulse = (motorBlockX->stepsPerMM * motorBlockX->encoderMMPerPulse);
                break;
                case 'y':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockY->stepsPerMM = data;
                    motorBlockY->stepSize = (1.0 / data);
                    motorBlockY->encoderMMPerPulse = ((STEPSPERREVOLUTION / data) / (ENCODERPULSESPERREVOLUTION));
                    motorBlockY->stepsPerEncoderPulse = (motorBlockY->stepsPerMM * motorBlockY->encoderMMPerPulse);
                break;
                case 'a':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockA->stepsPerMM = data;
                    motorBlockA->stepSize = (1.0 / data);
                    motorBlockA->encoderMMPerPulse = ((STEPSPERREVOLUTION / data) / (ENCODERPULSESPERREVOLUTION));
                    motorBlockA->stepsPerEncoderPulse = (motorBlockA->stepsPerMM * motorBlockA->encoderMMPerPulse);
                break;
                case 'z':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockZ->stepsPerMM = data;
                    motorBlockZ->stepSize = (1.0 / data);
                    motorBlockZ->encoderMMPerPulse = ((STEPSPERREVOLUTION / data) / (ENCODERPULSESPERREVOLUTION));
                    motorBlockZ->stepsPerEncoderPulse = (motorBlockZ->stepsPerMM * motorBlockZ->encoderMMPerPulse);
                break;
                case 'b':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockB->stepsPerMM = data;
                    motorBlockB->stepSize = (1.0 / data);
                break;
                case 'c':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockC->stepsPerMM = data;
                    motorBlockC->stepSize = (1.0 / data);
                break;
                case 'd':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockD->stepsPerMM = data;
                    motorBlockD->stepSize = (1.0 / data);
                break;
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);

                    toolBlockA->motorBlock->stepsPerMM = data;
                    toolBlockA->motorBlock->stepSize = (1.0 / data);
                break;
                default:
                break;
            }
        break;
        case '1':
            ///Set axis Forward Logic Level.
            switch (UDPRx[1])
            {
                case 'x':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockX->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockX->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'y':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockY->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockY->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'a':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockA->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockA->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'z':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockZ->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockZ->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'b':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockB->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockB->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'c':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockC->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockC->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'd':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockD->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockD->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 't':
                    if (UDPRx[2] == 'h')
                    {
                        toolBlockA->motorBlock->fwdDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        toolBlockA->motorBlock->fwdDir = IOPORT_LEVEL_LOW;
                    }
                break;
            }
        break;
        case '2':
            ///Set axis Home Logic Level.
            switch (UDPRx[1])
            {
                case 'x':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockX->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockX->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'y':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockY->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockY->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'a':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockA->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockA->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'z':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockZ->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockZ->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'b':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockB->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockB->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'c':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockC->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockC->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 'd':
                    if (UDPRx[2] == 'h')
                    {
                        motorBlockD->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        motorBlockD->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
                case 't':
                    if (UDPRx[2] == 'h')
                    {
                        toolBlockA->motorBlock->defaultDir = IOPORT_LEVEL_HIGH;
                    }
                    else
                    {
                        toolBlockA->motorBlock->defaultDir = IOPORT_LEVEL_LOW;
                    }
                break;
            }
        break;
        case '3':
            ///Set axis Home Speed.
            switch (UDPRx[1])
            {
                case 'x':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockX->homeSpeed = data;
                break;
                case 'y':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockY->homeSpeed = data;
                break;
                case 'a':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockA->homeSpeed = data;
                break;
                case 'z':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockZ->homeSpeed = data;
                break;
                case 'b':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockB->homeSpeed = data;
                break;
                case 'c':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockC->homeSpeed = data;
                break;
                case 'd':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockD->homeSpeed = data;
                break;
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);

                    toolBlockA->motorBlock->homeSpeed = data;
                break;
                default:
                break;
            }
        break;
        case '4':
            ///Set tool temperature
            switch (UDPRx[1])
            {
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);

                    toolBlockA->tempSet = data;
                break;
                default:
                break;
            }
        break;
        case '5':
            ///Send tool temperature to master
            switch (UDPRx[1])
            {
                case 't':
                    memcpy ((machineGlobalsBlock->UDPTxBuff + 2), &toolBlockA->tempRead, 8);
                break;
                default:
                break;
            }
            UDPSend ();
        break;
        case '6':
            ///Master will request ready status.
            machineGlobalsBlock->UDPTxBuff[0] = 't';
            machineGlobalsBlock->UDPTxBuff[1] = 'x';
            if (machineGlobalsBlock->idle == 0)
            {
                machineGlobalsBlock->UDPTxBuff[2] = '1';
            }
            else
            {
                machineGlobalsBlock->UDPTxBuff[2] = '0';
            }
            UDPSend ();
        break;
        case 'a':
            ///Receive new IP assignment
            switch (UDPRx[1])
            {
                case 'a':
                    memcpy (&newIP, (UDPRx + 2), 8);
                    machineGlobalsBlock->ethIP = newIP;
                break;
                default:
                break;
            }
        break;
        case 'b':
            ///A new set of target positions and speed.

            memcpy (&data, (UDPRx + 2), 8);
            machineGlobalsBlock->targetPosX = data;

            memcpy (&data, (UDPRx + 10), 8);
            machineGlobalsBlock->targetPosY = data;

            memcpy (&data, (UDPRx + 18), 8);
            machineGlobalsBlock->targetPosZ = data;

            memcpy (&data, (UDPRx + 26), 8);
            machineGlobalsBlock->targetPosT = data;

            memcpy (&data, (UDPRx + 34), 8);
            if (data != ~0)
            {
                machineGlobalsBlock->targetSpeed = data;
            }

            machineGlobalsBlock->newTarget = 1;
            machineGlobalsBlock->idle = 0;
        break;
        case 'c':
            ///Calibrate axis.
            switch (UDPRx[1])
            {
                case 'x':
                    calRoutine (motorBlockX);
                break;
                case 'y':
                    calRoutine (motorBlockY);
                break;
                case 'a':
                    calRoutine (motorBlockA);
                break;
                case 'z':
                    calRoutine (motorBlockZ);
                break;
                case 'b':
                    calRoutine (motorBlockB);
                break;
                case 'c':
                    calRoutine (motorBlockC);
                break;
                case 'd':
                    calRoutine (motorBlockD);
                break;
                case 't':
                    calRoutine (toolBlockA->motorBlock);
                break;
                default:
                break;
            }
        break;
        case 'd':
            ///Set motor direction.
            switch (UDPRx[1])
            {
                case 'x':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockX->targetDir = motorBlockX->fwdDir;
                    }
                    else
                    {
                        if (motorBlockX->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockX->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockX->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'y':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockY->targetDir = motorBlockY->fwdDir;
                    }
                    else
                    {
                        if (motorBlockY->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockY->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockY->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'a':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockA->targetDir = motorBlockA->fwdDir;
                    }
                    else
                    {
                        if (motorBlockA->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockA->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockA->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'z':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockZ->targetDir = motorBlockZ->fwdDir;
                    }
                    else
                    {
                        if (motorBlockZ->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockZ->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockZ->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'b':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockB->targetDir = motorBlockB->fwdDir;
                    }
                    else
                    {
                        if (motorBlockB->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockB->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockB->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'c':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockC->targetDir = motorBlockC->fwdDir;
                    }
                    else
                    {
                        if (motorBlockC->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockC->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockC->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 'd':
                    if (UDPRx[2] == 'f')
                    {
                        motorBlockD->targetDir = motorBlockD->fwdDir;
                    }
                    else
                    {
                        if (motorBlockD->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            motorBlockD->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            motorBlockD->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
                case 't':
                    if (UDPRx[2] == 'f')
                    {
                        toolBlockA->motorBlock->targetDir = toolBlockA->motorBlock->fwdDir;
                    }
                    else
                    {
                        if (toolBlockA->motorBlock->fwdDir == IOPORT_LEVEL_HIGH)
                        {
                            toolBlockA->motorBlock->targetDir = IOPORT_LEVEL_LOW;
                        }
                        else
                        {
                            toolBlockA->motorBlock->targetDir = IOPORT_LEVEL_HIGH;
                        }
                    }
                break;
            }
        break;
        case 'f':
            ///Run motor at frequency.
            switch (UDPRx[1])
            {
                case 'x':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockX->targetFreq = data;

                    motorBlockX->freqSet = 1;
                break;
                case 'y':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockY->targetFreq = data;
                    motorBlockY->freqSet = 1;
                break;
                case 'a':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockA->targetFreq = data;
                    motorBlockA->freqSet = 1;
                break;
                case 'b':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockB->targetFreq = data;
                    motorBlockB->freqSet = 1;
                break;
                case 'c':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockC->targetFreq = data;
                    motorBlockC->freqSet = 1;
                break;
                case 'd':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockD->targetFreq = data;
                    motorBlockD->freqSet = 1;
                break;
                case 'z':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockZ->targetFreq = data;
                    motorBlockZ->freqSet = 1;
                break;
                case 't':

                    memcpy (&data, (UDPRx + 2), 8);

                    toolBlockA->motorBlock->targetFreq = data;
                    toolBlockA->motorBlock->freqSet = 1;
                break;
            }
        break;
        case 'g':
            ///Set motor at frequency.
            switch (UDPRx[1])
            {
                case 'x':

                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockX->targetFreq = data;
                    motorBlockX->freqSet = 1;

                break;
                case 'y':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockY->targetFreq = data;
                    motorBlockY->freqSet = 1;
                break;
                case 'z':
                    memcpy (&data, (UDPRx + 2), 8);

                    motorBlockZ->targetFreq = data;
                    motorBlockZ->freqSet = 1;
                break;
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);

                    toolBlockA->motorBlock->targetFreq = data;
                    toolBlockA->motorBlock->freqSet = 1;
                break;
            }
        break;
        case 'h':
            ///Home axis.
            switch (UDPRx[1])
            {
                case 'x':
                    motorBlockX->homing = 1;
                break;
                case 'y':
                    motorBlockY->homing = 1;
                break;
                case 'a':
                    motorBlockA->homing = 1;
                break;
                case 'z':
                    motorBlockZ->homing = 1;
                break;
                case 'b':
                    motorBlockB->homing = 1;
                break;
                case 'c':
                    motorBlockC->homing = 1;
                break;
                case 'd':
                    motorBlockD->homing = 1;
                break;
                default:
                break;
            }
        break;
        case 'i':
            ///Set motor freqSet setting.
            motorBlockX->freqSet = UDPRx[2];

            motorBlockY->freqSet = UDPRx[2];
            motorBlockA->freqSet = UDPRx[2];

            motorBlockZ->freqSet = UDPRx[2];
            motorBlockB->freqSet = UDPRx[2];
            motorBlockC->freqSet = UDPRx[2];
            motorBlockD->freqSet = UDPRx[2];

            toolBlockA->motorBlock->freqSet = UDPRx[2];
        break;
        case 'p':
            ///Set target position. The Secondary receives a target (X,Y,Z,T) and a speed.
            ///Next, the Secondary must calculate the target velocity vector based on the target speed
            /// and position. Then, set the motors to the new speed, which is the components of the vector, except
            /// for the extruder, which is calculated separately based on the movement time.

        case 'q':
            ///Set axis target position steps.
            switch (UDPRx[1])
            {
                case 'x':

                    memcpy (&data, (UDPRx + 2), 8);
                    dataInt = data;

                    motorBlockX->targetPosSteps = dataInt;

                break;
                case 'y':
                    memcpy (&data, (UDPRx + 2), 8);
                    dataInt = data;

                    motorBlockY->targetPosSteps = dataInt;
                break;
                case 'z':
                    memcpy (&data, (UDPRx + 2), 8);
                    dataInt = data;

                    motorBlockZ->targetPosSteps = dataInt;
                break;
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);
                    dataInt = data;

                    toolBlockA->motorBlock->targetPosSteps = dataInt;
                break;
            }
        break;
        case 'r':
            ///Set relay.
            switch (UDPRx[1])
            {
                case 'x':
                    switch (UDPRx[2])
                    {
                        case '0':
                            switch (UDPRx[3])
                            {
                                case 'h':

                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay0, IOPORT_LEVEL_HIGH);
                                break;
                                case 'l':
                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay0, IOPORT_LEVEL_LOW);
                                break;
                            }

                        break;
                        case '1':
                            switch (UDPRx[3])
                            {
                                case 'h':

                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay1, IOPORT_LEVEL_HIGH);
                                break;
                                case 'l':
                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay1, IOPORT_LEVEL_LOW);
                                break;
                            }
                        break;
                        case '2':
                            switch (UDPRx[3])
                            {
                                case 'h':

                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay2, IOPORT_LEVEL_HIGH);
                                break;
                                case 'l':
                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay2, IOPORT_LEVEL_LOW);
                                break;
                            }
                        break;
                        case '3':
                            switch (UDPRx[3])
                            {
                                case 'h':

                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay3, IOPORT_LEVEL_HIGH);
                                break;
                                case 'l':
                                    g_ioport.p_api->pinWrite (machineGlobalsBlock->relay3, IOPORT_LEVEL_LOW);
                                break;
                            }
                        break;
                    }
                break;
                case 'y':

                break;
                case 'z':

                break;
            }
        break;
        case 's':
            ///Stop motor.
            switch (UDPRx[1])
            {
                case 'x':
                    stopMotor (motorBlockX);
                break;
                case 'y':
                    stopMotor (motorBlockY);
                break;
                case 'a':
                    stopMotor (motorBlockA);
                break;
                case 'b':
                    stopMotor (motorBlockB);
                break;
                case 'c':
                    stopMotor (motorBlockC);
                break;
                case 'd':
                    stopMotor (motorBlockD);
                break;
                case 'z':
                    stopMotor (motorBlockZ);
                break;
                case 't':
                    stopMotor (toolBlockA->motorBlock);
                break;
                default:
                break;
            }
        break;
        case 't':
            ///Master will request slave status.
            machineGlobalsBlock->UDPTxBuff[0] = 't';
            machineGlobalsBlock->UDPTxBuff[1] = 'x';
            if (motorBlockX->homing == 1 || motorBlockY->homing == 1 || motorBlockA->homing == 1
                    || motorBlockZ->homing == 1 || motorBlockB->homing == 1 || motorBlockC->homing == 1
                    || motorBlockD->homing == 1 || machineGlobalsBlock->idle == 0)
            {
                machineGlobalsBlock->UDPTxBuff[2] = '1';
            }
            else
            {
                machineGlobalsBlock->UDPTxBuff[2] = '0';
            }
            UDPSend ();

        break;
        case 'u':
            ///Send axis position data to master.
            switch (UDPRx[1])
            {
                case 'x':
                    memcpy ((machineGlobalsBlock->UDPTxBuff + 2), &motorBlockX->pos, 8);
                break;
                case 'y':
                    memcpy ((machineGlobalsBlock->UDPTxBuff + 2), &motorBlockY->pos, 8);
                break;
                case 'z':
                    memcpy ((machineGlobalsBlock->UDPTxBuff + 2), &motorBlockZ->pos, 8);
                break;
                case 't':
                    memcpy ((machineGlobalsBlock->UDPTxBuff + 2), &toolBlockA->motorBlock->pos, 8);
                break;
                default:
                break;
            }
            UDPSend ();
        break;
        case 'v':
            ///Set axis target velocity.
            switch (UDPRx[1])
            {
                case 'x':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockX->targetSpeed = data;
                break;
                case 'y':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockY->targetSpeed = data;
                break;
                case 'a':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockA->targetSpeed = data;
                break;
                case 'z':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockZ->targetSpeed = data;
                break;
                case 'b':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockB->targetSpeed = data;
                break;
                case 'c':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockC->targetSpeed = data;
                break;
                case 'd':
                    memcpy (&data, (UDPRx + 2), 8);
                    motorBlockD->targetSpeed = data;
                break;
                case 't':
                    memcpy (&data, (UDPRx + 2), 8);
                    toolBlockA->motorBlock->targetSpeed = data;
                break;
            }
        break;
        case 'z':
            ///Zero axes.
            if (UDPRx[1] == 'z')
            {
                motorBlockX->posSteps = 0;
                motorBlockY->posSteps = 0;
                motorBlockA->posSteps = 0;
                motorBlockZ->posSteps = 0;
                motorBlockB->posSteps = 0;
                motorBlockC->posSteps = 0;
                motorBlockD->posSteps = 0;
                toolBlockA->motorBlock->posSteps = 0;

                motorBlockX->pos = 0;
                motorBlockY->pos = 0;
                motorBlockA->pos = 0;
                motorBlockZ->pos = 0;
                motorBlockB->pos = 0;
                motorBlockC->pos = 0;
                motorBlockD->pos = 0;
                toolBlockA->motorBlock->pos = 0;
            }
        break;
    }

//    memset (p_packet->nx_packet_prepend_ptr, 0, 15);
//    machineGlobalsBlock->UDPRXReady = 0;

///Send ready message to master
//    UDPSendRDY();

///Drive idle pin LOW to indicate the machine is ready for more data.
//    g_ioport.p_api->pinWrite (machineGlobalsBlock->idlePin, IOPORT_LEVEL_LOW);
}

static void g_udp_sck_receive_cb(NX_UDP_SOCKET *p_sck)
{
    UINT status;
    NX_PACKET *p_packet = NULL;
    ULONG *length;
    char buff[UDPMSGLENGTH];
    ULONG srcIP;
    UINT srcPort;

    /* Receive data here */
    status = nx_udp_socket_receive (p_sck, &p_packet, NX_NO_WAIT);
    if (status == NX_SUCCESS)
    {
        memcpy (buff, p_packet->nx_packet_prepend_ptr, UDPMSGLENGTH);

        //        nx_udp_source_extract (p_packet, &srcIP, &srcPort);

        ///Don't send an echo for IP packets. Primary does not have event flag for it.
        if (buff[0] != 'a' || buff[1] != 'a')
        {
            p_packet->nx_packet_prepend_ptr[0] = 'A';
            p_packet->nx_packet_prepend_ptr[1] = 'C';
            p_packet->nx_packet_prepend_ptr[2] = 'K';

            status = nx_udp_socket_send(&machineGlobalsBlock->g_udp_sck, p_packet, PRIMARY_IP, PRIMARY_PORT);

            if (status != NX_SUCCESS)
            {
                if (DEBUG)
                    printf ("\nEcho Fail.");
            }
            else
            {

            }
            if (DEBUG)
            {
                if (NX_SUCCESS == status)
                {
                    printf ("\nEcho send success.");
                }
                else
                {
                    printf ("\nEcho send fail.");
                }
            }
        }

        if (DEBUG)
        {
            printf ("\nReceived:%s", buff);
        }
        if (NULL != buff[0])
        {
            processUDP (buff);
        }
        status = nx_packet_release(p_packet);
    }
    else
    {
        if (DEBUG)
            printf ("\nReceive Fail.");
    }

}

void setMacAddress(nx_mac_address_t *_pMacAddress)

{

    //  REA's Vendor MAC range: 00:30:55:xx:xx:xx

    fmi_unique_id_t id;

    g_fmi.p_api->uniqueIdGet (&id);

    ULONG lowerHalfMac = ((0x55000000) | (id.unique_id[0] & (0x00FFFFFF)));

    _pMacAddress->nx_mac_address_h = 0x0030;

    _pMacAddress->nx_mac_address_l = lowerHalfMac;

}

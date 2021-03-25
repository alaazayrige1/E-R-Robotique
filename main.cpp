#include "Lidar.h"
#include "PointeurLaser.h"
#include "Robot_total.h"



Thread thread_lidar;
Thread thread_pointeurlaser;
Thread thread_asser;
Thread thread_match;

Timer Temps_match;

DigitalIn detectionface(PF_12);
DigitalIn detectionderriere(PF_13);
DigitalOut out1(PF_14);
DigitalOut out2(PF_15);
PwmOut projpwm(PD_0);

DigitalOut LedG(LED1, 0);

char matchencours = 1;


int main()
{
    thread_lidar.start(&fonctionlidar);
    thread_pointeurlaser.start(&fonctionpointeurlaser);
    Thread_Stockage_Variable_Un.start(&Fct_Stockage_Variable_Un);
    put_angle_un.start(&put_angle_un_fct);
    LidarSerialUn.attach(&Lidar_lecture_fct);
    LidarSerialDeux.attach(&Lidar_lecture_fct_deux);
    thread_asser.start(&fonctionasser);
    thread_match.start(&fonctiontempsmatch);

    Temps_match.start();
    printf("on\n");
    while(matchencours == 1)
    {
        ThisThread::sleep_for(1000ms);
        LedG = !LedG;
    }
    //return 0;
}

void fonctiontempsmatch()
{
    while(1)
    {
        static float timerval;
        //timerval = Temps_match.read();
        if(Temps_match.read() > 20)
        {
            Temps_match.stop();
            Temps_match.reset();
            // STOPPER LE PROGRAMME
            matchencours = 0;
        }
    }
}

void projection()
{
    while(1)
    {
        if(detectionface == 1)
        {
            out1 = 1;
            projpwm = 1;
            // PROJECTION SENS DEVANT ACTIVE
        }
        if(detectionderriere == 1)
        {
            out2 = 1;
            projpwm = 1;
            // PROJECTION SENS DERRIERE ACTIVE
        }
        ThisThread::sleep_for(200ms);
    }
}


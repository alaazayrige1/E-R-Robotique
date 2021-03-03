///`c
#include "Lidar.h"
#include "PointeurLaser.h"
#include "Robot_total.h"




Thread thread_lidar;
Thread thread_pointeurlaser;
DigitalOut LedR(LED3, 0);
//UnbufferedSerial pc(USBTX, USBRX, 115200);

// main() runs in its own thread in the OS
int main()
{
    thread_lidar.start(&fonctionlidar);
    thread_pointeurlaser.start(&fonctionpointeurlaser);
    Thread_Stockage_Variable_Un.start(&Fct_Stockage_Variable_Un);
    put_angle_un.start(&put_angle_un_fct);
    LidarSerial.attach(&Lidar_lecture_fct);
    printf("on\n");
    while(1)
    {
        ThisThread::sleep_for(1000ms);
        LedR = !LedR;
    }
}'///

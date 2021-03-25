#include "PointeurLaser.h"



AnalogIn LaserUn(PA_3);
AnalogIn LaserDeux(PC_0);
AnalogIn LaserTrois(PC_3);
AnalogIn LaserQuatre(PF_3);

char position_laser_un = 0;
char position_laser_deux = 0;
char position_laser_trois = 0;
char position_laser_quatre = 0;
char laserun_proche = 0;
char laserdeux_proche = 0;
char lasertrois_proche = 0;
char laserquatre_proche = 0;


void fonctionpointeurlaser()
{
    while(1)
    {
    position_laser_un = LaserUn.read();
    position_laser_deux = LaserUn.read();
    position_laser_trois = LaserUn.read();
    position_laser_quatre = LaserUn.read();
    if(position_laser_un>valeurlimite)
    {
        laserun_proche = 1;
    }
    else
    {
        laserun_proche = 0;
    }
    if(position_laser_deux>valeurlimite)
    {
        laserdeux_proche = 1;
    }
    else
    {
        laserdeux_proche = 0;
    }
    if(position_laser_trois>valeurlimite)
    {
        lasertrois_proche = 1;
    }
    else
    {
        lasertrois_proche = 0;
    }
    if(position_laser_quatre>valeurlimite)
    {
        laserquatre_proche = 1;
    }
    else
    {
        laserquatre_proche = 0;
    }
        ThisThread::sleep_for(1000ms);
    }
}

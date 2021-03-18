#include "herkulex_robos.h"

char angle=0;
Herkulex sv(D1,D0, 115200);
Thread thread_droit;
Thread thread_droite;
Thread thread_gauche;

void servo_init()
{
    sv.setTorque(1, TORQUE_ON);
    sv.setTorque(2, TORQUE_ON);
    sv.setTorque(3, TORQUE_ON);
    sv.setTorque(4, TORQUE_ON);
    thread_droit.start(&bras_droit);
    thread_droite.start(&bras_droite);
    thread_gauche.start(&bras_gauche);     
}

void bras_droit()
{
    while(1)
    {
        if(angle==0)
        {
            sv.positionControl(1, 370, 50, GLED_ON);                                      
            sv.positionControl(2, 950, 50, GLED_ON);
            sv.positionControl(3, 21, 50, GLED_ON);                                      
            sv.positionControl(4, 1000, 50, GLED_ON);
            angle=1;
        }
        ThisThread::sleep_for(3000);
    }   
}

void bras_droite()
{
    while(1)
    {
        if(angle==1)
        {
            sv.positionControl(1, 650, 50, GLED_ON);
            sv.positionControl(2, 950, 50, GLED_ON);
            sv.positionControl(3, 330, 50, GLED_ON);                                      
            sv.positionControl(4, 1000, 50, GLED_ON);
            angle=2;
        }
    ThisThread::sleep_for(3000);  
    }
}

void bras_gauche()
{
    while(1)
    {
    if(angle==2)
        {
            sv.positionControl(1, 350, 50, GLED_ON);
            sv.positionControl(2, 720, 50, GLED_ON);
            sv.positionControl(3, 50, 50, GLED_ON); 
            sv.positionControl(4, 21, 50, GLED_ON);
            angle=0;
        }
    ThisThread::sleep_for(3000);
    } 
}


#include "mbed.h"
#include "herkulex_robos.h"

DigitalOut led (LED2);

Thread thread_servo_init;
Thread thread_droit;
Thread thread_droite;
Thread thread_gauche;

int main() 
{       
    servo_init();
    thread_droit.start(&bras_droit);
    thread_droite.start(&bras_droite);
    thread_gauche.start(&bras_gauche);
    
    while(1) 
    {
   
        led=!led;
        ThisThread::sleep_for(2000);
      
    }
}


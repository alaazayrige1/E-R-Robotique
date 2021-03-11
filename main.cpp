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
    
    while(1) 
    {
   
        led=!led;
        ThisThread::sleep_for(2000);
      
    }
}


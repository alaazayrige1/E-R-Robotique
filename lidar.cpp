#include "Lidar.h"


// Declaration de la liaison série
UnbufferedSerial LidarSerialUn(PD_5, PD_6, 115200);
UnbufferedSerial LidarSerialDeux(PC_12, PD_2, 115200);

//UnbufferedSerial LidarSerialDeux(PC_10, PC_11, 115200);

T_msg msg;
T_scan fullScan;

// Déclaration de variables
char angle_un = 0;
char angle_deux = 0;
char numerolidar = 0;
unsigned char distxy[3] = {0,0,0};
DigitalOut LedB(LED2, 0);

// Déclaration de threads
Thread Thread_Stockage_Variable_Un;
//Thread Thread_Stockage_Variable_Deux;
Thread put_angle_un;
//Thread put_angle_deux;

// Déclaration flags
EventFlags flag_reception;
EventFlags flag_traitement;
EventFlags flag_reception_deux;
EventFlags flag_traitement_deux;
EventFlags flag_priority;
EventFlags flag_prioritydeux;


// main() runs in its own thread in the OS
void fonctionlidar()
{
    LidarSerialUn.format(8, SerialBase::None,1);
    LidarSerialDeux.format(8, SerialBase::None,1);
    flag_priority.set(1);

    while(1)
    {
        LedB = !LedB;
        ThisThread::sleep_for(1000ms);
    }
}

void put_angle_un_fct()
{
    while(1)
    {
    flag_reception.wait_all(1,osWaitForever,true);
        for(int i =0;i<87;i++)
        {
            if (fullScan.spot[i].intensite > 20 && fullScan.spot[i].strangeStrength == false && fullScan.spot[i].falseDistance == false && fullScan.spot[i].distance > 1)
            {
                angle_un = i;
                distxy[0] = cos((angle_un-43)*(3.14/180)) * fullScan.spot[i].distance;
                distxy[1] = sin((angle_un-43)*(3.14/180)) * fullScan.spot[i].distance;
                distxy[2] = angle_un;
            }
    
        }
        if(numerolidar == 1)
        {
            flag_priority.set(1);
        }
        if(numerolidar == 2)
        {
            flag_prioritydeux.set(1);
        }
        flag_priority.set(1);
        ThisThread::sleep_for(100ms);
    }
}

void Lidar_lecture_fct()
{
    flag_prioritydeux.wait_all(1,osWaitForever,true);
    static bool syncronized = false;
    static int index = 0;
    char value;
    numerolidar = 1;

    LidarSerial.read(&value, 1); //lecture de l'octet reçu
    if (syncronized) {
        msg.octet[index] = value;
        index++;
        if (index == 22) {
            index=0;
            flag_traitement.set(1);
            syncronized = false;
        }
    } else {
        if (value == 0xFA) {
            msg.octet[0]=value;
            index = 1;
            syncronized = true;
        }
    }
}

void Lidar_lecture_fct_deux()
{
    flag_priority.wait_all(1,osWaitForever,true);
    static bool syncronized = false;
    static int index = 0;
    char value;
    numerolidar = 2;

    LidarSerial.read(&value, 1); //lecture de l'octet reçu
    if (syncronized) {
        msg.octet[index] = value;
        index++;
        if (index == 22) {
            index=0;
            flag_traitement.set(1);
            syncronized = false;
        }
    } else {
        if (value == 0xFA) {
            msg.octet[0]=value;
            index = 1;
            syncronized = true;
        }
    }
}

void Fct_Stockage_Variable_Un()
{
    int spotIndex = 0;
    while(1)
    {
        flag_traitement.wait_all(1,osWaitForever,true);
        if (msg.trame.index == 0xBD)
        {
            spotIndex = 0;
            flag_reception.set(1);
        } /*else {
            if (spotIndex>=120){
                printf("%d\n",spotIndex);
            } else {*/
            //traitement de Data0
            fullScan.spot[spotIndex].angle = msg.trame.index - 0xA0;
            fullScan.spot[spotIndex].distance = (unsigned short)msg.trame.data0.oneSpot.byte0 + ((unsigned short)msg.trame.data0.oneSpot.byte1.upperDistance << 8);
            fullScan.spot[spotIndex].intensite = (unsigned short)msg.trame.data0.oneSpot.byte2 + ((unsigned short)msg.trame.data0.oneSpot.byte3 << 8);
            fullScan.spot[spotIndex].falseDistance = (bool)msg.trame.data0.oneSpot.byte1.flag0;
            fullScan.spot[spotIndex].strangeStrength = (bool)msg.trame.data0.oneSpot.byte1.flag1;
            //traitement de Data1
            fullScan.spot[spotIndex+1].angle = msg.trame.index - 0xA0 + 1;
            fullScan.spot[spotIndex+1].distance = (unsigned short)msg.trame.data1.oneSpot.byte0 + ((unsigned short)msg.trame.data1.oneSpot.byte1.upperDistance << 8);
            fullScan.spot[spotIndex+1].intensite = (unsigned short)msg.trame.data1.oneSpot.byte2 + ((unsigned short)msg.trame.data1.oneSpot.byte3 << 8);
            fullScan.spot[spotIndex+1].falseDistance = (bool)msg.trame.data1.oneSpot.byte1.flag0;
            fullScan.spot[spotIndex+1].strangeStrength = (bool)msg.trame.data1.oneSpot.byte1.flag1;
            //traitement de Data2
            fullScan.spot[spotIndex+2].angle = msg.trame.index - 0xA0 + 2;
            fullScan.spot[spotIndex+2].distance = (unsigned short)msg.trame.data2.oneSpot.byte0 + ((unsigned short)msg.trame.data2.oneSpot.byte1.upperDistance << 8);
            fullScan.spot[spotIndex+2].intensite = (unsigned short)msg.trame.data2.oneSpot.byte2 + ((unsigned short)msg.trame.data2.oneSpot.byte3 << 8);
            fullScan.spot[spotIndex+2].falseDistance = (bool)msg.trame.data2.oneSpot.byte1.flag0;
            fullScan.spot[spotIndex+2].strangeStrength = (bool)msg.trame.data2.oneSpot.byte1.flag1;
            //traitement de Data3
            fullScan.spot[spotIndex+3].angle = msg.trame.index - 0xA0 + 3;
            fullScan.spot[spotIndex+3].distance = (unsigned short)msg.trame.data3.oneSpot.byte0 + ((unsigned short)msg.trame.data3.oneSpot.byte1.upperDistance << 8);
            fullScan.spot[spotIndex+3].intensite = (unsigned short)msg.trame.data3.oneSpot.byte2 + ((unsigned short)msg.trame.data3.oneSpot.byte3 << 8);
            fullScan.spot[spotIndex+3].falseDistance = (bool)msg.trame.data3.oneSpot.byte1.flag0;
            fullScan.spot[spotIndex+3].strangeStrength = (bool)msg.trame.data3.oneSpot.byte1.flag1;
            //}
            spotIndex = spotIndex + 4;
        //}
    }
}

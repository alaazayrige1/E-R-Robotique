# Code de la PIXY

## main.cpp

```c
#include "pixy2.h"
#include <cstdio>

#define calibrate 0
#define calDistance 610
#define debug 0

 int numblocks, oldnumblocks = 0, i = 0, index, counter = 10;
 float dataBlocks[255][6];
 int calWidth = 28, calHeight = 26;
 int avg[2]; 

 UnbufferedSerial pc(USBTX, USBRX,57600); 
 PIXY2 pixy(PD_5, PD_6,230400);
 T_pixy2ErrorCode cr;
 
 int calibrateW (){ 
        int sumW, avgW;
        //printf("width\n");

        while (i < counter)
        {
            do { 
                cr = pixy.pixy2_getBlocks(1, 255);               
            } while (cr != PIXY2_OK);

            int w = 0;
            w = pixy.Pixy2_blocks[0].pixWidth;
            sumW += w;

            printf("%d\n",w);
            i++;

            ThisThread::sleep_for(1s);
        } 
        avgW = sumW/10;
        i = 0;

        if (debug){
            printf("avgW: %d\n",avgW);
        }
        return avgW;
 }

 int calibrateH (){ 

        int sumH, avgH;
        //printf("height\n");

        while (i < counter)
        {
            do { 
                cr = pixy.pixy2_getBlocks(1, 255);               
            } while (cr != PIXY2_OK);

            int h = 0;
            
            h = pixy.Pixy2_blocks[0].pixHeight;

            sumH += h;

            printf("%d\n",h);
            i++;

            ThisThread::sleep_for(1s);
        }
        
        avgH = sumH/10;
        i = 0;

        if (debug){
            printf("avrgH: %d\n",avgH);
        }
        return avgH;
 }


 int calculateDistance(int x,int y){

    int curWidth, curHeight;
    int ow = 65, oh = 65;               
    int distWidth, distHeight;
    int flw, flh;
    int avg;
    int dist;


    flw = (calWidth * calDistance) / ow;
    flh = (calHeight * calDistance) / oh;

    // do { 
    //     cr = pixy.pixy2_getBlocks(1, 255);               
    // } while (cr != PIXY2_OK);

    // curWidth = pixy.Pixy2_blocks[0].pixWidth;
    // curHeight = pixy.Pixy2_blocks[0].pixHeight;
    
    curWidth = x;
    curHeight = y;
```

#ifndef LIDAR_H
#define LIDAR_H


#include "Robot_total.h"

extern UnbufferedSerial LidarSerial;

// Déclaration type structuré
typedef struct {
    char flag0 : 1;
    char flag1 : 1;
    char upperDistance : 6;
} T_byte1;

typedef struct {
    char byte0;
    T_byte1 byte1;
    char byte2;
    char byte3;
} T_data;

typedef union {
    long word;
    char octet[4];
    T_data oneSpot;
}T_dataWord;

typedef struct {
    char start;
    char index;
    short retain;
    T_dataWord data0;
    T_dataWord data1;
    T_dataWord data2;
    T_dataWord data3;
    short checksum;
} T_trame;

typedef union {
    T_trame trame;
    char octet[22];
} T_msg;

typedef struct {
    unsigned char angle;
    unsigned short distance;
    unsigned short intensite;
    bool falseDistance;
    bool strangeStrength;
} T_spot;

typedef struct {
    T_spot spot[120];
} T_scan;

extern T_msg msg;
extern T_scan fullScan;
// Déclaration de variables
extern char angle_un;
extern char angle_deux;
extern char numerolidar;
extern int spotIndex;
extern unsigned char distxy[3];
extern DigitalOut LedB;

// Déclaration de threads
extern Thread Thread_Stockage_Variable_Un;
//Thread Thread_Stockage_Variable_Deux;
extern Thread put_angle_un;
//Thread put_angle_deux;

// Déclaration flags
extern EventFlags flag_reception;
extern EventFlags flag_traitement;
extern EventFlags flag_reception_deux;
extern EventFlags flag_traitement_deux;

// Déclaration des fonctions
void Lidar_lecture_fct();
void Lidar_lecture_fct_deux();
void put_angle_un_fct();
//void put_angle_deux_fct();
void Fct_Stockage_Variable_Un();
//void Fct_Stockage_Variable_Deux();
#endif

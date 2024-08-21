#include <Wire.h>
//*********************************************| Barometer Setup |***********************************************
uint16_t dig_T1, dig_P1;
int16_t  dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5;  //dig_T# for temperature compensation   
int16_t  dig_P6, dig_P7, dig_P8, dig_P9;                  //dig_P# for pressure compensation 
int RateCalibrationNumber; 
float AltitudeBarometerStartUp;
unsigned long int p; 
signed long int var1, var2;
double pressure;

//******************************************| Optical flow and lidar |********************************************
bool readcomplete = false; 
int32_t arr[18] = {}, arr1[18] = {};


//**************************************************| GPS |*******************************************************
String code;

int j=1; // biến lưu vị trí ban đầu

String nmea[8];   //GNGLL
String nmea0[15]; //GNGGA
String nmea2[15]; //GNRMC
String nmea4[15]; //GNVTG

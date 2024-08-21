void setup()                              
{
  Serial.begin(9600);
  Serial3.begin(115200);  // OP-lidar
  Serial1.begin(115200);  // GPS
  Serial2.begin(9600);
  Wire.setClock(400000);  // BMP
  Wire.begin();                  

  Wire.beginTransmission(0x76);
  Wire.write(0xF4);                          
  Wire.write(0x57);                          
  Wire.endTransmission();   

  Wire.beginTransmission(0x76);
  Wire.write(0xF5);                         
  Wire.write(0x14);
  Wire.endTransmission();   

  uint8_t data[24], i=0; 
  Wire.beginTransmission(0x76);
  Wire.write(0x88);
  Wire.endTransmission();
  Wire.requestFrom(0x76,24);      

  while(Wire.available())   
  {
    data[i] = Wire.read();
    i++;
  }
  dig_T1 = (data[1] << 8) | data[0]; 
  dig_T2 = (data[3] << 8) | data[2];
  dig_T3 = (data[5] << 8) | data[4];
  dig_P1 = (data[7] << 8) | data[6]; 
  dig_P2 = (data[9] << 8) | data[8];
  dig_P3 = (data[11]<< 8) | data[10];
  dig_P4 = (data[13]<< 8) | data[12];
  dig_P5 = (data[15]<< 8) | data[14];
  dig_P6 = (data[17]<< 8) | data[16];
  dig_P7 = (data[19]<< 8) | data[18];
  dig_P8 = (data[21]<< 8) | data[20];
  dig_P9 = (data[23]<< 8) | data[22]; 

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  float AltitudeBarometer;
  for (RateCalibrationNumber=0; RateCalibrationNumber<10; RateCalibrationNumber ++) 
  {
    BMP_signals(&AltitudeBarometer);
    AltitudeBarometerStartUp+=AltitudeBarometer;
  }
  AltitudeBarometerStartUp/=10;  

  Serial.println("********************Setting up completely *********************");
}
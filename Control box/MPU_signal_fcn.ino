void mpu_signal(struct mpu *accr)
{
  float RRoll,RPitch,RYaw;
  Wire.beginTransmission(address_MPU); 
  Wire.write(0x1A); 
  Wire.write(0x01); 
  Wire.endTransmission(); 

  Wire.beginTransmission(address_MPU);
  Wire.write(0x1C); 
  Wire.write(0x10);
  Wire.endTransmission();

  Wire.beginTransmission(address_MPU);
  Wire.write(0x3B);               
  Wire.endTransmission();
  Wire.requestFrom(0x68,6); 
  int16_t AccXLSB = Wire.read()<<8 | Wire.read();
  int16_t AccYLSB = Wire.read()<<8 | Wire.read();
  int16_t AccZLSB = Wire.read()<<8 | Wire.read();

  Wire.beginTransmission(address_MPU);
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();
  Wire.beginTransmission(address_MPU);
  Wire.write(0x43);                 
  Wire.endTransmission();

  Wire.requestFrom(address_MPU,6);
  int16_t GyroX = Wire.read()<<8 | Wire.read();
  int16_t GyroY = Wire.read()<<8 | Wire.read();
  int16_t GyroZ = Wire.read()<<8 | Wire.read();

  if(clib.sign==1){
    RRoll = (float)GyroX/65.5 - clib.CalibRoll;
    RPitch = (float)GyroY/65.5 - clib.CalibPitch;
    RYaw = (float)GyroZ/65.5- clib.CalibYaw; 
  } else {
    RRoll = (float)GyroX/65.5;
    RPitch = (float)GyroY/65.5;
    RYaw = (float)GyroZ/65.5;  
  }

  float AX = (float)AccXLSB/4096-0.0425;
  float AY = (float)AccYLSB/4096-0.02;
  float AZ = (float)AccZLSB/4096;

  (*accr).AccX=AX; (*accr).AccY=AY; (*accr).AccZ=AZ;
  (*accr).RateRoll=RRoll;  (*accr).RatePitch=RPitch;  (*accr).RateYaw=RYaw;
}
void setup()                             
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);                        
  
  Wire.beginTransmission(address_HMC);
  Wire.write(0x02); 
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(address_MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  mpu_calib();

  Serial.println(" *********** Setting completely *********** ");
}

void mpu_calib()
{
  struct mpu mpucb;
  for (int RateCalibrationNumber=0; RateCalibrationNumber<100; RateCalibrationNumber ++) 
  {
    mpu_signal(&mpucb);
    clib.CalibRoll  +=  mpucb.RateRoll;
    clib.CalibPitch +=  mpucb.RatePitch;
    clib.CalibYaw   +=  mpucb.RateYaw;
  }
  clib.CalibRoll/=100; clib.CalibPitch/=100; clib.CalibYaw/=100; 
  clib.sign=1;
}
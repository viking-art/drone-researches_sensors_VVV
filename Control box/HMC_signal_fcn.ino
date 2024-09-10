#define dt 0.0067
void HMC_signal(struct laban *hmc, float rateY)
{
  int x,y,z;
  static float hard_cal[3];

  Wire.beginTransmission(address_HMC);
  Wire.write(0x03); 
  Wire.endTransmission();

  Wire.requestFrom(address_HMC, 6);
  if(6<=Wire.available())
  {
    x = Wire.read()<<8;   x |= Wire.read(); 
    z = Wire.read()<<8;   z |= Wire.read(); 
    y = Wire.read()<<8;   y |= Wire.read();
  }

  float mag_data[]={x, y, z};
  const float hard_iron[3] = {16.914333, -56.111788, -13.237758};
  const float soft_iron[3][3] = {
  {0.141144 , 0.011396, -0.000020},
  {0.011396 , 0.146821, 0.006380},
  {-0.000020, 0.006380, 0.169585},};

  for (uint8_t i = 0; i < 3; i++)   hard_cal[i] = mag_data[i] - hard_iron [i];
  for (uint8_t i = 0; i < 3; i++) {
  mag_data[i] = (soft_iron[i][0] * hard_cal [0]) + 
                (soft_iron[i][1] * hard_cal [1]) +
                (soft_iron[i][2] * hard_cal [2]); 
  }
  mag_data[1]+=12;
  if(mag_data[0]<0 && mag_data[0]<0) {mag_data[1]+=50;}

  float heading_true = atan2(mag_data[1], mag_data[0]);
  float heading = heading_true;

  if(heading < 0)     heading = heading+ 2*PI;
  if(heading > 2*PI)  heading = heading - 2*PI;
  if(heading_true < 0)     heading_true = heading_true+ 2*PI;
  if(heading_true > 2*PI)  heading_true = heading_true - 2*PI;
  
  heading = heading * 180 / M_PI; 
  heading_true = heading_true * 180 / M_PI; 

  (*hmc).true_north = heading_true; 
  (*hmc).heading = heading;
}
  
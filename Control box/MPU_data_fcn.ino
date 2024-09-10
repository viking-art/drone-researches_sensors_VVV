#define dt 0.0275
void mpu_data(struct mpu raw, struct rpyGyro *gyro,struct rpyAcc *rpyacc)
{
  float gyroll = (*gyro).Grroll;   float gypitch = (*gyro).Grpitch;   float gyyaw = (*gyro).Gryaw; 
  float RateRoll  = raw.RateRoll; 
  float RatePitch = raw.RatePitch; 
  float RateYaw   = raw.RateYaw;
  float AccX = raw.AccX;   float AccY = raw.AccY;   float AccZ = raw.AccZ;

  float Acc_angleroll  = atan(AccY/sqrt(AccX*AccX + AccZ*AccZ)) * 1/(3.142/180) - 0.5; 
  float Acc_anglepitch = atan(-AccX/sqrt(AccY*AccY + AccZ*AccZ)) * 1/(3.142/180) + 0.9;
  gyroll  += RateRoll*dt;
  gypitch += RatePitch*dt;
  gyyaw   += RateYaw*dt; 

  (*rpyacc).Aroll  = Acc_angleroll; 
  (*rpyacc).Apitch = Acc_anglepitch;
  (*gyro).Grroll = gyroll;
  (*gyro).Grpitch = gypitch;
  (*gyro).Gryaw = gyyaw;
}

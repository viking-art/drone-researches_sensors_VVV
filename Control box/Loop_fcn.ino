unsigned long Ms,m;
int loopx;
void loop()
{
  struct mpu mpuraw;  
  struct rpyGyro rpyG;    struct rpyAcc rpyA;
  struct kalman1D kal1d;  struct kalman2D kal2d;
  struct laban hmc;

  // ************************************* MPU ****************************************
  mpu_signal(&mpuraw);
  mpu_data(mpuraw,&rpyG,&rpyA);

  // ************************************* HMC ****************************************
  HMC_signal(&hmc,mpuraw.RateYaw);

  // ******************************** Kalman Filter ***********************************
  kalman_filter_1D(mpuraw,rpyA,hmc,&kal1d);
  kalman_filter_2D(mpuraw,rpyA,hmc,&kal2d);

  // ********************************** Print Data ************************************
  // Serial.print("AccX:");   Serial.print(mpuraw.AccX);  
  // Serial.print(" AccY:");  Serial.print(mpuraw.AccY);  
  // Serial.print(" AccZ:");  Serial.println(mpuraw.AccZ);

  // Serial.print("AccX:");    Serial.print(rpyA.Aroll);  
  // Serial.print(" kalX1:");  Serial.print(kal1d.kroll);  
  // Serial.print(" kalX2:");  Serial.println(kal2d.xrk);  

  // Serial.print("AccX:");    Serial.print(rpyA.Apitch);  
  // Serial.print(" kalY1:");   Serial.print(kal1d.kpitch);  
  // Serial.print(" kalY2:");  Serial.println(kal2d.xpk);  

  // Serial.print("h:");   Serial.println(hmc.heading);
  // Serial.print(" kalZ1:");   Serial.print(kal1d.kyaw);  
  // Serial.print(" kalZ2:");  Serial.println(kal2d.xyk);  
}




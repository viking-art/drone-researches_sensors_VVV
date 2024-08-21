float premlat; float premlong;
void convert_to_met(float llat, float llong, float inilat, float inilong ,float *mlat, float *mlong)
{
  const float heso = 74074.07407;

  float MTB1, MTB2, r1, r2;
  MTB1 = (llat - inilat)*heso;      r1 = abs(MTB1)-abs(premlat); 
  MTB2 = (llong - inilong)*heso;    r2 = abs(MTB2)-abs(premlong); 

  // Serial.print(inilat); Serial.print(" "); Serial.println(llat);

  if(r1<=0.1) { *mlat = MTB1; }
  if(r2<=0.1) { *mlong = MTB2;}

  premlat=MTB1; premlong=MTB2;
}

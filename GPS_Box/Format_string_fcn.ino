const unsigned long limit_1 = 100,limit_2=5000; 
unsigned long preMillis = 0,preM = 0;    

void formatString(float xgps, float ygps, int lidar, float alt, float vfx, float vfy, float vgps, bool qual,unsigned long timer, float ilat, float ilong)
{
  char buffer_v[30], buffer_p[30];
  int x   = xgps*100;
  int y   = ygps*100;
  int vtg = (int)(vgps*27.78);
  int vx  = (int)(vfx*27.78);
  int vy  = (int)(vfy*27.78);
  int zp  = (int)(alt);
  int zf  = lidar/10;

  if(qual==1) 
  sprintf(buffer_v,"*OFL,%d,%d,%d,%d,%d,%d,%d,A,",x,y,zf,zp,vx,vy,vtg);
  else sprintf(buffer_v,"*OFL,%d,%d,%d,%d,%d,%d,%d,N,",x,y,zf,zp,vx,vy,vtg);

  int checksum1 = 0;
  for (int i = 0; i < strlen(buffer_v); i++)  checksum1 += buffer_v[i];
  checksum1 = checksum1 % 256;
  sprintf(buffer_v + strlen(buffer_v), "%02X#", checksum1);

  int inilat  = ilat;
  int inilong  = ilong;
  sprintf(buffer_p,"*%d,%d,",inilat,inilong);

  int checksum2 = 0;
  for (int i = 0; i < strlen(buffer_p); i++)  checksum2 += buffer_p[i];
  checksum2 = checksum2 % 256;
  sprintf(buffer_p + strlen(buffer_p), "%02X#", checksum2);

  if(Serial2.availableForWrite()>=63)
  {
    if (timer - preMillis >= limit_1) 
    {
      preMillis = timer;
      Serial.println(buffer_v);
      Serial2.println(buffer_v);
    }
    if (timer - preM >= limit_2) 
    {
    preM = timer;
      Serial.println(buffer_p);
      Serial2.println(buffer_p);
    }
  }
}

  

bool p1,p2,p3,p4;
float vtgps,cog,llat,llong;
float inilat,inilong; float MTB1,MTB2;

void GPS_read()
{ 
  if(Serial1.available()>0)   
  {
    code = Serial1.readStringUntil('\n');     
    // Serial.println(code);
  }
  p1=0;p2=0;p3=0;p4=0;
}

void GPS_data(float *xgps, float *ygps, float *vtg,float *ini_lat,float *ini_long)
{
  if(code.startsWith("$GNGGA,")) { neogngga2(); p2=true;}
  if(code.startsWith("$GNGLL,")) { neogngll2(); p3=true;}
  if(code.startsWith("$GNVTG,")) { neognvtg2(); p4=true;}
  if(code.startsWith("$GNRMC,")) { neognrmc2(); p1=true;}

  trans_float(&vtgps,&cog,&llat,&llong);
  ini_pos(llat,llong,&inilat,&inilong);
  convert_to_met(llat,llong,inilat,inilong,&MTB1,&MTB2);

  *xgps = MTB1; *ygps = MTB2; *vtg = vtgps;
  *ini_lat = inilat;*ini_long = inilong;
}

bool checksignal_GPS()
{
  if(p1==1 || p2==1 || p3==1 || p4==1 ) { return 1;}
  else {return 0;}
}

void neogngll2()
{
  int stringplace = 0, pos = 0;
  for (int i = 0; i < code.length(); i++) {

    if (code.substring(i, i + 1) == ",") {        // tìm dấu phẩy trên mảng chuỗi, tìm được thì thực hiện lệnh trong if
      nmea[pos] = code.substring(stringplace, i); // lấy mã từ bắt đầu từ chỉ số stringplace cho đến chỉ số i, loại bỏ kí tự ở chỉ số i
      stringplace = i + 1;                        // chỉ số stringplace sẽ là chỉ số của i hiện tại + 1
      pos++;                                      // cho chỉ số của mảng nmea dịch sang chuỗi tiếp theo
    }                                             // ở mảng nmea, mỗi chuỗi nằm giữa 2 dấu phẩy xem như là 1 địa chỉ tương ứng với 1 chỉ số
    else if (i == code.length() - 1) {
      nmea[pos] = code.substring(stringplace, i);
    }
  }
  nmea[1] = convertlat();
  nmea[3] = convertlog();
}

void neogngga2()
{
  int stringplace1 = 0, pos1 = 0;
  for (int i1 = 0; i1 < code.length(); i1++) {
    if (code.substring(i1, i1 + 1) == ",") {        
      nmea0[pos1] = code.substring(stringplace1, i1); 
      stringplace1 = i1 + 1;                       
      pos1++;                                      
    }                                             
    else if (i1 == code.length() - 1) {
      nmea0[pos1] = code.substring(stringplace1, i1);
    }
  }
  nmea0[2] = convertlat1();
  nmea0[4] = convertlog1();
}

void neognrmc2()
{
  int stringplace2 = 0, pos2 = 0;
  for (int i2 = 0; i2 < code.length(); i2++) {
    if (code.substring(i2, i2 + 1) == ",") {   
      nmea2[pos2] = code.substring(stringplace2, i2); 
      stringplace2 = i2 + 1;                       
      pos2++;                                      
    }
    else if (i2 == code.length() - 1) {
      nmea2[pos2] = code.substring(stringplace2, i2);
    }

  }
  nmea2[3] = convertlat2();
  nmea2[5] = convertlog2();
}

void neognvtg2()
{
  int stringplace3 = 0, pos3 = 0;
  for (int i3 = 0; i3 < code.length(); i3++) {
    if (code.substring(i3, i3 + 1) == ",") {        
      nmea4[pos3] = code.substring(stringplace3, i3); 
      stringplace3 = i3 + 1;                       
      pos3++;                                      
    }                                             
    else if (i3 == code.length() - 1) {
      nmea4[pos3] = code.substring(stringplace3, i3);
    }
  }
}

/*****************************lấy latitude của GNGLL theo độ***************************************/
String convertlat()
{
  String dlat;
  float  mlat;
  for (int i = 0; i < nmea[1].length(); i++) {
    if (nmea[1].substring(i, i + 1) == ".") {
      dlat = nmea[1].substring(0, i - 2);
      mlat = nmea[1].substring(i - 2).toFloat(); // dd.mm...
    }
  }
  mlat = mlat/60;
  String CalcLat = "";

  char charVal[9];
  dtostrf(mlat, 4, 6, charVal);
  for (int i = 0; i < sizeof(charVal); i++)
  {
    CalcLat += charVal[i];
  }
  dlat += CalcLat.substring(1);
  return dlat;
}
/*****************************lấy longitude của GNGLL theo độ***************************************/
String convertlog()
{
  String dlog;
  float  mlog;
  for (int i = 0; i < nmea[3].length(); i++) {
    if (nmea[3].substring(i, i + 1) == ".") {
      dlog = nmea[3].substring(0, i - 2);
      mlog = nmea[3].substring(i - 2).toFloat(); // dd.mm...
    }
  }
  mlog = mlog/60;
  String CalcLat = "";

  char charVal[9];
  dtostrf(mlog, 4, 6, charVal);
  for (int i = 0; i < sizeof(charVal); i++)
  {
    CalcLat += charVal[i];
  }
  dlog += CalcLat.substring(1);
  return dlog;
}
/*********************************lấy latitude của GPGGA theo độ***************************************/
String convertlat1()
{
  String dlat1;
  float  mlat1;
  for (int i1 = 0; i1 < nmea0[2].length(); i1++) {
    if (nmea0[2].substring(i1, i1 + 1) == ".") {
      dlat1 = nmea0[2].substring(0, i1 - 2);
      mlat1 = nmea0[2].substring(i1 - 2).toFloat(); // dd.mm...
      }
  }
  mlat1 = mlat1/60;
  String CalcLat1 = "";

  char charVal1[9];
  dtostrf(mlat1, 4, 6, charVal1);
  for (int i1 = 0; i1 < sizeof(charVal1); i1++)
  {
    CalcLat1 += charVal1[i1];
  }
  dlat1 += CalcLat1.substring(1);
  return dlat1;
}
/*********************************lấy longitude của GPGGA theo độ***************************************/
String convertlog1()
{
  String dlog1;
  float  mlog1;
  for (int i1 = 0; i1 < nmea0[4].length(); i1++) {
    if (nmea0[4].substring(i1, i1 + 1) == ".") {
      dlog1 = nmea0[4].substring(0, i1 - 2);
      mlog1 = nmea0[4].substring(i1 - 2).toFloat(); // dd.mm...
    }
  }
  mlog1 = mlog1/60;
  String CalcLat1 = "";

  char charVal1[9];
  dtostrf(mlog1, 4, 6, charVal1);
  for (int i1 = 0; i1 < sizeof(charVal1); i1++)
  {
    CalcLat1 += charVal1[i1];
  }
  dlog1 += CalcLat1.substring(1);
  return dlog1;
}
/*********************************lấy latitude của GPRMC theo độ***************************************/
String convertlat2()
{
  String dlat2;
  float  mlat2;
  for (int i2 = 0; i2 < nmea2[3].length(); i2++) {
    if (nmea2[3].substring(i2, i2 + 1) == ".") {
      dlat2 = nmea2[3].substring(0, i2 - 2);
      mlat2 = nmea2[3].substring(i2 - 2).toFloat(); // dd.mm...
    }
  }
  mlat2 = mlat2/60;
  String CalcLat2 = "";

  char charVal2[9];
  dtostrf(mlat2, 4, 6, charVal2);
  for (int i2 = 0; i2 < sizeof(charVal2); i2++)
  {
    CalcLat2 += charVal2[i2];
  }
  dlat2 += CalcLat2.substring(1);
  return dlat2;
}
/*********************************lấy latitude của GPRMC theo độ***************************************/
String convertlog2()
{
  String dlog2;
  float  mlog2;
  for (int i2 = 0; i2 < nmea2[5].length(); i2++) {
    if (nmea2[5].substring(i2, i2 + 1) == ".") {
      dlog2 = nmea2[5].substring(0, i2 - 2);
      mlog2 = nmea2[5].substring(i2 - 2).toFloat(); // dd.mm...
    }
  }
  mlog2 = mlog2/60;
  String CalcLat2 = "";

  char charVal2[9];
  dtostrf(mlog2, 4, 6, charVal2);
  for (int i2 = 0; i2 < sizeof(charVal2); i2++)
  {
    CalcLat2 += charVal2[i2];
  }
  dlog2 += CalcLat2.substring(1);
  return dlog2;
}

void trans_float(float *vgps,float *c,float *gpslat,float *gpslong)
{
  float save1,save2,save3,save4,save5,save6,vtg,cog,llat,llong;

  if(nmea[6]=="A")    {save1 = nmea[1].toFloat();   save2 = nmea[3].toFloat();}
  if(nmea0[6]=="1")   {save4 = nmea0[4].toFloat();  save3 = nmea0[2].toFloat();}
  if(nmea4[6]=="N")   {vtg = nmea4[7].toFloat();    cog = nmea4[1].toFloat();}

  llat = (save3 + save1)/2;
  llong = (save4 + save2)/2;
  // Serial.print(llat); Serial.print(" "); Serial.println(llong);
  
  *vgps=vtg;  *c=cog;  *gpslat=llat;  *gpslong=llong;
}

void ini_pos(float llat, float llong, float *ini_lat, float *ini_long)
{
  if (j>=1)
  {
    j++;
    float inilat,inilong;
    inilat = llat; inilong = llong;
    *ini_lat=inilat; *ini_long=inilong;
    if (inilat !=0 && inilong !=0 && j>=100) j=0;
  }
}

float premlat; float premlong;
void convert_to_met(float llat, float llong, float inilat, float inilong ,float *mlat, float *mlong)
{
  const float heso = 74074.07407;

  float MTB1, MTB2, r1, r2;
  MTB1 = (llat - inilat)*heso;      r1 = abs(MTB1)-abs(premlat); 
  MTB2 = (llong - inilong)*heso;    r2 = abs(MTB2)-abs(premlong); 

  // Serial.print(inilat); Serial.print(" "); Serial.println(llat);

  if(r1<=0.1) { *mlat = MTB1*100; }
  if(r2<=0.1) { *mlong = MTB2*100;}

  premlat=MTB1; premlong=MTB2;
}


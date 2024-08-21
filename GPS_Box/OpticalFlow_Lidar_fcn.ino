byte a1,b1,g;  
int z; float vx,vy; 
bool check=false;

void OpticalFlow_Lidar_read()
{ 
  while (Serial3.available()>0) 
  {
    uint8_t byteReceived = Serial3.read();     
    if(byteReceived==0x24) g++;
    if(g==1)      {arr[a1]=byteReceived;     a1++;}
    if(g==2)      {arr1[b1]=byteReceived;    b1++;}
    if(g==3)      readcomplete = true;  
  }
}

void OpticalFlow_Lidar_data(int *zf, float *vfx, float *vfy)
{
  if(readcomplete==true)
  {
    OpticalFlow_Lidar_process(&vx,&vy,&z,&check);

    // Serial.print("z:");    Serial.println(z);
    // Serial.print("vx:");   Serial.println(vx);   
    // Serial.print("vy:");   Serial.println(vy);
    *zf=z; *vfx=vx; *vfy=vy;
    Resetarray();
  }
}

void Resetarray()
{
  memset(arr,0x00, sizeof(arr));
  memset(arr1,0x00, sizeof(arr1));
  g=0; a1=0; b1=0; readcomplete=false;
}

bool checksignal_OFlidar()
{
  if(check==1) {return 1;  check=0;}
  else {return 0;}
}
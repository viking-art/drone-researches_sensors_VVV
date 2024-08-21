#define fov_degrees  42           // FOV of the sensor in degrees
#define image_width_pixels  800   // Image width in pixels
#define dt  0.075

void OpticalFlow_Lidar_process(float *vfx, float *vfy, int *zf, bool *check)
{ 
  float vxp, vyp; 
  long dx1,dx2; long dy1,dy2; int d1,d2,dis;
  bool c=false,c1=false,c2=false;
  OptiLida(arr[17],arr[6],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14],arr[15],arr[16],&c1,&dx1,&dy1,&d1);
  OptiLida1(arr[17],arr[6],arr[9],arr[10],arr[11],arr[12],arr[13],arr[14],arr[15],arr[16],&c2,&dx2,&dy2,&d2);

  long dx=(dx1+dx2)/2;  
  long dy=(dy1+dy2)/2;   
  dis=(d1+d2)/2;

  OpticalFlow_Vel_transfer(dx,dy,dis,&vxp,&vyp);
  *vfx=vxp; *vfy=vyp; *zf= dis;
  if(c1==1 && c2==1) c=true;
  *check=c;
}

void OptiLida(uint8_t byte17, uint8_t byte6, uint8_t byte9, uint8_t byte10, uint8_t byte11,uint8_t byte12, uint8_t byte13,uint8_t byte14,uint8_t byte15,uint8_t byte16,bool *c1,long *dx1,long *dy1,int *d1)
{
  int16_t D;  
  long flowX ;  long flowY;   
  bool lidar,flow,check;
  if(byte13 != 0x00 && byte6 == 0x05)      
  {
    D = byte9;  D<<= 8;   D += byte10;    D = (D & 0xFF00) >> 8 | (D & 0x00FF) << 8; lidar=true;
  }
  if(lidar=true)  {if(D>=2000)  {D=2000;}   *d1=D;}

  if (byte17 != 0x00 || byte6 == 0x09)     
  {
    flowX=0; flowY=0;
    flowX |= byte12; 
    flowX = flowX <<8;    flowX |= byte11; 
    flowX = flowX <<8;    flowX |= byte9; 
    flowX = flowX <<8;    flowX |= byte10; 

    flowY += byte15; 
    flowY = flowY <<8;   flowY += byte16; 
    flowY = flowY <<8;   flowY += byte13;
    flowY = flowY <<8;   flowY += byte14; 
    flow = true;  
  }
  if(flow=true) { *dx1=flowX; *dy1=flowY;}
  if(flow==true || lidar==true) check=true;
  *c1=check;
}

void OptiLida1(uint8_t byte17, uint8_t byte6, uint8_t byte9, uint8_t byte10, uint8_t byte11,uint8_t byte12, uint8_t byte13,uint8_t byte14,uint8_t byte15,uint8_t byte16,bool *c2,long *dx2,long *dy2,int *d2)
{
  int16_t D,G;  
  int32_t flowX ;  int32_t flowY;   
  bool lidar,flow,check;
  if(byte13 != 0x00 && byte6 == 0x05)      
  {
    D = byte9;  D<<= 8;   D += byte10;    D = (D & 0xFF00) >> 8 | (D & 0x00FF) << 8; lidar=true;
  }
  if(lidar==true)  {if(D>=2000)  {D=2000;}   *d2=D;}

  if (byte17 != 0x00 || byte6 == 0x09)     
  {
    flowX=0; flowY=0;
    flowX |= byte12; 
    flowX = flowX <<8;    flowX |= byte11; 
    flowX = flowX <<8;    flowX |= byte9; 
    flowX = flowX <<8;    flowX |= byte10; 

    flowY += byte15; 
    flowY = flowY <<8;   flowY += byte16; 
    flowY = flowY <<8;   flowY += byte13;
    flowY = flowY <<8;   flowY += byte14; 
    flow = true;  
  }
  if(flow==true) { *dx2=flowX; *dy2=flowY;}
  if(flow==true || lidar==true) check=true;
  *c2=check;
}

void OpticalFlow_Vel_transfer(int dx, int dy, float alt, float *vfx, float *vfy) 
{   
  alt/=1000;    // meters
  float fov_radians = (fov_degrees) * PI / 180;                     // Convert FOV to radians
  float fov_width_meters = 2 * alt * dt * tan(fov_radians / 2);     // Calculate FOV width in meters
  float scale_factor = fov_width_meters / image_width_pixels;       // Calculate scale factor

  float vx = dx * scale_factor*3.6;      
  float vy = dy * scale_factor*3.6;     
  *vfx=vx; *vfy=vy; 
}
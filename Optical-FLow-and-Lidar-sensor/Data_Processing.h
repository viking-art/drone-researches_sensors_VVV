void OptiLida(uint8_t byte17, uint8_t byte6, uint8_t byte9, uint8_t byte10, uint8_t byte11,uint8_t byte12, uint8_t byte13,uint8_t byte14,uint8_t byte15,uint8_t byte16)
{
  int16_t D;  
  long flowX ;  long flowY;   
  bool lidar = false;   
  bool flow = false;
  if(byte13 != 0x00 && byte6 == 0x05)      
  {
    D = byte9;  D<<= 8;   D += byte10;    D = (D & 0xFF00) >> 8 | (D & 0x00FF) << 8; lidar=true;
  }
  if(lidar=true)  {if(D>=(distance+2000))  {D=distance;}   d1=D;  lidar=false;}

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
  if(flow=true) { dx1=flowX; dy1=flowY; flow=false;}
}

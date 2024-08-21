bool quality;
unsigned long currentMillis;
float xgps,ygps,vtg,ilat,ilong;
float zp,alt; int zf; float vfx,vfy; 


void loop() 
{     
  currentMillis = millis();
  // ************************************* BMP ****************************************
  BMP_signals(&alt);  
  BMP_data(&zp,alt); 

  // ************************************* GPS ****************************************
  GPS_read();
  GPS_data(&xgps,&ygps,&vtg,&ilat,&ilong);

  // ****************************** OpticalFlow&Lidar *********************************
  OpticalFlow_Lidar_read();
  OpticalFlow_Lidar_data(&zf,&vfx,&vfy);

  // ******************************** Signal_Quality **********************************
  // Signal_quality(currentMillis,&quality);

  // ********************************* Transfer_Data **********************************
  // formatString(xgps,ygps,zf,zp,vfx,vfy,vtg,quality,currentMillis,ilat,ilong);
}
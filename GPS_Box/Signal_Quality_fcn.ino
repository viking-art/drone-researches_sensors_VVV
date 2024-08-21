const unsigned long INTERVAL = 4000; 
const int REQUIRED_SIGNALS = 16;      
unsigned long previousMillis = 0;    
int signalCount = 0;                 

void Signal_quality(unsigned long timer,bool *quality) 
{
  bool GPS_sig,qual;
  GPS_sig = checksignal_GPS(); 
  if (GPS_sig==1 ) signalCount++;  
  if (timer - previousMillis >= INTERVAL) 
  {
    previousMillis = timer;
    if (signalCount >= REQUIRED_SIGNALS) qual=1;  
    else  qual=0; 
    signalCount = 0; 
    *quality=qual;
  }
}



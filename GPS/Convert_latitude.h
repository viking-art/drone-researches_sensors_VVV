String convertlat()
{
  String dlat;
  float  mlat;
  for (int i = 0; i < nmea[0].length(); i++) {
    if (nmea[0].substring(i, i + 1) == ".") {
      dlat = nmea[0].substring(0, i - 2);
      mlat = nmea[0].substring(i - 2).toFloat(); // dd.mm...
    }
  }
  mlat = mlat/60;
  char charVal[9];
  dtostrf(mlat, 4, 6, charVal);
  for (int i = 0; i < sizeof(charVal); i++)
  {
    CalcLat += charVal[i];
  }
  dlat += CalcLat.substring(1);
  return dlat;

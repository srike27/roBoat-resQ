#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial sgps(5, 6);
float torad= 3.141592/180,tolat=10.7905,tolon=78.7047;
int angle;
void setup()
{
 Serial.begin(9600);
 sgps.begin(9600);
 tolat*=torad;
 tolon*=torad;
}
void loop()
{
 if (sgps.available())
 {
   int c = sgps.read();
   if (gps.encode(c))
   {
     float slat,slon;
     gps.f_get_position(&slat, &slon);
     slat*=torad;
     slon*=torad;
     angle=((atan2((sin((tolon-slon))*cos(tolat)), ((cos(slat)*sin(tolat))-(sin(slat)*cos(tolat)*cos((tolon-slon)))))*180)/3.141592);
     //angle=((angle+360)%360);
     Serial.write((angle*127)/180);
   }
 }

}

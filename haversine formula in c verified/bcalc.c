#include<stdio.h>
#include<math.h>
int main()
{
double lat1,lat2,long1,long2,x,y;
int angle;
double torad= 3.141592/180;
/*lat1=0;
long1=0;
lat2=-89;
long2=2;*/
lat2=10.7905*torad;
long2=78.7047*torad;
lat1=13.0827*torad;
long1=80.2707*torad;
angle=((atan2((sin((long2-long1))*cos(lat2)), ((cos(lat1)*sin(lat2))-(sin(lat1)*cos(lat2)*cos((long2-long1)))))*180)/3.141592);	
angle=((angle+360)%360);
printf("%d",angle);
}

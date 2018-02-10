/* 1 ---->  right motor ----> e - 2, 22,23
 * 2 ---->  back motor ----> 3, 24, 25
 * 3 ---->  left motor  ----> 4, 26, 27
 * 4 ---->  front motor ----> 5, 28, 29
 * 
 */
#include <ultdist.h>
#include <DCMotor.h>
#include <Math.h>

dcm mr(2,22,23);
dcm mb(3,24,25);
dcm ml(4,26,27);
dcm mf(5,28,29);

int vrmin=0, vbmin=0, vlmin=0, vfmin=0; // calibrate and update
int vr=0, vb=0, vl=0, vf=0;
int rspeed, bspeed, lspeed, fspeed;
int r1,r2,b1,b2,l1,l2,f1,f2;

int heading, bearing;
float theta = -90*(3.14/180); // for now; have to change later

void omnicontrol()
{
  vr = -100*(sin(theta));
  vl = -vr;
  vb = -100*(cos(theta));
  vf = -vb;
  
  // convert -100 to 100 into pwm value for speed
  if(vr>=0)
  rspeed = map(vr,0,100,vrmin,255);
  else
  rspeed = map(vr,-100,0,-255,-vrmin);
  if(vb>=0)  
  bspeed = map(vb,0,100,vbmin,255);
  else
  bspeed = map(vb,-100,0,-255,-vbmin);
  if(vl>=0)  
  lspeed = map(vl,0,100,vlmin,255);
  else
  lspeed = map(vl,-100,0,-255,-vlmin);
  if(vf>=0)
  fspeed = map(vf,0,100,vfmin,255);
  else
  fspeed = map(vf,-100,0,-255,-vfmin);

  mr.mspeed(rspeed);
  mb.mspeed(bspeed);
  ml.mspeed(lspeed);
  mf.mspeed(fspeed);
  Serial.print(rspeed);
  Serial.print(' ');
  Serial.print(bspeed);
  Serial.print(' ');
  Serial.print(lspeed);
  Serial.print(' ');
  Serial.println(fspeed);
  
}

void setup()
{
  Serial.begin(9600);
  mr.minit();
  mb.minit();
  ml.minit();
  mf.minit();
}

void loop()
{
  omnicontrol();
}


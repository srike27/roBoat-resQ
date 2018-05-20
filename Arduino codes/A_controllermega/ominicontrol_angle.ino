/*
* 1 ---->  m1 right motor ----> e - 8, 22,23
 * 2 ----> m2 back motor ----> 9, 24, 25
 * 3 ----> m3 left motor  ----> 10, 26, 27
 * 4 ----> m4 front motor ----> 11, 28, 29
 *
 */
#include <ultdist.h>
#include <DCMotor.h>

dcm m1(8,22,23);
dcm m2(9,24,25);
dcm m3(10,26,27);
dcm m4(11,28,29);

int vrmin=120, vbmin=120, vlmin=120, vfmin=120; // calibrate and update
int vr=0, vb=0, vl=0, vf=0;
int rspeed, bspeed, lspeed, fspeed;
int r1,r2,b1,b2,l1,l2,f1,f2;

int heading, bearing;
int theta = 0; // for now; have to change later

void omnicontrol(int theta)
{
  vr = -100*(sin(theta*(3.14/180)));
  vl = -vr;
  vb = -100*(cos(theta*(3.14/180)));
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

  m1.mspeed(rspeed);
  m2.mspeed(bspeed);
  m3.mspeed(lspeed);
  m4.mspeed(fspeed);
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
  m1.minit();
  m2.minit();
  m3.minit();
  m4.minit();
}

void loop()
{
  theta++;
  omnicontrol(theta);
  delay(50);
  if(theta==359){
    theta=0;
  }
}

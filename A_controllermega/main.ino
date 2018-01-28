#include <TinyGPS.h>
#include <ultdist.h>
#include <DCMotor.h>
TinyGPS gps;
long i=0,dl,dm,dr;
int sound;
int head,bearing=0,lspeed=200,rspeed=200,bear=200;
int lflag=0, mflag=0, rflag=0, lerr, merr, rerr, rkp=100, lkp=100, mkp=100;
ultdist mu(50,51);//trig,echo
ultdist ru(52,53);
ultdist lu(48,49);
dcm ml(5,8,9);//en,i1,i2 ----> left motor
dcm mr(6,10,11); // ----> right motor
float slat,slon;

void read_bearing()
{
 if(Serial2.available())
 {
  bearing=Serial2.read();
  bearing=bearing*1.40625;
 }
}

void read_head()
{
  if (Serial1.available()) 
  {
    head = Serial1.read();
    head = head*1.40625;
  }
}

void head_control(int a)
{
  int e,kp=10,f;
  if(abs(a-head)>4)
  {
    if(abs(a-head)<(360-abs(a-head)))
    {
      f = (a-head)/abs(a-head);
      e = abs(a-head);
      lspeed = (100+(e*kp))*(f);
      rspeed = (100+(e*kp))*(-f);
    }
    else
    {
      f = (head-a)/abs(a-head);
      e = 360 - abs(a-head);
      lspeed = (100+(e*kp))*(f);
      rspeed = (100+(e*kp))*(-f);
    }
    if(lspeed>255) lspeed = 255;
    if(rspeed>255) rspeed = 255;
    if(lspeed<-255) lspeed = -255;
    if(rspeed<-255) rspeed = -255;
    ml.mspeed(lspeed);
    mr.mspeed(rspeed);
    //Serial.println(head);
  }
  else
  {
    ml.mspeed(200);
    mr.mspeed(200);
  }
}

void obs_avoid()
{
  dm=mu.getdist();
  dl=lu.getdist();
  dr=ru.getdist();
  if(dl<20) {lflag = 1; lerr = 20-dl;}
  else lflag = 0; 
  if(dm<20) {mflag = 1; merr = 20-dl;}
  else mflag = 0;
  if(dr<20) {rflag = 1; rerr = 20-dr;}
  else rflag = 0;

  if(lflag==0&&mflag==0&&rflag==0)      //   000
  {
    /*lspeed = 150;
    rspeed = 150;
    ml.mspeed(lspeed);
    mr.mspeed(rspeed);*/
    head_control(bear);
  }
  if(lflag==0&&mflag==0&&rflag==1)      //   001
  {
    lspeed = -100;
    ml.mspeed(lspeed);
    rspeed += rkp*rerr;
    if(rspeed>255) rspeed = 255;
    mr.mspeed(rspeed);
    bear=head;
  }if(lflag==0&&mflag==1&&rflag==0)      //   010
  {
    //obstacle ahead
  }  
  if(lflag==0&&mflag==1&&rflag==1)      //   011
  {
    lspeed = -150; rspeed = -150;
    ml.mspeed(lspeed);
    mr.mspeed(rspeed);
    _delay_ms(1000);
    read_head();
    int temp_head;
    if(head<90) temp_head = (head-90)+360;
    else temp_head = head-90;
    while(abs(head-temp_head)>5)
    {
      head_control(temp_head);
      read_head();
    }
    bear=head;
  }  
  if(lflag==1&&mflag==0&&rflag==0)      //   100
  {
    rspeed = -100;
    mr.mspeed(rspeed);
    lspeed += lkp*lerr;
    if(lspeed>255) lspeed = 255;
    ml.mspeed(lspeed);
    bear=head;
  }  
  if(lflag==1&&mflag==1&&rflag==0)      //   110
  {
    lspeed = -150; rspeed = -150;
    ml.mspeed(lspeed);
    mr.mspeed(rspeed);
    _delay_ms(1000);
    read_head();
    int temp_head;
    if(head>270) temp_head = (head+90)-360;
    else temp_head = head+90;
    while(abs(head-temp_head)>5)
    {
      head_control(temp_head);
      read_head();
    }
    bear=head;
  }  
  if(lflag==1&&mflag==1&&rflag==1)      //   111
  {
    lspeed = -150; rspeed = -150;
    ml.mspeed(lspeed);
    mr.mspeed(rspeed);
    _delay_ms(1000);
    read_head();
    int temp_head;
    if(head<180) temp_head = (head-180)+360;
    else temp_head = head-180;
    while(abs(head-temp_head)>5)
    {
      head_control(temp_head);
      read_head();
    }
    bear=head;
  }
  Serial.print(head); Serial.print(' ');
  Serial.print(dl); Serial.print(' ');
  Serial.print(dm); Serial.print(' ');
  Serial.println(dr);
}


void setup() {
  // put your setup code here, to run once:
  mu.ultinit();
  ru.ultinit();
  lu.ultinit();
  ml.minit();
  mr.minit();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_head();
  read_bearing();
  bear=head;
  if(i%30==0){
    dm=mu.getdist();
  }
  else if(i%30==10){
    dr=ru.getdist();
  }
  else if(i%30==20){
    dl=lu.getdist();
  }
  if(dl<20||dm<20||dr<20)
  obs_avoid();
  /*if(!(digitalRead(2))&&(i%10==0)){
    Serial.println("HelP");
    Serial2.println("HelP");
  }*/
 //Serial.println(bearing);
 // head_control(bearing);
  i++;
}

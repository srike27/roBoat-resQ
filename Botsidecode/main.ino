#include <ultdist.h>
#include <DCMotor.h>
long i=0,dl,dm,dr;
int sound;
int head,lspeed=200,rspeed=200;
ultdist mu(50,51);//trig,echo
ultdist ru(52,53);
ultdist lu(48,49);
dcm ml(5,8,9);//en,i1,i2 ----> left motor
dcm mr(6,10,11); // ----> right motor

void object_avoid()
{
  if(dl<10)
  {

  }
  else
  {
    ml.mspeed(255);
    mr.mspeed(255);
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
    Serial.println(head);
  }
  else
  {
    ml.mspeed(200);
    mr.mspeed(200);
  }
}
/*void hcontrol(int a){
  int e,kp=1,f;
  if(a!=head){
    f=(a-head)/abs(a-head);
    if(abs(a-head)<abs(360-a+head)){
      e=abs(a-head);
      ml.mspeed(lspeed-f*e*kp);
      mr.mspeed(rspeed+f*e*kp);
    }
    else{
      e=abs(360-a+head);
      ml.mspeed(lspeed+f*e*kp);
      mr.mspeed(rspeed-f*e*kp);
    }
  }
  else{
    ml.mspeed(lspeed-20);
    mr.mspeed(rspeed-20);
  }
}
*/

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
  if (Serial1.available()) {
    head = Serial1.read();
    //head += 256;
    head = head*1.40625;
    //Serial.println(inByte);
    //ml.mspeed(100);
    //mr.mspeed(-100);
  }
  if(i%30==0){
    dm=mu.getdist();
  }
  else if(i%30==10){
    dr=ru.getdist();
  }
  else if(i%30==20){
    dl=lu.getdist();
  }
  /*if(dl<100&&dm<100&&dr<100){
  Serial.print(dl);
  Serial.print("  ");
  Serial.print(dm);
  Serial.print("  ");
  Serial.println(dr);
  }*/

  //object_avoid();
//  hcontrol(60);
  head_control(0);
 // Serial.println(head);
  /*if(!(digitalRead(2))&&(i%10==0)){
    Serial.println("HelP");
    Serial2.println("HelP");
  }*/
  //Serial.println(" ");
  i++;
}

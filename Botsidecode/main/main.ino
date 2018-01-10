#include <ultdist.h>
#include <DCMotor.h>
long i=0,dl,dm,dr;
int sound;
ultdist mu(50,51);//trig,echo
ultdist ru(52,53);
ultdist lu(48,49);
dcm ma(5,8,9);//en,i1,i2
dcm mb(6,10,11);
void setup() {
  // put your setup code here, to run once:
  mu.ultinit();
  ru.ultinit();
  lu.ultinit();
  ma.minit();
  mb.minit();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int inByte;
  if (Serial1.available()) {
    inByte = Serial1.read();
    if(inByte>127){
      inByte=inByte-256;
    }
    inByte=180*inByte/127;
    //Serial.println(inByte);
    ma.mspeed(inByte);
    mb.mspeed(-inByte);
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
  if(dl<100&&dm<100&&dr<100){
  Serial.print(dl);
  Serial.print("  ");
  Serial.print(dm);
  Serial.print("  ");
  Serial.println(dr);
  }
  /*if(!(digitalRead(2))&&(i%10==0)){
    Serial.println("HelP");
    Serial2.println("HelP");
  }*/
  //Serial.println(" ");
  i++;
}


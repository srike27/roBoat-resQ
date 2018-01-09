#include <ultdist.h>
#include <DCMotor.h>
long i=0,da,db,dc;
int sound;
ultdist a(50,51);//trig,echo
ultdist b(52,53);
ultdist c(48,49);
dcm ma(5,8,9);//en,i1,i2
dcm mb(6,10,11);
void setup() {
  // put your setup code here, to run once:
  a.ultinit();
  b.ultinit();
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
    da=a.getdist();
  }
  else if(i%30==10){
    db=b.getdist();
  }
  else if(i%30==20){
    dc=c.getdist();
  }
  if(da<100&&db<100&&dc<100){
  Serial.print(da);
  Serial.print("  ");
  Serial.print(db);
  Serial.print("  ");
  Serial.println(dc);
  }
  /*if(!(digitalRead(2))&&(i%10==0)){
    Serial.println("HelP");
    Serial2.println("HelP");
  }*/
  //Serial.println(" ");
  i++;
}

#include "DCMotor.h"

dcm::dcm(int ei,int i1i,int i2i) {
  e=ei;
  i1=i1i;
  i2=i2i;
}
void dcm::minit(){
  pinMode(e, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
}

void dcm::mspeed(int s) {
  if(s>0){
    digitalWrite(i1,HIGH);
    digitalWrite(i2,LOW);
  }
  else if(s<0){
    digitalWrite(i1,LOW);
    digitalWrite(i2,HIGH);
  }
  else{
    digitalWrite(i1,LOW);
    digitalWrite(i2,LOW);
  }
  analogWrite(e,abs(s));
}

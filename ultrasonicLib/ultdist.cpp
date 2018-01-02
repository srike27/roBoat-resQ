#include "ultdist.h"

ultdist::ultdist(int trigi,int echoi) {
  trig=trigi;
  echo=echoi;
}
void ultdist::ultinit(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

long ultdist::getdist() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long distance = pulseIn(echo, HIGH);
  distance= distance*0.034/2;
  return distance;
}

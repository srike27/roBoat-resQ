#include<ultdist.h>
long i=0,da,db;
ultdist a(50,51);
ultdist b(52,53);
void setup() {
  a.ultinit();
  b.ultinit();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(i%2==0){
    da=a.getdist();
  }
  else{
    db=b.getdist();
  }
  Serial.print(da);
  Serial.print("  ");
  Serial.println(db);
  i++;
}

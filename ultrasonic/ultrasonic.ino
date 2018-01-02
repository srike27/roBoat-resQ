/*
PL(0:2)-(49 48 47)-(LTrig MTrig RTrig)
INT(0,1,4)-(21,20,2)-(LEcho MEcho REcho)
PL(3:5)-(46,45,44)-(LLED MLED RLED) 
*/
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
volatile int flag1=0,flag2=0,flag3=0,o1,o2,o3;
volatile uint32_t ovf1=0,ovf2=0,ovf3=0;
volatile uint64_t time1=0,time2,time3,ms5=0;
volatile long distance1=0,distance2=0,distance3=0;
void interrupt()
{
  EIMSK |= (1 << INT0)|(1<<INT1) |(1<<INT4);
  EICRA |= (1 << ISC00)|(1<<ISC10);
  EICRB |= (1 << ISC40); 
}
void timer3init(){
    TCCR3B=(0<<CS32)|(0<<CS31)|(1<<CS30);
  TIMSK3|=(1<<TOIE3)|(OCIE3A);
  OCR3A=1020;
}
void timer4init(){
    TCCR4B=(0<<CS42)|(0<<CS41)|(1<<CS40);
  TIMSK4|=(1<<TOIE4)|(OCIE4A);
  OCR4A=1020;
}
void timer5init(){
    TCCR5B=(0<<CS52)|(0<<CS51)|(1<<CS50);
  TIMSK5|=(1<<TOIE5);
  OCR5A=1020;
}
void timer1init()
{
  TCCR1B |= (1<<WGM12) | (1<<CS11)|(1<<CS10);//Prescalar 64
  TIMSK1 |=(1<<OCIE1A);
  OCR1A=2499;
}
void ultracheck(){
  if(distance1<200){
      //Serial.print(distance1);
      //Serial.print(' ');
      PORTL|=(1<<PL3); 
    }
    else{
      //Serial.print("x  ");
      PORTL&=~(1<<PL3);
    }
    if(distance2<200){
      //Serial.print(distance2);
      //Serial.print(' ');
      PORTL|=(1<<PL4); 
    }
    else{
      //Serial.print("x  ");
      PORTL&=~(1<<PL4);
    }
    if(distance3<200){
      //Serial.print(distance3);
      //Serial.println(' ');
      PORTL|=(1<<PL5); 
    }
    else{
      //Serial.println("x  ");
      PORTL&=~(1<<PL5);
    }
}
int main()
{
  DDRL=0xFF;
  interrupt();
  timer3init();
  timer4init();
  timer5init();
  timer1init();
  sei();
  //Serial.begin(9600);
  while(1)
  {
    ultracheck();
  }
}
ISR(TIMER1_COMPA_vect){
  if(ms5==1){
    PORTL |= (1<<PL0);
    _delay_us(10);
    PORTL=0;
  }
  if(ms5==5){
    PORTL |= (1<<PL1);
    _delay_us(10);
    PORTL=0;
  }
  if(ms5==9){
    PORTL |= (1<<PL2);
    _delay_us(10);
    PORTL=0;
  }
  if(ms5==13){
    ms5=0;
  }
  ms5++;
}
ISR(TIMER3_COMPA_vect){
  if(flag1&&ovf1==0){
    o1=1;
  }
}
ISR(TIMER4_COMPA_vect){
  if(flag2&&ovf2==0){
    o2=1;
  }
}
ISR(TIMER5_COMPA_vect){
  if(flag3&&ovf3==0){
    o3=1;
  }
}
ISR(TIMER3_OVF_vect)
{
  if(flag1)
  ovf1++;
}
ISR(TIMER4_OVF_vect)
{
  if(flag2)
  ovf2++;
}
ISR(TIMER5_OVF_vect)
{
  if(flag3)
  ovf3++;
}

ISR(INT0_vect)
{ 
 if(flag1==0)
 {
  flag1=1;
  o1=0;
  ovf1=0;
  TCNT3=0;
 }
 else if(flag1==1)
 {
  time1=(ovf1*65536 + TCNT3);
  distance1 = (((time1) * (0.034))/32);
  flag1=0;
   
 }
}
ISR(INT1_vect)
{ 
 
 if(flag2==0)
 {
  flag2=1;
  ovf2=0;
  o2=0;
  TCNT4=0;
  
 }
 else if(flag2==1)
 {
  time2=(ovf2*65536 + TCNT4);
  distance2 = (((time2) * (0.034))/32);
  flag2=0;
 }
}
ISR(INT4_vect)
{ 
 
 if(flag3==0)
 {
  flag3=1;
  ovf3=0;
  o3=0;
  TCNT5=0;
  
 }
 else if(flag3==1)
 {
  time3=(ovf3*65536 + TCNT5);
  distance3 = (((time3) * (0.034))/32);
  flag3=0; 
 }
}

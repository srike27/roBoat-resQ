#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
volatile int flag1=0,flag2=0,flag3=0;
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
  TIMSK3|=(1<<TOIE3)|(1<<OCIE3A);
}
void timer4init(){
    TCCR4B=(0<<CS42)|(0<<CS41)|(1<<CS40);
  TIMSK4|=(1<<TOIE4)|(1<<OCIE4A);
}
void timer5init(){
    TCCR5B=(0<<CS52)|(0<<CS51)|(1<<CS50);
  TIMSK5|=(1<<TOIE5)|(1<<OCIE5A);
}
void timer1init()
{
  TCCR1B |= (1<<WGM12) | (1<<CS11)|(1<<CS10);//Prescalar 64
  TIMSK1 |=(1<<OCIE1A);
  OCR1A=1249;
}
int main()
{
  DDRB|=0b00000001;
  DDRD&=0b11111011;
  interrupt();
  timer3init();
  timer4init();
  timer5init();
  timer1init();
  sei();
  Serial.begin(9600);
  while(1)
  {
     /*PORTL&=0b11111110;
     _delay_us(1);
     PORTL|=0b00000001;
     _delay_us(10);
     PORTL&=0b11111110;
     _delay_ms(20);
     
     
     PORTL&=0b11111101;
     _delay_us(1);
     PORTL|=0b00000010;
     _delay_us(10);
     PORTL&=0b11111101;
     _delay_ms(20);

     
     PORTL&=0b11111011;
     _delay_us(1);
     PORTL|=0b00000100;
     _delay_us(10);
     PORTL&=0b11111011;
     _delay_ms(20);
  */
     Serial.print(distance1);
     Serial.print(' ');
     Serial.print(distance2);
     Serial.print(' ');
     Serial.println(distance3);
  }
}
ISR(TIMER1_COMPA_vect){
  if(ms5==0){
    PORTL |= (1<<PL0);
    _delay_us(10);
    PORTL=0;
  }
  if(ms5==4){
    PORTL |= (1<<PL1);
    _delay_us(10);
    PORTL=0;
  }
  if(ms5==8){
    PORTL |= (1<<PL2);
    _delay_us(10);
    PORTL=0;
    ms5=0;
  }
  ms5++;
}
ISR(TIMER3_COMPA_vect){
  
}
ISR(TIMER4_COMPA_vect){

}
ISR(TIMER5_COMPA_vect){

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
  ovf1=0;
  TCNT3=0;
  
 }
 else if(flag1==1)
 {
  time1=(ovf1*65536 + TCNT3);
  distance1 = (((time1) * (0.034))/32);
  flag1=0; 
  if(distance1>150){
    distance1=337-distance1;
  }
 }
}
ISR(INT1_vect)
{ 
 
 if(flag2==0)
 {
  flag2=1;
  ovf2=0;
  TCNT4=0;
  
 }
 else if(flag2==1)
 {
  time2=(ovf2*65536 + TCNT4);
  distance2 = (((time2) * (0.034))/32);
  flag2=0;
  if(distance2>150){
    distance2=337-distance2;
  } 
 }
}
ISR(INT4_vect)
{ 
 
 if(flag3==0)
 {
  flag3=1;
  ovf3=0;
  TCNT5=0;
  
 }
 else if(flag3==1)
 {
  time3=(ovf3*65536 + TCNT5);
  distance3 = (((time3) * (0.034))/32);
  flag3=0; 
  if(distance3>150){
    distance3=337-distance3;
  }
 }
}

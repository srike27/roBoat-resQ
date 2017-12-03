/*
Arduino Uno
2 BODC motors
L293D Motor Driver
pin5-EB
pin6-EA
pin8,pin9-A1,A2
pin11,pin10-B1,B2
*/
#include<avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include<avr/interrupt.h> 
void timer0init(){
  TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<COM0B1);
  TCCR0B|=(1<<CS01);
  TIMSK0|=(1<<OCIE0A)|(1<<OCIE0B);
}
void setduty(int l,int r){
  OCR0A=(255*l)/100;
  OCR0B=(255*r)/100;
}

int main()
{
  DDRB=0xFF;
  DDRD=0xFF;
  timer0init();
  int i=0;
  while(1)
  {PORTB=(1<<0)|(1<<3);
  for(i=100;i>60;i--){
  setduty(i,i);
  _delay_ms(20);
  }
  for(i=60;i<100;i++){
  setduty(i,i);
  _delay_ms(20);
  }
  PORTB=(1<<1)|(1<<2);
  for(i=100;i>60;i--){
  setduty(i,i);
  _delay_ms(20);
  }
  for(i=60;i<100;i++){
  setduty(i,i);
  _delay_ms(20);
  } 
 }
}


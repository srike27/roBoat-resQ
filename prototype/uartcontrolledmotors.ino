#include<avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include<avr/interrupt.h>
unsigned char ch; 
void timer0init(){
  TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<COM0B1);
  TCCR0B|=(1<<CS01);
  TIMSK0|=(1<<OCIE0A)|(1<<OCIE0B);
}
void timer1init()
{
  TCCR1B |= (1<<WGM12) | (1<<CS11)|(1<<CS10);//Prescalar 64
  TIMSK1 |=(1<<OCIE1A);
  OCR1A=2499;
}

void setduty(int l,int r){
  OCR0A=(255*l)/100;
  OCR0B=(255*r)/100;
}
void usart_init(void)
 { UCSR0B=(1<< RXEN0)|(1<< TXEN0); 
UCSR0C=(1<<UCSZ01)|(1<<UCSZ00) ; 
UBRR0L= 0x67 ; //BAUD RATE 9600 
UCSR0A= 0x00;
}
 void usart_send(int ch ) 
 
{
 while(UCSR0A!=(UCSR0A|(1<< UDRE0)));//waiting for UDRE to become high
 UDR0= ch; }

char usart_recieve(){
 while(UCSR0A!= (UCSR0A|(1<<RXC0)));
 ch=UDR0;
 return ch;
}
void ff(){
  PORTB=(1<<0)|(1<<3);
  setduty(100,100);
}
void fb(){
  PORTB=(1<<1)|(1<<2);
  setduty(100,100);
}
void fs(){
  PORTB=PORTB & 0b11110000;
}
void pr(){
  PORTB=(1<<1)|(1<<3);
}
void pl(){
  PORTB=(1<<0)|(1<<2);
}
int main(){
  DDRD|=(1<<5)|(1<<6);
  timer0init();
  DDRB=0xFF;
  usart_init();
  sei();
  while(1){
    usart_recieve();
    if(ch==0b10110111)
    {  
      ff();
    }
    else if(ch==0b01111011) 
    {
      fb(); 
    }
    else if(ch==0){
      fs();
    }
    else if(ch==0b10110000){
      PORTB=(1<<0);//toprightcorner
    }
    else if(ch==0b00000111){
      PORTB=(1<<3);//topleftcorner
    }
    else if(ch==0b01110000){
      PORTB=(1<<1);//bottomleftcorner
    }
    else if(ch==0b00001011){
      PORTB=(1<<2);//bottomrightcorner
    }
    else if(ch==0b10111011){
      pl();//leftcorner
    }
    else if(ch==0b01110111){
      pr();//leftcorner
    }
    /*else if(ch=='6'){
      pr(); 
    }
    else if(ch=='4'){
      pl();
    }*/
  }
  return 0;
}



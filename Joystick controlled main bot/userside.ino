#include<avr/io.h>
void adc_init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
  uint16_t adc;
  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8)|ch;
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  adc=ADC;
   ADMUX = (ADMUX & 0b11111000);
  return (adc);
}
void usart_int(void)
 { UCSR0B=(1<< RXEN0)|(1<< TXEN0); 
UCSR0C=(1<<UCSZ01)|(1<<UCSZ00) ; 
UBRR0L= 0x67 ; //BAUD RATE 9600 
UCSR0A= 0x00;
}
 void usart_send(int ch ) 
 
{
 while(UCSR0A!=(UCSR0A|(1<< UDRE0)));
 UDR0= ch; }
 int main(void) 
{ DDRB=0xFF;
 PORTB=0x00; 
usart_int();
adc_init();
uint16_t x,y; 
unsigned char ch; 
while(1) 
{ 
  x=adc_read(0);
  y=adc_read(1);
  if(x>1000){
    ch='8';
  }
  else if(x<750){
    ch='2';
  }
  else if(y>1000){
    ch='6';
  }
  else if(y<750){
    ch='4';
  }
  else{
    ch='5';
  }
 usart_send(ch);
 } 
} void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

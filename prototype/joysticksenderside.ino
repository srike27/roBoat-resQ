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
  if(x>600&&y>600){
    ch=0b10110000;//topright
  }
  else if(x<450&&y>600){
    ch=0b00001011;
  }
  else if(x>600&& y<450){
    ch=0b00000111;
  }
  else if(y<450 && x<450){
    ch=0b01110000;
  }
  else if(x>450 && x<600 && y>450 && y<600){
    ch=0;
  }
  else if(x>600&& y>450 && y<600){
    ch=0b10110111;//forward
  }
  else if(x>450 && x<600 && y>600){
    ch=0b10111011;
  }
  else if(x>450 && x<600&& y<450){
    ch=0b01110111;
  }
  else if(x<450&& y>450 && y<600){
    ch=0b01111011;//reverse
  }
  
 usart_send(ch);
 } 
} 

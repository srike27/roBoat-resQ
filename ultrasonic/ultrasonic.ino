#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
volatile int flag=0;
volatile uint32_t ovf=0;
volatile uint64_t timer=0;
volatile long distance=0;
void interrupt()
{
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC00);
}
int main()
{
  DDRB|=0b00000001;
  DDRD&=0b11111011;
  interrupt();
  sei();
  TCCR0B=(0<<CS02)|(0<<CS01)|(1<<CS00);
  TIMSK0|=(1<<TOIE0);
  Serial.begin(9600);
  while(1)
  {
     PORTB&=0b11111110;
     _delay_us(1);
     PORTB|=0b00000001;
     _delay_us(10);
     PORTB&=0b11111110;
     _delay_ms(50);
     Serial.println(distance);
     
  }
}
ISR(TIMER0_OVF_vect)
{
  if(flag)
  ovf++;
}
ISR(INT0_vect)
{ 
 
 if(flag==0)
 {
  flag=1;
  ovf=0;
  TCNT0=0;
  
 }
 else if(flag==1)
 {
  timer=(ovf*256 + TCNT0);
  distance = ((float(timer) * (0.034))/32);
  flag=0; 
 }
}


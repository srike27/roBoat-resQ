#include<avr/io.h>

unsigned char ch;
  
void UART_init()
{
  UBRR0L = 0x67;
  UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
  UCSR0A = 0x00;
}

void UART_init1()
{
  UBRR1L = 0x67;
  UCSR1B |= (1<<TXEN1) | (1<<RXEN1);
  UCSR1A = 0x00;
}

void UART_send( int x)
{
  while(UCSR0A != (UCSR0A|(1<<UDRE0)));
  UDR0 = x;
}

void UART_receive()
{
  while(UCSR0A != (UCSR0A|(1<<RXC0)));
  ch = UDR0;
}

void UART_receive1()
{
  while(UCSR1A != (UCSR1A|(1<<RXC1)));
  ch = UDR1;
}

int main()
{
  DDRB = 0xFF;
  PORTB = 0x00;
  UART_init();
  UART_init1();
  while(1)
  {
   for(int i=0;i<20;i++)
   {
    UART_receive1();
    UART_send(ch);
   }
   UART_send('\n');
  }
}


#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#define BAUD 9600U
#define BAUD_PRESCALER ( ( F_CPU/(8UL*BAUD) ) - 1U )
#define ASYNCHRONOUS  0b00000000
#define PARITY_BIT 0b00000000
#define STOP_BIT 0b00000000
#define DATA_BITS 0b00000110
#define DOUBLE_MODE (UCSR0A | (1<<U2X0))
#define TRANSMITTER_EN (UCSR0B | (1U<<TXEN0) )


void usart_init(void)
{
 
  // setting the baud rate of 9600
  UBRR0L = BAUD_PRESCALER; 
  UBRR0H = BAUD_PRESCALER >> 8;
  // setting the FRAME STRUCTURE
  UCSR0C = (ASYNCHRONOUS | PARITY_BIT | STOP_BIT |  DATA_BITS) ;
  UCSR0A = DOUBLE_MODE; // setting DOUBLE_MODE  of asynchronous operation
  UCSR0B = TRANSMITTER_EN; // for 8 data bit selection, and also transmitter is enabled
	
	
}
void usart_transmit(unsigned char data) // unsigned int is two bytes.
{
 
	while ((UCSR0A & (1<<UDRE0))==0){}; // wait until buffer is empty
    UDR0 = data; // data transmit buffer
}



int main(void)
{
    
	
    usart_init();
	while(1)
	{
    unsigned char a = 'A';
       usart_transmit(a);
		_delay_ms(1000);
	}
	
}
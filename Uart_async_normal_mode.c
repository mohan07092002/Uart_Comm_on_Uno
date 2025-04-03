#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#define BAUD 9600U
#define BAUD_PRESCALER ( ( F_CPU/(16UL*BAUD) ) - 1U )
#define ASYNCHRONOUS  0b00000000
#define PARITY_BIT 0b00000000
#define STOP_BIT 0b00000000
#define DATA_BITS 0b00000110
#define NORMAL_MODE UCSR0A
#define TRANSMITTER_EN (UCSR0B | (1U<<TXEN0))


void usart_init(void)
{
  // setting the FRAME STRUCTURE
  UCSR0C = (ASYNCHRONOUS | PARITY_BIT | STOP_BIT |  DATA_BITS) ;
	// setting the baud rate of 9600
	UBRR0L = BAUD_PRESCALER; 
	UBRR0H = BAUD_PRESCALER >> 8;
 
	UCSR0A = NORMAL_MODE; // setting normal mode of asynchronous operation, transmit buffer is empty we are setting
	UCSR0B = TRANSMITTER_EN; // for 8 data bit selection, and also transmitter is enabled
	
}
void usart_transmit(unsigned char data)
{
 
	while ((UCSR0A & (1<<UDRE0))==0){}; // wait till buffer is empty
	UDR0 = data; // data transmit buffer
}



int main(void)
{
    /* Replace with your application code */
	
    usart_init();
	while(1)
	{
		usart_transmit('H');
		usart_transmit('E');
		usart_transmit('L');
		usart_transmit('L');
		usart_transmit('O');
		usart_transmit('\n');
		_delay_ms(1000);
	}
	
}
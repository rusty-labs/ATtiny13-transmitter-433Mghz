/*
  RF transmitter example for attiny13.
  The code was created by analyzing these sources:
  1. RCSwitch library, https://code.google.com/p/rc-switch/
  2. http://habrahabr.ru/post/224459/
  3. http://avrbasiccode.wikispaces.com/
  
  For data receving just use examples from RCSwitch.
  
  Don't forget to set up properly frequency for attiny13.
  See Arduino\hardware\attiny\boards.txt
  I've used attiny13.build.f_cpu=1200000L to get proper delays
  
*/

#include <util/delay.h>

const short  nPulseLength = 350;

const short  nHighPulses_0 = (nPulseLength * 1);
const short nLowPulses_0 = (nPulseLength * 3);

const short nHighPulses_1 = (nPulseLength * 3);
const short nLowPulses_1 = (nPulseLength * 1);

const short nLowPulses_sync =  (nPulseLength * 31);

#define PIN_TX		(1<<PB3) // PB3 pin, goes to transmitter data pin
#define PIN_LED		(1<<PB4) // PB4 pin, for led

void send(char* sCodeWord){

	while (*sCodeWord != '\0') {
  
		PORTB |= PIN_TX; // same as digitalWrite high

		if(*sCodeWord == '0')
		{
			_delay_us(nHighPulses_0);
			PORTB &= ~PIN_TX; // same as digitalWrite low
			_delay_us(nLowPulses_0);
		}else
		{
			_delay_us(nHighPulses_1);
			PORTB &= ~PIN_TX;
			_delay_us(nLowPulses_1);
		} 

		++sCodeWord;
	}

	PORTB |= PIN_TX;
	_delay_us(nHighPulses_0);

	PORTB &= ~PIN_TX;
	_delay_us(nLowPulses_sync);
}


void setup() {         
	DDRB |= PIN_TX; // Set output direction on PIN_TX
}

void loop() {  

	for(byte i = 0; i<10; ++i)
	{
	  send("1011101000110101"); 
	}

	//_delay_ms(1000);
}

/* file Sensor.c
********************************************************************************
********************************************************************************
Visitor Counter: counts the amount of people entering or leaving a room
IDE:    Atmel Studio 6.2
Target: ATmega328P 8b microcontroller on Arduino Uno dev board
================================================================================
DEVELOPMENT TEAM
Anthony Dinh
Michael Jurs
================================================================================
CODE MAP
void sendTriggerA(void); ->send trigger pulse to sensor A
void sendTriggerB(void); ->send trigger pulse to sensor B
unsigned long getDurationA(void); -> get the duration of echo A
unsigned long getDurationB(void); -> get the duration of echo B
long microsecondsToCentimeters(long); -> convert time into distance
conditional block that determines who enter + leaves by looking at a certain distance
void display_count(int); -> display amount of count
================================================================================
TODO
Add code to improve delay between people
Add code to have buzzer implemented
Add feature that stores about of people at a certain time period for future reference
================================================================================
*/


#define F_CPU 16000000UL
#include <avr/io.h>
#include<avr/wdt.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <stdlib.h>

void sendTriggerA(void);
void sendTriggerB(void);
unsigned long getDurationA(void);
unsigned long getDurationB(void);
long microsecondsToCentimeters(long);
void lcd_init(void);
void lcd_display_distance_for_testing(long);
void lcd_wr_cmd(char);
void lcd_wr_char(char);
void display_count(int);

int main()
{

	//Initialize variables for main use
	long durationA, durationB, distanceA, distanceB;
	char lastFlag = 'z';
	int count = 0;
	int current_count = 0;


	//LCD initializing
	DDRB = 0b00000111; //E, RW, RS
	DDRD = 0xFF; //LCD Inputs

	//triggerB initializing
	DDRC |= (1 << PC1); // output trigger b
	DDRC &= ~(1 << PC4); //input echo b
	DDRC |= (1 << PC2); //OUTPUT LED pink

	//triggerA initializing
	DDRB |= (1 << PB3); //trigger a
	DDRB &= ~(1 << PB5); //input echo a
	DDRC |= (1 << PC3); //led red

	lcd_init(); //Initialize LCD to be used

	sei(); //set interrupt

	while (1)
	{
		// this block of code sets up sensor to be used and gets the duration back
		sendTriggerA();
		durationA = getDurationA();
		sendTriggerB();
		durationB = getDurationB();

		//converts duration into distance
		distanceB = microsecondsToCentimeters(durationB);
		distanceA = microsecondsToCentimeters(durationA);

		//conditional block that detects if entering or leaving by using
		//a flag to determine which was the last sensor used
		if (distanceB > 15 && distanceB < 40)
		{
			PORTC |= (1 << PC2);
			if (lastFlag == 'a')
			{
				count++;
				lastFlag = 'z';
				_delay_ms(100);
			} else
			{
				lastFlag = 'b';
			}

		} else
		{
			PORTC &= ~(1 << PC2);
		}

		if (distanceA > 15 && distanceA < 40)
		{
			PORTC |= (1 << PC3);
			if (lastFlag == 'b')
			{
				count--;
				lastFlag = 'z';
				_delay_ms(100);
			} else
			{
				lastFlag = 'a';
			}

		} else
		{
			PORTC &= ~(1 << PC3);
		}

		// if over 1000 people in room just restart counter
		//not realistically possible
		//and not allowed to have negative count
		if (count == 1000 || count < 0)
		{
			count = 0;
		}

		//displays count to LCD
		if (count != current_count)
		{
			current_count = count;
			lcd_wr_cmd(0x01);
			display_count(count);

		}

	_delay_ms(200);


	}
}

//sending pulse from MCU to sensor B
void sendTriggerB()
{

	PORTC &= ~(1 << PC1);
	_delay_us(2);
	PORTC |= (1 << PC1);
	_delay_us(5);
	PORTC &= ~(1 << PC1);
}

//sending pulse from MCU to sensor A
void sendTriggerA()
{

	PORTB &= ~(1 << PB3);
	_delay_us(2);
	PORTB |= (1 << PB3);
	_delay_us(5);
	PORTB &= ~(1 << PB3);
}

//convert time it takes to distance
long microsecondsToCentimeters(long microseconds)
{

	return microseconds / 29 / 2;
}

//calculates the time it takes for echo pin B to go low and returns it in microsecond
unsigned long getDurationB()
{
	unsigned long duration = 0;
	unsigned long loopCount = 0;
	unsigned long maxCount = 3000; //amount of loops desired to wait for

	// While the pin is not high, don't do anything and make sure the max hasnt been reached
	while (((PINC >> PC4) & 1) != 1)
	{
		if (loopCount++ == maxCount)
		{
			return 0;
		}
	}

	// When the pin is high, increment the timer and make sure not more than max
	while (((PINC >> PC4) & 1) == 1)
	{
		if (loopCount++ == maxCount)
		{
			return 0;
		}
		duration++;
	}

	// Return the pulse time in microsecond!
	return duration * 1.455;

}



unsigned long getDurationA()
{
	unsigned long duration = 0;
	unsigned long loopCount = 0;
	unsigned long maxCount = 3000;

	// While the pin is *not* in the target state we make sure the timeout hasn't been reached.
	while (((PINB >> PB5) & 1) != 1)
	{
		if (loopCount++ == maxCount)
		{
			return 0;
		}
	}

	// When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
	while (((PINB >> PB5) & 1) == 1)
	{
		if (loopCount++ == maxCount)
		{
			return 0;
		}
		duration++;
	}

	// Return the pulse time in microsecond!
	return duration * 1.455;

}

void lcd_wr_cmd(char cmd) // function set
{
	PORTB = 0b00000000; // 0, 0, 0
	PORTD = cmd; //function set

	_delay_us(1); // tw delay
	PORTB = 0b00000100; // 1, 0 ,0 ( E is high)
	PORTB = 0b00000000; // 0, 0 ,0 (E go low again)

}

void lcd_init(void)
{
	_delay_ms(1);
	_delay_ms(40); // can be tuned down to be 20
	lcd_wr_cmd(0x38); // function set command
	_delay_us(80);
	lcd_wr_cmd(0x0C); //display set
	_delay_us(80);
	lcd_wr_cmd(0x06); //enable set
	_delay_us(80);
	//lcd_wr_custom(0, myHeart); //write to the CG RAM

}

void lcd_wr_char(char character)
{
	PORTB = 0b00000000;
	PORTD = character; //display character
	PORTB = 0b00000001; // 0, 0, 1
	_delay_us(1); // tw delay
	PORTB = 0b00000101; // 1, 0 ,1
	PORTB = 0b00000001; // 0, 0 ,1
	_delay_ms(1);

}
//not used for final production but can be used while debugging and if wanted to see
//how far sensor could reach and the distance it outputs
//also can check for accuracy
void lcd_display_distance_for_testing(long distance)
{
	char my_string[7];
	ltoa(distance, my_string, 10);
	if (distance < 100)
	{
		for (int i = 0; i < 2; i++)
		{
			lcd_wr_char(my_string[i]);
		}
	} else
	{
		for (int i = 0; i < 3; i++)
		{
			lcd_wr_char(my_string[i]);
		}
	}

}

//outputs  the total count to LCD
void display_count(int count_input)
{
	char count_string[7];
	char unit_message[] = { 't', 'o', 't', 'a', 'l', ':', ' ' };
	ltoa(count_input, count_string, 10); // function from stlib.h to covert long to char
	_delay_ms(100);

	//prints out "total" to LCD
	for (int i = 0; i < 7; i++)
	{
		lcd_wr_char(unit_message[i]);
		_delay_ms(100);
	}

	//conditionals to print out number because has a funny character if digit has 2 places or 3 places
	if (count_input < 10)
	{
		for (int i = 0; i < 1; i++)
		{
			lcd_wr_char(count_string[i]);
			// _delay_ms(100);
		}
	} else if (count_input < 100)
	{
		for (int i = 0; i < 2; i++)
		{
			lcd_wr_char(count_string[i]);
			// _delay_ms(100);
		}

	} else
	{
		for (int i = 0; i < 3; i++)
		{
			lcd_wr_char(count_string[i]);
		}
	}

	lcd_wr_char(' ');
	// _delay_ms(100);

}




//bike will automatically honk whenever there is an obstacle within a certain range
#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>


#define TRIG 3
#define ECHO 4

void setup()
	{

		wiringPiSetup();

		pinMode(TRIG, OUTPUT);
		pinMode(ECHO,INPUT);

		digitalWrite(TRIG,LOW);
		delay(30);
	}




	int getCM()
	{

		digitalWrite(TRIG,HIGH);
		delayMicroseconds(20);
		digitalWrite(TRIG,LOW);

		while(digitalRead(ECHO)==LOW);
		
		long startTime=micros();
		
		while(digitalRead(ECHO)==HIGH);
		
		long travelTime=micros()-startTime;
		
		int distance=travelTime*0.034/2;
		
		return distance;
	}	
	



	int main()
	{	wiringPiSetup();
		pinMode(5,OUTPUT);
		digitalWrite(5,LOW);
		setup();
		while(1)
		{
			int dist=getCM();
			printf("Distance: %dcm\n",dist);
if(dist<50)
			{	digitalWrite(5,HIGH);//value to be changed
				printf("honking the horn\n");
				delay(3000);
				digitalWrite(5,LOW);
			}
					
			
			delay(1000);
		}
	}

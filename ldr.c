//Lights will atomatically scitch on in the night
#include<stdio.h>
#include<wiringPi.h>

int main()
{
  int LIGHT=21, led=22, L;
  wiringPiSetup();
  pinMode(LIGHT, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW );
  
while(1)
  {
      L=digitalRead(LIGHT); // READ THE SENSOR
        

       if(L==1)
    {
        printf("LIGHT IS ON\n");
        digitalWrite(led,HIGH);
    }
     
       else
    {
        printf("LIGHT IS OFF\n");
        digitalWrite(led, LOW);
    }
   delay(500);


}
//END
}        

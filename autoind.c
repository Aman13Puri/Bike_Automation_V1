//Indicators will work automatically using movement of the bike handle
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define Device_Address 0x68	/*Device Address/Identifier for MPU6050*/

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

int fd;

void MPU6050_Init(){
	
	wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
	wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
	wiringPiI2CWriteReg8 (fd, CONFIG, 0);		/* Write to Configuration register */
	wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

	} 
short read_raw_data(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}



int main(){
	int i;
	float Gyro_x,Gyro_y,Gyro_z;
	float Gx=0, Gy=0, Gz=0;
	fd = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
	MPU6050_Init();		                 /* Initializes MPU6050 */
	wiringPiSetup();
	pinMode(2,OUTPUT);
	pinMode(1,OUTPUT);
	while(1)
	{	digitalWrite(1,LOW);
		digitalWrite(2,LOW);
		Gyro_z = read_raw_data(GYRO_ZOUT_H);
		Gz = Gyro_z/131;
		if(Gz>10.0)
		{	printf("Left Turn\n");
			for(i=0;i<5;i++)
			{	
				digitalWrite(1,HIGH);
				delay(500);
				digitalWrite(1,LOW);
				delay(500);
			}
		}

		if(Gz<-10.0)
		{	printf("Right Turn\n");
			for(i=0;i<5;i++)
			{	
				digitalWrite(2,HIGH);
				delay(500);
				digitalWrite(2,LOW);
				delay(500);
			}
		}
		
		
		delay(100);
		
	}
	return 0;
}

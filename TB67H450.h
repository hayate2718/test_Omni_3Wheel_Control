/* 
 * File:   TB67H450.h
 * Author: 0_hayate
 *
 * Created on January 24, 2024, 5:58 PM
 */

#ifndef TB67H450_H
#define	TB67H450_H

/*
PIN_1_GND;	GND
PIN_2_IN2;	logic in 2
PIN_3_IN1;	logic in 1
PIN_4_VREF;	motor output current config pin
PIN_5_VM;	motor supply
PIN_6_OUT1;	motor output pin 1
PIN_7_RS;	motor output current shunt pin
PIN_8_OUT2; motor output pin 2
*/

class TB67H450
{
private:
	
	unsigned long int PIN2_IN2; 
	unsigned long int PIN3_IN1;

	void* _PIN2_IN2;
	void* _PIN3_IN1;

	unsigned long int PWM_Resolution;
	float PWM_Const;
	unsigned char calc_flag_1;

public:
	
	TB67H450(void* _PIN2_IN2,void* _PIN3_IN1);

	void Set_PIN2_IN2(unsigned int pin_stat);
	void Set_PIN3_IN1(unsigned int pin_stat);
	
	void Define_PIN2_IN2(void* _MCU_PIN);
	void Define_PIN3_IN1(void* _MCU_PIN);

	void Set_PWM_Resolution(unsigned long int resolution);

	void Motor_Control(float vel, float max_vel);

};


#endif	/* TB67H450_H */


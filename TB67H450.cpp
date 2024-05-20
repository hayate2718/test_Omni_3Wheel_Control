#include "TB67H450.h"
#include <string.h>
#include <math.h>

TB67H450::TB67H450(void* _PIN2_IN2,void* _PIN3_IN1) :
	PIN2_IN2(0),
	PIN3_IN1(0),
	PWM_Resolution(0),
	PWM_Const(0),
	calc_flag_1(0){
	
	this->_PIN2_IN2 = _PIN2_IN2;
	this->_PIN3_IN1 = _PIN3_IN1;


	return;
}

void TB67H450::Set_PIN2_IN2(unsigned int stat) {
	this->PIN2_IN2 = stat;
	memcpy(this->_PIN2_IN2,&(this->PIN2_IN2),sizeof(this->_PIN2_IN2));

}

void TB67H450::Set_PIN3_IN1(unsigned int stat) {
	this->PIN3_IN1 = stat;
	memcpy(this->_PIN3_IN1, &(this->PIN3_IN1), sizeof(this->_PIN3_IN1));
}

void TB67H450::Define_PIN2_IN2(void* _MCU_PIN) {
	this->_PIN2_IN2 = _MCU_PIN;
}

void TB67H450::Define_PIN3_IN1(void* _MCU_PIN) {
	this->_PIN3_IN1 = _MCU_PIN;
}

void TB67H450::Set_PWM_Resolution(unsigned long int resolution) {
	this->PWM_Resolution = resolution;
}

void TB67H450::Motor_Control(float vel,float max_vel) {

	if (!this->calc_flag_1) {
		this->PWM_Const = this->PWM_Resolution / max_vel;
		calc_flag_1 = 1; 
	}

	unsigned long int vel_buf = (unsigned long int)fabsf(vel*this->PWM_Const);
	
	if (vel < 0) {
		Set_PIN2_IN2(0);
		Set_PIN3_IN1(vel_buf);
	}
	else {
		Set_PIN2_IN2(vel_buf);
		Set_PIN3_IN1(0);
	}
}

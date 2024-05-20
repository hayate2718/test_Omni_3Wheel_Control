
#include "omni_3wheel_control.h"
#include "math.h"


omni_3wheel_control::omni_3wheel_control() : 
	wheel_1(0),
	wheel_2(0),
	wheel_3(0),
	wheel_1_velocity(0),
	wheel_2_velocity(0),
	wheel_3_velocity(0),
	global_velocity_x(0),
	global_velocity_y(0),
	local_velocity_x(0),
	local_velocity_y(0),
	robot_angle(0),
	robot_range(1),
	robot_angular_velocity(0),
	robot_angular_wheel(0)
{

	//????????????????
	cos_theta_1 = 0.5;
	sin_theta_1 = 0.8660254;

	cos_theta_2 = 0.5;
	sin_theta_2 = -(0.8660254);

	cos_theta_3 = -1;
	sin_theta_3 = 0;


	return;
}

void omni_3wheel_control::local_control(float local_velocity_x, float local_velocity_y){

	this->local_velocity_x = local_velocity_x;
	this->local_velocity_y = local_velocity_y;

	wheel_1 = this->local_velocity_x * cos_theta_1 + this->local_velocity_y * sin_theta_1;
	wheel_2 = this->local_velocity_x * cos_theta_2 + this->local_velocity_y * sin_theta_2;
	wheel_3 = this->local_velocity_x * cos_theta_3 + this->local_velocity_y * sin_theta_3;

	return;
}

void omni_3wheel_control::global_control(float global_velocity_x, float global_velocity_y) {
	
	this->global_velocity_x = global_velocity_x;
	this->global_velocity_y = global_velocity_y;

	float angle = 0;
	angle = this->get_robot_angle();

	this->local_control(
		this->global_velocity_x * cosf(angle)+this->global_velocity_y * sinf(angle),
		this->global_velocity_y * cosf(angle)-this->global_velocity_x * sinf(angle)
	);

	return;
}


void omni_3wheel_control::angular_velocity_control(float angular_velocity) {
	
	this->robot_angular_velocity = angular_velocity;

	this->robot_angular_wheel = this->robot_range * this->robot_angular_velocity;
	
	return;
}

float omni_3wheel_control::get_wheel_velocity_1() {
	this->wheel_1_velocity = this->wheel_1 + this->robot_angular_wheel;
	return this->wheel_1_velocity;
}

float omni_3wheel_control::get_wheel_velocity_2() {
	this->wheel_2_velocity = this->wheel_2 + this->robot_angular_wheel;
	return this->wheel_2_velocity;
}

float omni_3wheel_control::get_wheel_velocity_3() {
	this->wheel_3_velocity = this->wheel_3 + this->robot_angular_wheel;
	return this->wheel_3_velocity;
}


void omni_3wheel_control::set_robot_angle(float angle) {
	this->robot_angle = angle;
	return;
}

float omni_3wheel_control::get_robot_angle() {
	return this->robot_angle;
}


void omni_3wheel_control::set_sin_theta_1(float theta){
	this->sin_theta_1 = theta;
	return;
}

void omni_3wheel_control::set_cos_theta_1(float theta) {
	this->cos_theta_1 = theta;
	return;
}

void omni_3wheel_control::set_sin_theta_2(float theta) {
	this->sin_theta_2 = theta;
	return;
}

void omni_3wheel_control::set_cos_theta_2(float theta) {
	this->cos_theta_2 = theta;
	return;
}

void omni_3wheel_control::set_sin_theta_3(float theta) {
	this->sin_theta_3 = theta;
	return;
}

void omni_3wheel_control::set_cos_theta_3(float theta) {
	this->cos_theta_3 = theta;
	return;
}

void omni_3wheel_control::set_robot_range(float range) {
	this->robot_range = range;
	return;
}
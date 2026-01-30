#include "main.h"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include <cstdint>

using namespace pros;

Controller master(E_CONTROLLER_MASTER);
MotorGroup DriveL({-1, -3, -4});
MotorGroup DriveR({5, 6, 7});

Motor intake(11);
Motor stickMotor(19);

Rotation stickRotation(18);
Imu imu(20);

adi::DigitalOut doublePark('G');
adi::DigitalOut lift('H');
adi::DigitalOut hood('E');
adi::DigitalOut matchloader('D');
adi::DigitalOut descore('C');

void on_center_button() {}

void initialize() {
	lcd::initialize();
	stickRotation.reverse();
	stickRotation.reset_position();
	imu.reset();
	Task screenTask([]{
		while(true){
			lcd::set_text(1, "Stick Angle: " + std::to_string(stickRotation.get_position()/100));
			lcd::set_text(2, "IMU Heading: " + std::to_string(imu.get_heading()));
			pros::delay(10);
		}
	});
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

	bool doubleParkState = false;
	bool liftState = true;
	bool hoodState = true;
	bool matchloaderState = false;
	bool descoreState = false;

	int timeout = 0;

	lift.set_value(liftState);

	while (true) {

		if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
			if(liftState == false && stickRotation.get_position()/100 < 300){
				stickMotor.move_voltage(12000);
				hoodState = false;
			}
			else if(liftState == true && stickRotation.get_position()/100 < 300){
				stickMotor.move_voltage(12000);
				hoodState = false;
			}
			else{
				stickMotor.brake();
				stickMotor.move_voltage(0);
			}
		} else if(master.get_digital(DIGITAL_R1)){ 
			intake.move_voltage(12000);
		} else if(master.get_digital(DIGITAL_R2)){
			intake.move_voltage(-12000);
		} else {
			intake.move_voltage(0);
			hoodState = true;
			if (timeout < 700 && stickRotation.get_position()/100 > 10){
				timeout++;
				stickMotor.move_voltage(-6000);
			} else {
				stickMotor.brake();
				stickMotor.move_voltage(0);
				timeout = 0;
				if(stickRotation.get_position()/100 > 5){
					stickRotation.reset_position();
				}
			}
		}

		hood.set_value(hoodState);

		if(master.get_digital_new_press(DIGITAL_B)){
			doubleParkState = !doubleParkState;
			doublePark.set_value(doubleParkState);
		}

		if(master.get_digital_new_press(DIGITAL_A)){
			matchloaderState = !matchloaderState;
			matchloader.set_value(matchloaderState);
		}

		if(master.get_digital_new_press(DIGITAL_L2)){
			liftState = !liftState;
			lift.set_value(liftState);
		}

		if(liftState == true){
			descoreState = true;
		} else if (liftState == true && master.get_digital(DIGITAL_L1)){
			descoreState = false;
		} else if (liftState == false){
			descoreState = false;
		} else {
			descoreState = false;
		}

		descore.set_value(descoreState);

		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = -master.get_analog(ANALOG_RIGHT_X) * 0.7;  
		DriveL.move(dir - turn);  
		DriveR.move(dir + turn);   
	

		pros::delay(10); 
	}         
}
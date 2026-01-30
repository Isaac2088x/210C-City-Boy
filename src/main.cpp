#include "main.h"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

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
adi::DigitalOut matchloader('B');
adi::DigitalOut descore('C');

void on_center_button() {}

void initialize() {
	lcd::initialize();
	stickRotation.reverse();
	stickRotation.reset();
	imu.reset();
	Task screenTask([]{
		while(true){
			lcd::set_text(1, "Stick Angle: " + std::to_string(stickRotation.get_angle()));
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
	bool hoodState = false;
	bool matchloaderState = false;
	bool descoreState = false;

	lift.set_value(liftState);

	while (true) {


		if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2) && liftState == false && stickRotation.get_angle() > 32900){
			hoodState = true;
			stickMotor.move_voltage(12000);
		}else if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2) && liftState == true && stickRotation.get_angle() < 33000){
			hoodState = true;
			stickMotor.move_voltage(12000);
		} else if(master.get_digital(DIGITAL_R1)){
			intake.move_voltage(12000);
		}
		else if(master.get_digital(DIGITAL_R2)){
			hoodState = false;
			intake.move_voltage(-12000);
		}else{
			intake.move_voltage(0);
			if(stickRotation.get_angle() > 500){
				stickMotor.move_voltage(-12000);
			}else{
				stickMotor.move_voltage(0);
			}
		}

		hood.set_value(hoodState);

		if(master.get_digital_new_press(DIGITAL_L1)){
			doubleParkState = !doubleParkState;
			doublePark.set_value(doubleParkState);
		}

		if(master.get_digital_new_press(DIGITAL_L2)){
			liftState = !liftState;
			lift.set_value(liftState);
		}

		if(master.get_digital_new_press(DIGITAL_A)){
			matchloaderState = !matchloaderState;
			matchloader.set_value(matchloaderState);
		}

		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = -master.get_analog(ANALOG_RIGHT_X) * 0.7;  
		DriveL.move(dir - turn);  
		DriveR.move(dir + turn);   
	

		pros::delay(10); 
	}         
}

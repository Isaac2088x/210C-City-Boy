#include "main.h"
#include "pros/adi.hpp"
#include "pros/llemu.hpp"
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
adi::DigitalOut hood('A');
adi::DigitalOut matchloader('B');
adi::DigitalOut descore('C');

void on_center_button() {}

void initialize() {
	lcd::initialize();
	stickRotation.reset();
	imu.reset();
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

		

		if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
			intake.move(-127);
			hoodState = false;
		} else if(master.get_digital(DIGITAL_R1)){
			intake.move(127);
			hoodState = false;
		} else if(master.get_digital(DIGITAL_R2)){
			intake.move(127);
			hoodState = true;
			stickMotor.move_voltage(12000);
		} else {
			intake.move(0);
			if(stickRotation.get_angle() < 350) { 
                stickMotor.move_voltage(-4000);  
            } else {
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

#include "main.h"
#include "pros/adi.hpp"

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

void on_center_button() {}

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "EFN EFN EFN EFN");
	stickRotation.reset();
	imu.reset();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


void opcontrol() {

	bool doubleParkState = false;
	bool liftState = false;

	while (true) {

		if(master.get_digital(DIGITAL_R1)) {
			intake.move(127);
		} else if(master.get_digital(DIGITAL_R2)) {
			intake.move(-127);
		} else {
			intake.move(0);
		}

		if(master.get_digital(DIGITAL_L1)) {
			stickMotor.move(50);
		} 
		else if(master.get_digital(DIGITAL_L2)) {
			stickMotor.move(-50);
		} else {
			stickMotor.move(0);
		}

		if(master.get_digital_new_press(DIGITAL_A)){
			doubleParkState = !doubleParkState;
			doublePark.set_value(doubleParkState);
		}

		if(master.get_digital_new_press(DIGITAL_B)){
			liftState = !liftState;
			lift.set_value(liftState);
		}

		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = -master.get_analog(ANALOG_RIGHT_X) * 0.7;  
		DriveL.move(dir - turn);  
		DriveR.move(dir + turn);      
		pros::delay(10); 
	}         
}

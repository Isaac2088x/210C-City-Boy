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
adi::DigitalOut hood('A');
adi::DigitalOut matchloader('B');
adi::DigitalOut descore('C');

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
	bool hoodState = false;
	bool matchloaderState = false;
	bool descoreState = false;

	while (true) {

		if(master.get_digital(DIGITAL_R1)){
			intake.move(127);
			hoodState = false;
		} else if(master.get_digital(DIGITAL_R2)){
			intake.move(-127);
			hoodState = true;
		} else{
			intake.move(0);
			hoodState = false;
		}		


		if(hoodState == true){
			hood.set_value(true);
			while(stickRotation.get_angle() > 31){
				stickMotor.move(-50);
			}
			stickMotor.move(0);

		} else {
			hood.set_value(false);
		}

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

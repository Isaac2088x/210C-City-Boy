#include "main.h"
#include "globals.cpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"

using namespace pros;


void on_center_button() {}

void initialize() {
	lcd::initialize();
	StickRot.reverse();
	StickRot.reset_position();
	StickRot.reset();
	Lift.set_value(true);
	int setPoint = StickRot.get_angle();

	Task calibrateTask([]{
		chassis.calibrate();
	});

// 	Task screenTask([]{
// 		while(true){
// 			lcd::set_text(1, "Stick Angle: " + std::to_string(StickRot.get_position()/100));
// 			lcd::set_text(2, "IMU Heading: " + std::to_string(imu.get_heading()));
// 			lcd::set_text(3, "Velocity: " + std::to_string(StickRot.get_velocity()));
// 			pros::delay(10);
// 		}
// 	});
}

void disabled() {}

void competition_initialize() {}

int autonthing = 1;

void autonomous() {

	switch (autonthing) {
		case 0:
			chassis.moveToPoint(10, 33, 2000);
			delay(600);
			Match.set_value(true);
			chassis.turnToHeading(60, 1900);
			delay(100);
			Match.set_value(false);
			chassis.moveToPoint(31, 41, 1800);
			delay(300);
			Match.set_value(true);
			chassis.moveToPoint(16, 20, 3000, {.forwards = false});
			chassis.moveToPoint(34, 12, 5000);
			delay(200);
			Match.set_value(false);
			chassis.turnToHeading(180, 2000);
			delay(100);
			chassis.moveToPoint(34, 27, 1500, {.forwards = false});
			Hood.set_value(false);
			delay(300);
			Stick.move_voltage(12000);
			delay(500);
			Stick.move_voltage(-7000);
			delay(300);
			Stick.move_voltage(0);
			Match.set_value(true);
			chassis.moveToPoint(34, -9, 2000);
			delay(300);
			chassis.moveToPoint(34, 0, 2000);
			delay(300);
			Match.set_value(false);
			chassis.turnToHeading(310, 1500);
			chassis.moveToPoint(-6, 38, 2500);
			delay(800);
			Intake.move_voltage(-7000);
			delay(500);
			Wing.set_value(true);
			chassis.moveToPoint(23, 25, 2000, {.forwards = false});
			chassis.turnToHeading(180, 1500);
			delay(100);
			Wing.set_value(false);
			delay(200);
			chassis.moveToPoint(23, 34, 1500, {.forwards = false});
			break;

		case 1:

			break;

	}
	chassis.setPose(0,0,0);
	Lift.set_value(true);
	Hood.set_value(true);
	Intake.move_voltage(12000);

	




}

void opcontrol() {

	bool doubleParkState = false;
	bool LiftState = true;
	bool hoodState = true;
	bool matchloaderState = false;
	bool descoreState;

	int armTimeout = 0;

	Lift.set_value(LiftState);

	while (true) {

		if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
			if(LiftState == false && StickRot.get_position()/100 < 300){
				Intake.move_voltage(12000);
				Stick.move_voltage(12000);
				hoodState = false;
			}
			else if(LiftState == true && StickRot.get_position()/100 < 330){
				Intake.move_voltage(12000);
				Stick.move_voltage(12000);
				hoodState = false;
			}
			else{
				Stick.brake();
				Stick.move_voltage(0);
			}
		} else if(master.get_digital(DIGITAL_R1)){ 
			hoodState = true;
			Intake.move_voltage(12000);
		} else if(master.get_digital(DIGITAL_R2)){
			hoodState = true;
			Intake.move_voltage(-12000);
		} else {
			Intake.move_voltage(0);
			hoodState = true;

			if(abs(StickRot.get_velocity()) < 10) {
				Stick.move_voltage(0);
				StickRot.reset_position();
			} else if (StickRot.get_position()/100 > 20){
				Stick.move_velocity(-5000);
			} else {
				Stick.move_voltage(0);
			}

		}

		Hood.set_value(hoodState);

		if(master.get_digital_new_press(DIGITAL_B)){
			doubleParkState = !doubleParkState;
			Park.set_value(doubleParkState);
		}

		if(master.get_digital_new_press(DIGITAL_A)){
			matchloaderState = !matchloaderState;
			Match.set_value(matchloaderState);
		}

		if(master.get_digital_new_press(DIGITAL_L2)){
			LiftState = !LiftState;
			Lift.set_value(LiftState);
		}

		if (LiftState == true && master.get_digital(DIGITAL_L1)){
			descoreState = false;
		} else if(LiftState == true){
			descoreState = true;
		} else {
			descoreState = false;
		}

		Wing.set_value(descoreState);

		int dir = master.get_analog(ANALOG_LEFT_Y);    
		int turn = -master.get_analog(ANALOG_RIGHT_X) * 0.7;  
		DriveL.move(dir - turn);  
		DriveR.move(dir + turn);   
	

		pros::delay(10); 
	}         
}
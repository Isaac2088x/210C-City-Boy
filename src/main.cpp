#include "main.h"
#include "global.hpp"
#include "lemlib/api.hpp"
#include "auton.hpp"

void initialize() {
    pros::lcd::initialize();
	StickRot.reset_position();
	chassis.calibrate();

}

void on_center_button() {}

void disabled() {}

void competition_initialize() {}

int auton = 4;


void autonomous() {
	switch (auton) {
		case 0:
			None();
			break;
		case 1:
			OneInch();
			break;
		case 2:
			LeftGen();
			break;
		case 3:
			RightGen();
			break;
		case 4:
			LeftElim();
			break;
		case 5:
			SAWP();
			break;
	}
	return;
}

void opcontrol() {

	int button = 0;

	bool doubleParkState = false;
	bool LiftState = false;
	bool hoodState = true;
	bool matchloaderState = false;
	bool descoreState = false;

	Stick.move_voltage(0);
	chassis.cancelAllMotions();
	while (true) {

		button = FrontLimit.get_value();

		if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2)){
			if(LiftState == false && StickRot.get_position()/100 < 240){
				Intake.move_voltage(12000);
				Stick.move_voltage(12000);
				hoodState = true;
			}
			else if(LiftState == true && StickRot.get_position()/100 < 250){
				Intake.move_voltage(12000);
				Stick.move_voltage(12000);
				hoodState = true;
			}
			else{
				Stick.brake();
				Stick.move_voltage(0);
			}
		} else if(master.get_digital(DIGITAL_R1)){ 
			hoodState = false;
			Intake.move_voltage(12000);
		} else if(master.get_digital(DIGITAL_R2)){
			hoodState = false;
			Intake.move_voltage(-8400);
		} else if(button == 1){
			Stick.move_voltage(0);
			StickRot.reset_position();
		} else if(abs(StickRot.get_position())/100 > 30){
			Stick.move_voltage(-12000); 
		} else {
			Intake.move_voltage(0);
			hoodState = false;
			button = 0;
			Stick.move_voltage(0);
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

		if (LiftState == false && master.get_digital(DIGITAL_L1)){
			descoreState = false;
		} else if(LiftState == false){
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
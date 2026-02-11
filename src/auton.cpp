#include "main.h"
#include "auton.hpp"
#include "global.hpp"
#include "lemlib/api.hpp"

void None(){
    // None
    pros::delay(16000);
    return;
}
void OneInch(){
    // 1 inch
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, 6, 5000);
    pros::delay(16000);
	return;
}
void LeftGen(){
    // Left Genesis
	chassis.setPose(0, 0, 0);
    Intake.move_voltage(12000);
    chassis.moveToPoint(-7.286, 27.272, 1000, {.maxSpeed = 100});
	pros::delay(530);
	Match.set_value(true);
    chassis.turnToHeading(-135, 1000);
    chassis.moveToPoint(-36.875, 3.187, 1000, {.maxSpeed = 100});
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(-36.875, 24.7, 1000, {.forwards = false, .maxSpeed = 100});
    pros::delay(1300);
    Hood.set_value(true);
    Stick.move_voltage(12000);
    pros::delay(440);
    Stick.move_voltage(-8000);
	pros::delay(570);
    Stick.move_voltage(0);
    chassis.moveToPoint(-36.875, -11, 1500, {.maxSpeed = 90});
    pros::delay(580);
    Hood.set_value(false);
    chassis.moveToPoint(-36.875, 8, 1000, {.forwards = false, .maxSpeed = 90});
    pros::delay(600);
    Lift.set_value(true);
    chassis.turnToHeading(-135, 1000);
    chassis.moveToPoint(3, 39, 2000, {.forwards = false, .maxSpeed = 90});
    pros::delay(1300);
    Hood.set_value(true);
    Stick.move_voltage(8400);
    pros::delay(750);
    Stick.move_voltage(-6000);
    pros::delay(750);
    Stick.move_voltage(0);
    Match.set_value(false);
    // chassis.moveToPoint(-23, 17, 1000, {.maxSpeed = 90});
    // chassis.turnToHeading(0, 1000);
    // chassis.moveToPoint(-23, 41, 1000, {.maxSpeed = 90});
    return;
}
void RightGen(){
    // Right Genesis
    chassis.setPose(0,0,90);
    Intake.move_voltage(12000);

    chassis.moveToPoint(34, 0, 1500);
    chassis.turnToHeading(180, 1000);
    pros::delay(550);
    chassis.setPose(34, 0, 180);

    Match.set_value(true);
    pros::delay(350);
    chassis.moveToPoint(34, -15.7, 1000);
    pros::delay(400);
    chassis.moveToPoint(34, 25, 2000, {.forwards = false, .maxSpeed = 120});

    Hood.set_value(true);
    Match.set_value(false);
    pros::delay(900);
    Stick.move_voltage(12000);
    pros::delay(500);
    Stick.move_voltage(-8000);
    pros::delay(600);
    Stick.move_voltage(0);


    chassis.moveToPoint(34, 2, 1000);
    Hood.set_value(false);
    chassis.turnToHeading(-45, 1000);
    chassis.moveToPoint(8.902, 21.451, 3000, {.maxSpeed = 110});
    pros::delay(620);
    Match.set_value(true);
    pros::delay(400);
    Match.set_value(false);
    chassis.moveToPoint(-2, 31, 2000, {.maxSpeed = 100});
    Wing.set_value(true);
    pros::delay(800);
    Intake.move_voltage(-8400);
    pros::delay(1000);
    chassis.moveToPoint(20.5, 19.5, 1500, {.forwards = false, .maxSpeed = 90});
    chassis.turnToHeading(180, 1000);
    Wing.set_value(false);
    chassis.moveToPoint(20.5, 39, 1000, {.forwards = false});
    return;
}
void LeftElim(){
    // Left Eliminations
    pros::delay(50);
    chassis.setPose(0, 0, 0);
    Intake.move_voltage(12000);
    chassis.moveToPoint(-7.286, 27.272, 1000, {.maxSpeed = 110});
    pros::delay(530);

    Match.set_value(true);
    chassis.turnToHeading(-135, 800);
    chassis.moveToPoint(-35.4, 3.187, 1000, {.maxSpeed = 110});
    chassis.turnToHeading(180, 1000);
    pros::delay(600);
    chassis.setPose(-35.4, 3.187, 180);
    chassis.moveToPoint(-35.4, -7, 1100, {.maxSpeed = 110});
    pros::delay(600);
    // pros::delay(580);
    // Hood.set_value(false);

    chassis.moveToPoint(-36.1, 26, 1200, {.forwards = false, .maxSpeed = 110});
    pros::delay(1400);
    chassis.cancelAllMotions();
    DriveL.move_voltage(-5000);
    DriveR.move_voltage(-5000);
    Hood.set_value(true);

    Stick.move_voltage(12000);
    pros::delay(630);
    Stick.move_voltage(-12000);
    pros::delay(500);
    Stick.move_voltage(0);
    // pros::delay(200);
    // chassis.moveToPoint(-38, 14, 1000, {.minSpeed = 90});
    // pros::delay(400);

    Hood.set_value(false);
    // pros::delay(500);
    // chassis.cancelAllMotions();
    // pros::delay(500);
    // DriveL.move_voltage(-7000);
    // DriveR.move_voltage(-7000);
    // pros::delay(600);
    pros::delay(10000);
    return;
}
void SAWP(){
    // SAWP
    chassis.setPose(1.3, 0, -90);
    Lift.set_value(false);
    Hood.set_value(false);
    Intake.move_voltage(12000);
    chassis.moveToPoint(-10, 0, 400);
    chassis.moveToPoint(47.0, 0, 1400, {.forwards = false, .maxSpeed=110});
    pros::delay(650);
    Match.set_value(true);
    chassis.turnToHeading(177, 780);
    chassis.moveToPoint(47.5, -15.3, 900, {.maxSpeed=110});
    pros::delay(600);
    chassis.moveToPoint(47.5, 24, 1000, {.forwards = false, .maxSpeed=127});
    pros::delay(800);
    Intake.move_voltage(0);
    Hood.set_value(true);
    Stick.move_voltage(12000);
    pros::delay(430);
    Stick.move_voltage(-8000);
    pros::delay(500);
    Stick.move_voltage(0);
    Intake.move_voltage(12000);
    Match.set_value(false);
    chassis.moveToPoint(47.5, 16, 500, {.maxSpeed=110});
    chassis.swingToHeading(-70, lemlib::DriveSide::RIGHT, 800, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed=70 });
    pros::delay(200);
    Hood.set_value(false);
    chassis.moveToPoint(18, 27.5, 900, {.maxSpeed=110});
    pros::delay(300);
    Lift.set_value(true);
    chassis.moveToPoint(-32.6, 27.6, 900, {.maxSpeed=110});
    pros::delay(890);
    Match.set_value(true);
    Hood.set_value(true);
    chassis.moveToPoint(-15.4, 41.5, 900, {.forwards = false, .maxSpeed=110});
    chassis.turnToHeading(-135, 600, {.minSpeed=30});
    pros::delay(550);
    chassis.setPose(-15.4, 41.5, -135);

    Intake.move_voltage(0);
    Stick.move_voltage(9000);
    // Hood.set_value(true);
    pros::delay(600);
    
    Stick.move_voltage(-9000);
    pros::delay(600);

    Stick.move_voltage(0);
    
    Intake.move_voltage(12000);
    chassis.moveToPoint(-50.3, 10, 1000, {.maxSpeed=110, .minSpeed=30});
    pros::delay(400);
    Match.set_value(true);
    Hood.set_value(false);
    Lift.set_value(false);
    chassis.turnToHeading(180, 800);
    pros::delay(850);
    chassis.setPose(-50.3, 10, 180);
    chassis.moveToPoint(-50.7, -13, 1000, {.maxSpeed=110});
    pros::delay(750);
    Hood.set_value(true);
    chassis.moveToPoint(-50.7, 35, 1000, {.forwards = false, .maxSpeed=110});
    pros::delay(700);
    Intake.move_voltage(0);
    Stick.move_voltage(12000);
    pros::delay(400);
    
    Stick.move_voltage(-6000);
    pros::delay(500);
    Stick.move_voltage(0);
    return;
}
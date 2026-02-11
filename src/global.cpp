#include "main.h"
#include "global.hpp"
#include "lemlib/api.hpp" 

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup DriveL({-1, -3, -4});
pros::MotorGroup DriveR({5 , 6, 7});
pros::Motor Intake(11);
pros::Motor Stick(19);
pros::Rotation StickRot(18);
pros::Rotation V1(-12);
pros::Imu imu(20);
pros::adi::DigitalOut Match('D');
pros::adi::DigitalOut Hood('E');
pros::adi::DigitalOut Lift('H');
pros::adi::DigitalOut Wing('C');
pros::adi::DigitalOut Park('G');
pros::adi::DigitalIn FrontLimit('B');
lemlib::TrackingWheel Ver1(&V1, lemlib::Omniwheel::NEW_2, 0);

lemlib::Drivetrain drivetrain(&DriveL, // left motor group
                              &DriveR, // right motor group
                              11, // track width
                              lemlib::Omniwheel::NEW_325, // wheel size
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

lemlib::OdomSensors sensors(&Ver1, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::ControllerSettings lateral_controller(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              16, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(3.8, // proportional gain (kP)
                                              0.013, // integral gain (kI)
                                              27.2, // derivative gain (kD)
                                              4, // anti windup - 3
                                              0.8, // small error range, in degrees - 1
                                              100, // small error range timeout, in milliseconds
                                              1.9, // large error range, in degrees - 3
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew) - 0
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
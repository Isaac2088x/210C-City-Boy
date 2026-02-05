#pragma once
#include "lemlib/api.hpp" 

extern pros::Controller master;
extern pros::MotorGroup DriveL;
extern pros::MotorGroup DriveR;
extern pros::Motor Intake;
extern pros::Motor Stick;
extern pros::Rotation StickRot;
extern pros::Rotation V1;
extern pros::Imu imu;
extern pros::adi::DigitalOut Match;
extern pros::adi::DigitalOut Hood;
extern pros::adi::DigitalOut Lift;
extern pros::adi::DigitalOut Wing;
extern pros::adi::DigitalOut Park;
extern lemlib::TrackingWheel Ver1;


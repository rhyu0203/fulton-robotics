/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       syu                                                       */
/*    Created:      Fri Aug 16 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include<iostream>  

using namespace vex;
using namespace std; 

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

// define your global instances of motors and other devices here

vex::controller Controller1 = vex::controller(vex::controllerType::primary);

vex::motor FR = vex::motor(vex::PORT1);
vex::motor BR = vex::motor(vex::PORT2);
vex::motor FL = vex::motor(vex::PORT3);
vex::motor BL = vex::motor(vex::PORT4);

vex::motor Ramp = vex::motor(vex::PORT7);

vex::motor IntakeRight = vex::motor(vex::PORT5);
vex::motor IntakeLeft = vex::motor(vex::PORT6);

const int HIGH_GEAR = 5;
const int LOW_GEAR = 2;

double gear = HIGH_GEAR;

const int SPIN_UP = 1;
const int SPIN_STOP = 0;
const int SPIN_DOWN = -1;

void intakeSpin(int direction){
  if(direction == SPIN_UP){
    IntakeRight.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm);
    IntakeLeft.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm); 
  }
  else if(direction == SPIN_DOWN){
    IntakeRight.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
    IntakeLeft.spin(vex::directionType::rev, 200, vex::velocityUnits::rpm); 
  }
  else{
    IntakeRight.stop(vex::brakeType::brake);
    IntakeLeft.stop(vex::brakeType::brake); 
  }
}

const int RAMP_LOAD = 1;
const int RAMP_STOP = 0;
const int RAMP_UNLOAD = -1;

void moveRamp(int rampAction) {
  if (rampAction == RAMP_LOAD) {
    Ramp.spin(vex::directionType::rev, 10, vex::velocityUnits::rpm);
  } else if (rampAction == RAMP_UNLOAD) {
    Ramp.spin(vex::directionType::fwd, 10, vex::velocityUnits::rpm);
  } else {
    Ramp.stop(vex::brakeType::brake);
  }
}

void leftJoystickControl() {
  //FL.spin(directionType::fwd, ((Controller1.Axis4.value() + Controller1.Axis3.value())/2)*gear*50/127, velocityUnits::rpm);
  //FR.spin(directionType::fwd, ((Controller1.Axis4.value() - Controller1.Axis3.value())/2)*gear*50/127, velocityUnits::rpm);
  BL.spin(directionType::fwd, ((Controller1.Axis4.value() + Controller1.Axis3.value())/2)*gear*50/127, velocityUnits::rpm);
  BR.spin(directionType::fwd, ((Controller1.Axis4.value() - Controller1.Axis3.value())/2)*gear*50/127, velocityUnits::rpm);
  if(-10 < Controller1.Axis3.value() && Controller1.Axis3.value() < 10 && -10 < Controller1.Axis4.value() && Controller1.Axis4.value() < 10){
    //FR.stop(vex::brakeType::brake);            
    BR.stop(vex::brakeType::brake);
    //FL.stop(vex::brakeType::brake);
    BL.stop(vex::brakeType::brake);
  }
}

int main() { 
  while(true) {
    if(Controller1.ButtonR1.pressing()) {
      intakeSpin(SPIN_UP);
    }
    else if(Controller1.ButtonR2.pressing()){
      intakeSpin(SPIN_DOWN); 
    }
    else {
      intakeSpin(SPIN_STOP);
    }
    
    if(Controller1.ButtonL1.pressing()) {
      moveRamp(RAMP_LOAD);
      //Ramp.spin(vex::directionType::rev, 2, vex::velocityUnits::rpm);
    }
    else if(Controller1.ButtonL2.pressing()){
      moveRamp(RAMP_UNLOAD);
      //Ramp.spin(vex::directionType::fwd, 2, vex::velocityUnits::rpm);
    }
    else {
      moveRamp(RAMP_STOP);
      //Ramp.stop(vex::brakeType::brake);
    }
    leftJoystickControl();
    if(Controller1.ButtonX.pressing()) {
      gear = HIGH_GEAR;
    }
    if(Controller1.ButtonB.pressing()) {
      gear = LOW_GEAR;
    }
  }
}

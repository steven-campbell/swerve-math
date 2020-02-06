#ifndef SWERVE_HPP
#define SWERVE_HPP

#include <cmath>

double convertAngle(double angle, double currentEncoderValue);
double convertAngleOld(double angle, double encoderValue);

double modPos(double in, int m);
double changeAngleZone(double inputAngle);
#endif

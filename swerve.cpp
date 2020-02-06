#include "swerve.hpp"

#define INTRINSIC_ENCTICKS_ONEROT 7
#define GEAR_RATIO 59.1666666
//#define ENCODER_TICKS_ONE_ROTATION INTRINSIC_ENCTICKS_ONEROT * GEAR_RATIO
#define ENCODER_TICKS_ONE_ROTATION 360

double convertAngle(double angle, double currentEncoderPosition) {
	double encPos = modPos(currentEncoderPosition, ENCODER_TICKS_ONE_ROTATION);
	//double encPos = currentEncoderPosition % ENCODER_TICKS_ONE_ROTATION;
	double currAngle = encPos / ENCODER_TICKS_ONE_ROTATION;
	double targAngle = angle / 360.;

	double output = currentEncoderPosition;
	double offset = std::fmin(std::abs(targAngle-currAngle), 1-std::abs(targAngle-currAngle));
	offset *= ENCODER_TICKS_ONE_ROTATION;

	//if((targAngle - currAngle + 1) % 1. < 0.5) {
	if(std::fmod(targAngle - currAngle + 1, 1) < 0.5) {
		output += offset;
	} else {
		output -= offset;
	}

	return output;
}

double convertAngleOld(double angle, double encoderValue) {
	double encPos = encoderValue / ENCODER_TICKS_ONE_ROTATION;
	double temp = angle;
	temp += (int) encPos;

	//encPos %= encPos;
	encPos = std::fmod(encPos, encPos);

	if((angle - encPos) > 0.5) temp -= 1;
	if((angle - encPos) < -0.5) temp += 1;

	return temp;

}

double modPos(double in, int m) {
	int mod = std::fmod(in, (int) m);
	if(in < 0) {
		mod += m;
	}
	return mod;
}

double changeAngleZone(double inputAngle) {
	return inputAngle < 0 ? inputAngle + 360 : inputAngle;
}

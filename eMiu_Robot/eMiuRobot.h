// eMiuRobot.h

#ifndef _EMIUROBOT_h
#define _EMIUROBOT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Servo.h"

enum Direction
{
	FORWARD = 0,
	BACKWARD,
	LEFT,
	RIGHT
};

class EMiuRobotClass
{
 public:
	void InitMotor(uint8_t enAPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t in3Pin, uint8_t in4Pin, uint8_t enBPin);
	void InitSonicSensor(uint8_t trigerPin, uint8_t echoPin, uint16_t maxDistance);
	void InitServo(uint8_t handServoPin, uint8_t sensorServoPin);

	void SetLeftMotorSpeed(int16_t speed);
	void SetRightMotorSpeed(int16_t speed);
	void SetTwoMotorSpeed(int16_t speed);
	void SetSensorRotation(uint8_t angle);
	void SetHandRotation(uint8_t angle);

	float ReadSonicSensor();
	float ReadContinuouslySonicSensor();

private:
	uint8_t mEnAPin;
	uint8_t mIn1Pin; 
	uint8_t mIn2Pin;
	uint8_t mIn3Pin;
	uint8_t mIn4Pin;
	uint8_t mEnBPin;

	uint8_t mTrigerPin;
	uint8_t mEchoPin;
	uint16_t mSensorTimeout;

	uint8_t mhandServoPin;
	uint8_t msensorServoPin;

	uint8_t mLeftMotorSpeed;
	uint8_t mRightMotorSpeed;
	uint8_t mHandAngle;
	uint8_t mSensorAngle;

	Servo mSensorServo;
	Servo mHandServo;

	void setDirection(Direction motorPosition, uint8_t direction);

};

extern EMiuRobotClass EMiuRobot;

#endif


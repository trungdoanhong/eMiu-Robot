#include "eMiuRobot.h"

void EMiuRobotClass::InitMotor(uint8_t enAPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t in3Pin, uint8_t in4Pin, uint8_t enBPin)
{
	mEnAPin = enAPin;
	mIn1Pin = in1Pin;
	mIn2Pin = in2Pin;
	mIn3Pin = in3Pin;
	mIn4Pin = in4Pin;
	mEnBPin = enBPin;

	pinMode(mEnAPin, OUTPUT);
	pinMode(mIn1Pin, OUTPUT);
	pinMode(mIn2Pin, OUTPUT);
	pinMode(mIn3Pin, OUTPUT);
	pinMode(mIn4Pin, OUTPUT);
	pinMode(mEnBPin, OUTPUT);

	setDirection(LEFT, FORWARD);
	setDirection(RIGHT, FORWARD);
	SetTwoMotorSpeed(0);
}

void EMiuRobotClass::InitSonicSensor(uint8_t trigerPin, uint8_t echoPin, uint16_t maxDistance = 200)
{
	mTrigerPin = trigerPin;
	mEchoPin = echoPin;

	mSensorTimeout = maxDistance * 2 * 29.1 + 1;

	pinMode(mTrigerPin, OUTPUT);
	pinMode(mEchoPin, INPUT_PULLUP);
}

void EMiuRobotClass::InitServo(uint8_t handServoPin, uint8_t sensorServoPin)
{
	mSensorServo.attach(sensorServoPin);
	mHandServo.attach(handServoPin);

}

void EMiuRobotClass::SetLeftMotorSpeed(int16_t speed)
{
	speed = constrain(speed, -255, 255);

	if (speed >= 0)
	{
		setDirection(LEFT, FORWARD);
	}
	else
	{
		setDirection(LEFT, BACKWARD);
	}

	speed = abs(speed);

	analogWrite(mEnBPin, speed);

}
void EMiuRobotClass::SetRightMotorSpeed(int16_t speed)
{
	speed = constrain(speed, -255, 255);

	if (speed >= 0)
	{
		setDirection(RIGHT, FORWARD);
	}
	else
	{
		setDirection(RIGHT, BACKWARD);
	}

	speed = abs(speed);

	analogWrite(mEnAPin, speed);

}
void EMiuRobotClass::SetSensorRotation(uint8_t angle)
{
	angle = constrain(angle, 0, 180);
	mSensorServo.write(angle);

}
void EMiuRobotClass::SetHandRotation(uint8_t angle)
{
	angle = constrain(angle, 0, 180);
	mHandServo.write(angle);
}
void EMiuRobotClass::SetTwoMotorSpeed(int16_t speed)
{
	SetRightMotorSpeed(speed);
	SetLeftMotorSpeed(speed);

}

void EMiuRobotClass::setDirection(Direction motorPosition, uint8_t direction)
{ 
	uint8_t dirPin1 = mIn1Pin;
	uint8_t dirPin2 = mIn2Pin;

	if (motorPosition == LEFT)
	{
		dirPin1 = mIn3Pin;
		dirPin2 = mIn4Pin;
	}

	if (direction == FORWARD)
	{
		digitalWrite(dirPin1, HIGH);
		digitalWrite(dirPin2, LOW);
	}
	else
	{
		digitalWrite(dirPin1, LOW);
		digitalWrite(dirPin2, HIGH);
	}
}

float EMiuRobotClass::ReadSonicSensor()
{
	long duration, distanceCm;

	digitalWrite(mTrigerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(mTrigerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(mTrigerPin, LOW);

	duration = pulseIn(mEchoPin, HIGH, mSensorTimeout); 

	distanceCm = duration / 29.1 / 2;

	return distanceCm;
}

EMiuRobotClass EMiuRobot;


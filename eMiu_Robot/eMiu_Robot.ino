#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#include "eMiuRobot.h"
#include "SerialCommand.h"
#include "MultiThread.h"

#define EN1		5
#define IN1		11
#define IN2		12
#define IN3		A1
#define IN4		A0
#define EN2		6

#define TRIGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 300

#define HAND_SERVO_PIN 7
#define SENSOR_SERVO_PIN 8

float PitchAngle;
float RollAngle;
float YawAngle;
float OffsetBalanceAngle;
float BalanceAngle = 8;

float KP = 2;
float KI;
float KD;
float OffsetOutputSpeed = 30;

#include "RobotMPUSensor.h"

SerialCommand SerialCMD;

float LeftMotorSpeed = 0;
float RightMotorSpeed = 0;
float SensorAngle = 90;
float HandAngle = 120;
float SpeedOffset = 0;

MultiThread UltrasonicThread = MultiThread();
MultiThread GyroThread = MultiThread();

void setup()
{
	SerialCMD = SerialCommand(&Serial, 9600);
	SerialCMD.AddCommand("ls", &LeftMotorSpeed);
	SerialCMD.AddCommand("rs", &RightMotorSpeed);
	SerialCMD.AddCommand("ha", &HandAngle);
	SerialCMD.AddCommand("sa", &SensorAngle);
	SerialCMD.AddCommand("ss", SetSpeed);
	SerialCMD.AddCommand("seta", SetAngle);

	InitMPU();

	EMiuRobot.InitMotor(EN1, IN1, IN2, IN3, IN4, EN2);
	EMiuRobot.InitSonicSensor(TRIGER_PIN, ECHO_PIN, MAX_DISTANCE);
	EMiuRobot.InitServo(HAND_SERVO_PIN, SENSOR_SERVO_PIN);

	SetAngle();
}

void loop()
{
	SerialCMD.Execute();
	SendGyroValue();
	SendObstacleDistance();
}

void SetSpeed()
{
	EMiuRobot.SetLeftMotorSpeed(LeftMotorSpeed + SpeedOffset);
	EMiuRobot.SetRightMotorSpeed(RightMotorSpeed);
}

void SetAngle()
{
	EMiuRobot.SetHandRotation(HandAngle);
	EMiuRobot.SetSensorRotation(SensorAngle);
}

void SendObstacleDistance()
{
	RUN_EVERY(UltrasonicThread, 500)

	Serial.println(String("D") + EMiuRobot.ReadSonicSensor());
}

void SendGyroValue()
{
	RUN_EVERY(GyroThread, 100)
	ReadGyroValue(&YawAngle, &PitchAngle, &RollAngle);
	Serial.println(String("Y") + YawAngle);
	Serial.println(String("P") + PitchAngle);
	Serial.println(String("R") + RollAngle);
}
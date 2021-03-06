#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotentiometerLeft, sensorPotentiometer)
#pragma config(Sensor, in2,    armPotentiometerRight, sensorPotentiometer)
#pragma config(Sensor, in3,    GyroDown,       sensorNone)
#pragma config(Sensor, in5,    CubeIntakePotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl7,  SonarSensor,    sensorSONAR_mm)
#pragma config(Sensor, dgtl11, Jumper1,        sensorDigitalIn)
#pragma config(Sensor, dgtl12, Jumper2,        sensorDigitalIn)
#pragma config(Sensor, I2C_1,  FrontLeftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  FrontRightEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  RightLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  LeftLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           CrayonIntake,  tmotorVex393, openLoop)
#pragma config(Motor,  port2,           FrontLeft,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port3,           FrontRight,    tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port4,           BackRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           BackLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port6,           RightLift1,    tmotorVex393, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port7,           RightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           LeftLift1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           LeftLift2,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port10,          CubeIntake,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//int gyrotestval;
//int jumper1testval;
//int jumper2testval;

//int filterjoystick (int joystick);

int DefaultLeftValue = 0;
int DefaultRightValue = 0;

////////////////////////////////////////////////////
/// Autonomous mode - Not using
void Claw(int power);
void GyroRotateAndReadyCube(int angle);
void GyroRotateToInitialPosition(int power);
void GyroRotate(int angle);
bool PickUpCube(int value,int power);
void ReleaseCube(int value,int power);

////////////////////////////////////////////////////
/// Autonomous mode - Using
void SonarRotate(int distance, int power);
void StopMoving();
void EncoderRotate(int power);
void EncoderLiftUp(int power, int leftTarget, int rightTarget);
void EncoderLiftDown(int power, int leftTarget, int rightTarget);
void PickUpSkyrise(int duration);
void ReleaseSkyrise(int duration);
void StopLift();
void AdjustAutoLiftUp();
int AdjustBatteryLevel(int OriginalPower);

////////////////////////////////////////////////////
/// Drive mode
int LiftAdjust(int thisP, int otherP);
int GetLeftPower(float leftPot, float rightPot);
int GetRightPower(float leftPot, float rightPot);

int ReverseIfNeeded(int power);

float GetLeftValue();
float GetRightValue();
void AdjustLift();

bool MovingForward = true;
////////////////////////////////////////////////////
/*
typedef struct {
	int Left;
	int Right;
} HeightValuePair;

HeightValuePair heightValuePairs[8];
*/

typedef enumWord {
    Adjusted = 0,
		Up = 1,
    Down = 2
} ACTIONS;

ACTIONS PreviousAction;

/////////////////////////////////////////////////////////////////////////////////////////
//																																										 //
//                          Pre-Autonomous Functions																	 //
//																																										 //
// You may want to perform some actions before the competition starts. Do them in the	 //
// following function.																																 //
//																																										 //
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  //bStopTasksBetweenModes = true;

	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
 	SensorType[GyroDown] = sensorNone;
//	SensorType[GyroUp] = sensorNone;

	// SensorType[SonarSensor] = sensorNone;


 	wait1Msec(1000);
 	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 	SensorType[GyroDown] = sensorGyro;
// 	SensorType[GyroUp] = sensorGyro;
	//SensorType[SonarSensor] = sensorSONAR_mm;

 	wait1Msec(1000);



/*
	heightValuePairs[0].Left = 1556;
	heightValuePairs[0].Right = 1618;
	heightValuePairs[1].Left = 1556;
	heightValuePairs[1].Right = 1618;
	heightValuePairs[2].Left = 2062;
	heightValuePairs[2].Right = 2128;
	heightValuePairs[3].Left = 2135;
	heightValuePairs[3].Right = 2185;
	heightValuePairs[4].Left = 2308;
	heightValuePairs[4].Right = 2356;
	heightValuePairs[5].Left = 2613;
	heightValuePairs[5].Right = 2645;
	heightValuePairs[6].Left = 2997;
	heightValuePairs[6].Right = 2997;

	heightValuePairs[7].Left = 3428;
	heightValuePairs[7].Right = 3488;
*/

	// = new HEIGHTVALUEPAIR[]( {10,20}, {20,30} );

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																																														//
//                                 Autonomous Task																						//
//																																														//
// This task is used to control your robot during the autonomous phase of a VEX Competition.	//
// You must modify the code to add your own robot specific commands here.											//
//																																														//
////////////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
		ClearTimer(T3);

		int sshortDelay = 25;
		int shortDelay = 50;
		int defaultDelay = 100;
		int offset = 150;
						// pick up skyrise
		for (int i = 0; i <= 6; i++)
		{
			PickUpSkyrise(700);
			wait1Msec (defaultDelay);
	
			nMotorEncoder(LeftLift2) = 0;
			nMotorEncoder(RightLift1) = 0;
	
				
			switch (i)
			{
				case 0:
				case 1:
				case 2: offset = 150; break;
				case 3: offset = 300; break;
				case 4: offset = 400; break;
				case 5: offset = 520; break;
				case 6: offset = 680; break;
			}
			
			
			int left = -1550 - (offset * i);
			int right = -1550 - (offset * i);
			
			EncoderLiftUp(-127, left, right); // Lift up
	 		wait1Msec(defaultDelay);
	
			nMotorEncoder(FrontRight) = 0;
			nMotorEncoder(FrontLeft) = 0;
	
			// rotate to the skyrise base
			int sonarRotationOriginalPower = 48;
			int sonarRotationPower = AdjustBatteryLevel(sonarRotationOriginalPower);
			SonarRotate(300, sonarRotationPower);
			wait1Msec (defaultDelay);

			
	
			// EncoderLiftDown(70, -750 * i , -750 * i); //Lift down
			
			int heightToDrop = 120;
			if (0==i)
			{
				left = 0;
				right = 0;
				heightToDrop = 0;
			}
			else if (1 == i)
			{
				heightToDrop = 200;
			}
			
			EncoderLiftDown(50, left + heightToDrop , right + heightToDrop); //Lift down
			
			wait1Msec (defaultDelay);
	
			ReleaseSkyrise(500);
			writeDebugStreamLine("T3 - %d: %d	", i, time1[T3]);

			wait1Msec(shortDelay);
	
			EncoderLiftDown(60, 0, 0); //Lift down
			wait1Msec(sshortDelay);
	
	//		gyroRotationAngle = SensorValue[GyroDown];
	
	
	
			// rotate to the autoload
			int gyroRotationOriginalPower = 43;
			int gyroRotationPower = AdjustBatteryLevel(gyroRotationOriginalPower);
	
			EncoderRotate(gyroRotationPower);
//			wait1Msec(defaultDelay);
	
		}
		
		
		// GyroRotateToInitialPosition(gyroRotationPower);


		/*
		while(nMotorEncoder[FrontLeft] < 10)
		{
		  motor[FrontLeft] = WantedPower;
			motor[FrontRight] = WantedPower;
			motor[BackRight] = WantedPower;
			motor[BackLeft] = WantedPower;
		}
		*/
		//////////////////////
		/// RED RED RED RED RED
		/// RED RED RED RED RED
		/// RED RED RED RED RED
		//////////////////////

		//////////////////////
		/// BLUE BLUE BLUE BLUE BLUE
		/// BLUE BLUE BLUE BLUE BLUE
		/// BLUE BLUE BLUE BLUE BLUE
		//////////////////////

		/*if (SensorValue[Jumper1] == 1)
		{ // Initialize for Blue
			isBlue = true;

			initialmoveLeftDistance = 30;
			initialmoveDiagonalDistance = 230;
			initialForwardDistance = 0;

			initialGyroRotate = 395;
			defaultGyroRotate = -755;

			iteration_defaultGyroRotate = -705;
			finalMove = 50;
		}
		//////////////////////
		/// BLUE BLUE BLUE BLUE BLUE
		/// BLUE BLUE BLUE BLUE BLUE
		/// BLUE BLUE BLUE BLUE BLUE
		//////////////////////


		if (SensorValue[Jumper2] == 1) //run the first autonomous
		{
				// move Diagonal to put the cube
				// was 130
				MoveDiagonal(defaultMovePower, initialmoveDiagonalDistance);
				wait1Msec (defaultDelay);

//				MoveDiagonalReverse(-valM, 20);

				// move forward to the autoload
				// -33 for BLUE

				if (SensorValue[Jumper1] == 0)
				{ // need only for RED
					LeftRight(-defaultMovePower, -initialmoveLeftDistance);
					wait1Msec (defaultDelay);
				}
				else
				{
					ForBack(-defaultMovePower, initialForwardDistance);
					wait1Msec (defaultDelay);
				}

				// LeftRight(valM, 1);
				// wait1Msec (defaultDelay);

				// rotate to face the autoload
				// 330 for BLUE
				GyroRotate(initialGyroRotate);

				wait1Msec (defaultDelay);

				// move forward to the autoload
				// -33 for BLUE

				// pick up skyrise
				PickUpSkyrise(800);
				wait1Msec (defaultDelay);

				// Lift up
				int moveUpTo = 420;
				int savedLeftValue = SensorValue[armPotentiometerLeft];
 				int savedRightValue = SensorValue[armPotentiometerRight];
				LiftUp(false, -127, savedLeftValue + moveUpTo, savedRightValue + moveUpTo); // Lift up
				// LiftUpAndCloseCubeIntake(-127, savedLeftValue + moveUpTo, savedRightValue + moveUpTo); // Lift up
 				wait1Msec(defaultDelay);

				// rotate to the skyrise base
				GyroRotate(defaultGyroRotate);

				wait1Msec(defaultDelay);
				motor[CubeIntake] = 0;

				// lift down to the base
				LiftDown(false, 127, savedLeftValue, savedRightValue); //Lift our 	robot down
				wait1Msec(defaultDelay);

				ReleaseSkyrise(550);
				// wait1Msec(defaultDelay);


				writeDebugStream("T3 - 0: %d	", time1[T3]);

				//////////////////////////////////////////////////////////////
				///2nd round
				//////////////////////////////////////////////////////////////
				// Need to increase for programming skill
				bool programmingSkill = false;
				int iteration_index = 1;
				int iteration_Height = 50;
				int iteration_ReleaseDuration = 50;
				bool adjustNeeded = false;

				if (programmingSkill)
				{
					iteration_index = 5;
					iteration_Height = 50;
					iteration_ReleaseDuration = 550;
					defaultDelay = defaultDelay * 2;
				}

				for (int i = 1; i <= iteration_index; i++) // MULTI
				{
					GyroRotate(-iteration_defaultGyroRotate);
					wait1Msec (defaultDelay);

					PickUpSkyrise(800);
					wait1Msec (defaultDelay);
					// wait1Msec(500);

					// Need to increase for programming skill
					// multiple
					int differenceMoveUp = moveUpTo + (iteration_Height * i);
					int leftHeight = savedLeftValue + differenceMoveUp;
					int rightHeight = savedRightValue + differenceMoveUp;

					if (programmingSkill && i > 1)
					{
						leftHeight = heightValuePairs[i].Left;
						rightHeight = heightValuePairs[i].Right;
						adjustNeeded = true;
					}

					LiftUp(adjustNeeded, -127, leftHeight, rightHeight); //Lift up
					wait1Msec(defaultDelay);
					GyroRotate(iteration_defaultGyroRotate);


					// rotate to the skyrise base


					wait1Msec(defaultDelay * 3);
// adding
					ForBack(-finalMove, 30);
// adding

					LiftDown(false, 30, leftHeight - 170, rightHeight - 170); //Lower our 	robot down
					wait1Msec(defaultDelay);

					// Need to increase for programming skill
					// 550
					ReleaseSkyrise(iteration_ReleaseDuration);

					// Lower down to the base
					LiftDown(false, 127, savedLeftValue, savedRightValue); //Lift our 	robot down

					writeDebugStreamLine("T3 - %d: %d	", i, time1[T3]);
					wait1Msec(defaultDelay);
				}
		}*/


}

int AdjustBatteryLevel(int OriginalPower)
{
	float AdjustBatteryLevel = nImmediateBatteryLevel;
  float BatteryOffset =	6000 / AdjustBatteryLevel;
  int WantedPower = OriginalPower * BatteryOffset;


	writeDebugStreamLine("(AjustBattery) BatterLevel: %d - OriginalPower: %d - WantedPower: %d", AdjustBatteryLevel, OriginalPower, WantedPower);


  return WantedPower;
}


void EncoderLiftUp(int power, int leftTarget, int rightTarget)
{
	while(nMotorEncoder(LeftLift2) > leftTarget
				|| nMotorEncoder(RightLift1) > rightTarget)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

//			writeDebugStreamLine("(LiftUp) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();
		wait1Msec(100);
		
		AdjustAutoLiftUp();
}

void EncoderLiftDown(int power, int leftTarget, int rightTarget)
{
	while(nMotorEncoder(LeftLift2) < leftTarget
				|| nMotorEncoder(RightLift1) < rightTarget)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();
}

bool PickUpCube(int value,int power) //pick cube up and stuff
{
	  ClearTimer(T2);
		if (SensorValue[CubeIntakePotentiometer] >= value || SensorValue[CubeIntakePotentiometer] < 300)
		{
			return true;
		}

		while(SensorValue[CubeIntakePotentiometer] < value)
		{
		    motor[CubeIntake] = -power;
		    if (time1[T2] > 1000)
		    {
		    	motor[CubeIntake] = 0;
		    	return false;
		    }
		}

		motor[CubeIntake] = 0;
		return true;
}

void ReleaseCube(int value,int power)
{
		if (SensorValue[CubeIntakePotentiometer] <= value)
		{
			return;
		}

		while(SensorValue[CubeIntakePotentiometer] > value)
		{
		    motor[CubeIntake] = power;
		}

		motor[CubeIntake] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//																																														 //
//                                 User Control Task																					 //
//																																														 //
// This task is used to control your robot during the user control phase of a VEX Competition. //
// You must modify the code to add your own robot specific commands here.											 //
//																																														 //
/////////////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	bool armPotentiometerUsed = true;

	bool cubeIntakeClosing = false;
	bool crayonIntakeClosing = false;

  const int power7 = 50;
	 //DefaultLeftValue = SensorValue[armPotentiometerLeft];
	 //DefaultRightValue = SensorValue[armPotentiometerRight];

	// DefaultLeftValue = 1864;
	// DefaultRightValue = 1902;
  DefaultLeftValue = 1700;
	DefaultRightValue = 1753;

	while (true)
	{
		 ClearTimer(T2);
		 while (time1[T2] < 100){}

     // reverse when moving backward
     if (vexRT[Btn7U] == 1)
     {
 //      StopMoving();
       MovingForward = true;
     }
     else if(vexRT[Btn7D] == 1)
     {
   //    StopMoving();
       MovingForward = false;
     }


     int filtered2 = vexRT[Ch2];
     int filtered4 = vexRT[Ch4];


     // writeDebugStream("wheels: %d ->	", filtered2);

     if (SensorValue[armPotentiometerLeft] > 2800 || SensorValue[armPotentiometerRight] > 2800)
		 {
		  	filtered2 = 0;
		 }/*
		 else if (SensorValue[armPotentiometerLeft] > 2890 || SensorValue[armPotentiometerRight] > 2910)
		 {
		  	filtered2 = filtered2 / 3;
		 }*/
     else if (SensorValue[armPotentiometerLeft] > 2230 || SensorValue[armPotentiometerRight] > 2270)
		 {
		  	filtered2 = filtered2 / 2;
		 }



		 writeDebugStreamLine("%d	", filtered2);




		// Button7
    filtered2 = ReverseIfNeeded(filtered2);
        // filtered4 = ReverseIfNeeded(filtered4);
    int power7r = ReverseIfNeeded(power7);

    int btn7r = vexRT[Btn7R];
    int btn7l = vexRT[Btn7L];

		//standard drive motor block
		motor[FrontLeft] = filtered2 + filtered4 + btn7r * power7r - btn7l * power7r;
		motor[FrontRight] = filtered2 - filtered4 - btn7r * power7r + btn7l * power7r;
		motor[BackRight] = filtered2 - filtered4 + btn7r * power7r - btn7l * power7r;
		motor[BackLeft] = filtered2 + filtered4 - btn7r * power7r + btn7l * power7r;

		float leftPot = GetLeftValue();
  	float rightPot = GetRightValue();

  	if (leftPot <= 0 || rightPot <= 0)
  	{
			armPotentiometerUsed = false;
		}
		else
		{
			armPotentiometerUsed = true;
		}

		int lp = 127;
		int rp = 127;

		if (armPotentiometerUsed == true)
		{
			lp = GetLeftPower(leftPot, rightPot);
			rp = GetRightPower(leftPot, rightPot);
		}

		if (lp != 0 && rp != 0)
		{
		    writeDebugStream("lp: %d	", lp);
		    writeDebugStreamLine("rp: %d", rp);
	    }


	  int btn8r = vexRT[Btn8R];
	  int btn8l = vexRT[Btn8L];

	  int btn8d = vexRT[Btn8D];
	  int btn8u = vexRT[Btn8U];

	  /*
    if (btn8r + btn8l > 0)
    {
			SensorValue[GyroUp] = 0;
    }
    */


    /*
    if (btn8d + btn8u > 0)
    {

    	if (SensorValue[CubeIntakePotentiometer] > 930)
			{
				if (!PickUpCube(2600, 127))
				{
					btn8d = btn8u = 0;
				}
			}
    }
		*/

	  // lp = 127;
	  // rp = 127;

	  // int temp = lp;
	  // lp = rp;
	  // rp = temp;
		motor[LeftLift1] =  (btn8d - btn8u) * lp + btn8l * 25 - btn8r * 25;
		motor[LeftLift2] =  (btn8d - btn8u) * lp + btn8l * 25 - btn8r * 25;
		motor[RightLift1] = (btn8d - btn8u) * rp + btn8r * 25 - btn8l * 25;
		motor[RightLift2] = (btn8d - btn8u) * rp + btn8r * 25 - btn8l * 25;


    if (btn8d + btn8u + btn8r + btn8l == 0)
    {
    	 lp = 0;
			 rp = 0;

				motor[LeftLift1] = motor[LeftLift2] = lp;
				motor[RightLift1] = motor[RightLift2] = rp;
	}

        // adjust when we stops
		if (armPotentiometerUsed == true)
		{
			// AdjustLift();
		}


		int btn5u = vexRT[Btn5U];
		int btn5d = vexRT[Btn5D];

		if (btn5u == 1)
		{
			cubeIntakeClosing = false;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5d == 1)
		{
			cubeIntakeClosing = true;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5u == 0 && btn5d == 0 && cubeIntakeClosing)
		{
				motor[CubeIntake] = -20;
		}
		else if (btn5u == 0 && btn5d == 0 && !cubeIntakeClosing)
		{
				motor[CubeIntake] = 0;
		}


		int btn6u = vexRT[Btn6U];
		int btn6d = vexRT[Btn6D];

		if (btn6d == 1)
		{
			crayonIntakeClosing = false;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 1)
		{
			crayonIntakeClosing = true;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 0 && btn6d == 0 && crayonIntakeClosing)
		{
				motor[CrayonIntake] = 25;
		}
		else if (btn6u == 0 && btn6d == 0 && !crayonIntakeClosing)
		{
				motor[CrayonIntake] = 0;
		}
	}
}

int ReverseIfNeeded(int power)
{
    return MovingForward ? power : -power;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// GetValues
/// Get Potentiometer values
/////////////////////////////////////////////////////////////////////////////////////////////
float GetLeftValue()
{
	int sValue = SensorValue[armPotentiometerLeft];
	float value = (sValue * 1) - DefaultLeftValue;
	if (value <0) value = 0;

		return value;
}

float GetRightValue()
{
		int sValue = SensorValue[armPotentiometerRight];
		float value =  sValue - DefaultRightValue;
		if (value <0) value = 0;

		return value;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// GetPowers
/// Calculate the power for lifts based on the sensor values and the current actions
/////////////////////////////////////////////////////////////////////////////////////////////
int GetLeftPower(float leftPot, float rightPot)
{
	const int fullPower = 127;
	const int fullPower_Down = 100;
	const float delta = 0.6;
	const float delta_Down = 0.6;

    // No buttons pressed
	if (vexRT[Btn8D] == 0 && vexRT[Btn8U] == 0) return 0;

    // On moving up
    if (vexRT[Btn8U] == 1)
	{
		  if (SensorValue[armPotentiometerLeft] > 3550)
		  {
		  	return 0;
		  }
        // moving up
        PreviousAction = Up;

        // if we just started moving, we need full power.
		if (leftPot <= 300)
		{
			return fullPower;
		}

        // when the right lift is higher, we need full power for the left
		if (leftPot <= rightPot)
		{
			return fullPower;
		}
		else
		{
            // when the left is higher, we need to slow down the left
            // the delta is a magic number. we need even less power for left while the other one is catching up
			float offset = (rightPot / leftPot) * 100 * delta;
			int power = (fullPower * offset) / 100;
			return power;
		}
	}
    // On moving down
	else if (vexRT[Btn8D] == 1)
	{
        // moving down
        PreviousAction = Down;

        // if the current is higher than the other, need full power. but we still don't need 127.
		if (leftPot >= rightPot)
		{
			if (leftPot <= 400)
			{
				// need to slow down?;
				// return fullPower_Down * 0.3;
			}
			return fullPower_Down;
		}
		else
		{
			float offset = (leftPot / rightPot) * delta_Down;
			int power = (fullPower_Down * offset);
			return power;
		}
	}

	return 0;
}

int GetRightPower(float leftPot, float rightPot)
{
	const int fullPower = 127;
	const int fullPower_Down = 100;
	const float delta = 0.6;
	const float delta_Down = 0.6;

	if (vexRT[Btn8D] == 0 && vexRT[Btn8U] == 0) return 0;

	if (vexRT[Btn8U] == 1)
	{
		if (SensorValue[armPotentiometerRight] > 3602)
		  {
		  	return 0;
		  }

		PreviousAction = Up;
		if (rightPot <= 300)
		{
			return fullPower;
		}

		if (leftPot >= rightPot)
		{
			return fullPower;
		}
		else
		{
			float offset = (leftPot / rightPot) * 100 * delta;
			int power = (fullPower * offset) / 100;
			return power;
		}
	}
	else if (vexRT[Btn8D] == 1)
	{
    PreviousAction = Down;
		if (leftPot <= rightPot)
		{
			if (rightPot <= 400)
			{
                // need to slow down
				//return fullPower_Down * 0.3;
			}
			return fullPower_Down;
		}
		else
		{
			float offset = (rightPot / leftPot) * delta_Down;
			int power = (fullPower_Down * offset);
			return power;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// Adjust lifts
/// Adjust the lifts whenever we release the buttons.
/////////////////////////////////////////////////////////////////////////////////////////////
void AdjustLift()
{
    // any buttons pressed? if so, returns;
	if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

    // already adjusted? if so, returns;
	if (PreviousAction == Adjusted) return;

	motor[LeftLift1] = 0;
	motor[LeftLift2] = 0;

	motor[RightLift1] = 0;
	motor[RightLift2] = 0;

	float leftPot = GetLeftValue();
  float rightPot = GetRightValue();

    // skip adjustment, if the lifts are too low or too high.
  if (leftPot <= 100 || rightPot <=100 || leftPot >= 1500 || rightPot >= 1500)
  {
  	return;
  }

    // offset = tolerance
  int offset = 10;
  int offset_Down = 5;

    // power values that we need for up and down
	int power = -33;
	int power_Down = -35; // adjust by moving up even for down. found it is more stable. use positive values to adjust by moving down.

    if (leftPot == rightPot) return;

    ClearTimer(T1);


    // in case of moving up
    if (PreviousAction == Up)
    {
		if (leftPot > rightPot)
		{
            // when the left is higher, move up the right until the right + offset is not lower than the left.
			while (leftPot > rightPot + offset)
			{
					if (time1[T1] > 1000) return;

				  if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;
					motor[RightLift1] = motor[RightLift2] = power;

					leftPot = GetLeftValue();
			    rightPot = GetRightValue();
			}
		}
		else if (leftPot < rightPot)
		{
			while (leftPot + offset < rightPot)
			{
				if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

					motor[LeftLift1] = motor[LeftLift2] = power;

					leftPot = GetLeftValue();
    			rightPot = GetRightValue();
			}
		}
	}
	else if (PreviousAction == Down)
	{
        // ok, for down. even more interesting
        // let's wait for 1.3 secs. (until the lift completely stops)
	    // ClearTimer(T1);
			// while (time1[T1] < 1300){}

    leftPot = GetLeftValue();
    rightPot = GetRightValue();

		if (leftPot > rightPot)
		{
			while (leftPot  > rightPot + offset_Down)
			{
				if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

				 motor[RightLift1] = motor[RightLift2] = power_Down;

                // uncommend the block below if we want to adjust by moving down.
                // then we might need the delays
                // motor[LeftLift1] = power_Down;
				// motor[LEftLift2] = power_Down;

				// ClearTimer(T1);
				// while (time1[T1] < 300){}

				 leftPot = GetLeftValue();
				 rightPot = GetRightValue();
			}
		}
		else if (leftPot < rightPot)
		{
			while (leftPot + offset_Down < rightPot)
			{
				 if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

				 motor[LeftLift1] = motor[LeftLift2] = power_Down;

                // uncommend the block below if we want to adjust by moving down.
				// motor[RightLift1] = power_Down;
				// motor[RightLift2] = power_Down;



				 leftPot = GetLeftValue();
				 rightPot = GetRightValue();
			}
		}
	}

	motor[LeftLift1] = 0;
	motor[LeftLift2] = 0;
	motor[RightLift1] = 0;
	motor[RightLift2] = 0;

    // finish the adjustment
    PreviousAction = Adjusted;
}


int LiftAdjust (int thisP, int otherP)
{
	const int tolerance = 10;
	int scaletolerance = ((thisP + otherP) / 2 - 1550) / 200;
	if (thisP > otherP + (tolerance - scaletolerance))
	{
		return 1 + (1 * (thisP - otherP)) / 1;
	}
	else if (thisP + (tolerance - scaletolerance) < otherP)
	{
		return -1 + (1 * (thisP - otherP)) / 1;
	}
	else
	{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                               Functions Below
//
//
/////////////////////////////////////////////////////////////////////////////////////////////
void GyroRotateAndReadyCube(int angle)
{
	motor[CubeIntake] = -127;
	GyroRotate(angle);
	motor[CubeIntake] = 0;
}

void Rotate(int power)
{
//	if (SensorValue[Jumper1] == 0)
//	{
//		power = -power;
//	}
    motor[FrontLeft] = power;
    motor[FrontRight] = -power;
    motor[BackRight] = -power;
    motor[BackLeft] = power;
}

void StopMoving()
{
		motor[FrontLeft] = 0;
		motor[FrontRight] = 0;
		motor[BackRight] = 0;
		motor[BackLeft] = 0;
}


void SonarRotate(int distance, int power)
{
	if (distance <= 0) return;

	if (SensorValue[Jumper1] == 1)
	{ // RED
		power = -power;
		// power = -30;
		while (SensorValue[SonarSensor] > distance)
		{
			Rotate(power);
		}
	}

	StopMoving();
//	return SensorValue[GyroDown];
}


void EncoderRotate(int power)
{
	int left = nMotorEncoder(FrontLeft);

	left = left / 8;
	if (power <= 0) return;

	if (left < 0)
	{ // RED
		while (nMotorEncoder(FrontLeft) < left)
		{
			Rotate(power);
		}
	}

	StopMoving();
}

void GyroRotateToInitialPosition(int power)
{
	if (power <= 0) return;

	if (SensorValue[GyroDown] < 0)
	{	// RED
			while (SensorValue[GyroDown] < 0)
			{
				Rotate(power);
			}
	}
	else
	{ // BLUE
		power = -power;
		while (SensorValue[GyroDown] < 0)
		{
			Rotate(power);
		}
	}
}

void GyroRotate(int angle)
{
	SensorValue[GyroDown] = 0;
	int power = 50;

	if (SensorValue[Jumper1] == 0)
	{
		if (angle > 0)
		{
			while (SensorValue[GyroDown] < angle)
			{
				Rotate(power);
			}
		}
		else
		{
			power = -power;
			while (SensorValue[GyroDown] > angle)
			{
				Rotate(power);
			}
		}
	}
	else
	{
		// Blue
		angle = -angle;

		if (angle > 0)
		{
			while (SensorValue[GyroDown] < angle)
			{
				Rotate(power);
			}
		}
		else
		{
			power = -power;
			while (SensorValue[GyroDown] > angle)
			{
				Rotate(power);
			}
		}
	}

//	StopMoving();
}

void PickUpSkyrise(int duration)
{
		Claw(127);
		wait1Msec(duration);
		Claw(30);
}

void ReleaseSkyrise(int duration)
{
		Claw(-127);
		wait1Msec(duration);
		Claw(0);
}

void Claw(int power)
{
    motor[CrayonIntake] = power;
}

void StopLift()
{
		motor[LeftLift1] = 0;
    motor[RightLift1] = 0;
		motor[LeftLift2] = 0;
    motor[RightLift2] = 0;
}

void AdjustAutoLiftUp()
{
		int originalPower = 38;
		int power = AdjustBatteryLevel(originalPower) * -1;

		if (nMotorEncoder(LeftLift2) > nMotorEncoder(RightLift1))
		{
							
				while(nMotorEncoder(LeftLift2)> nMotorEncoder(RightLift1))
				{
				    motor[LeftLift1] = power;
				    motor[LeftLift2] = power;
		//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
				}
				
				StopLift();
	}
	else
	{
										
		while(nMotorEncoder(RightLift1) > nMotorEncoder(LeftLift2))
		{
		    motor[RightLift1] = power;
		    motor[RightLift2] = power;
//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}
		
		StopLift();
	}
}

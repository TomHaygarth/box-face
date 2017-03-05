/*
	File: XController.h
	Author: Tom Haygarth
	Version 0.1
	Updated: 20/03/2013

	Xcontroller is a class that encapsulates the functionality of an Xbox360 controller 
*/

#pragma once

#include <Windows.h>
#include <XInput.h>

namespace BoxFace
{

	struct BOXVEC2
	{
		float X;
		float Y;
	};

	class XController
	{
	public:


		///--- Initialises the controller ---///
		///--- ControllerID is the controller number (range from 0-3) ---///
		///--- Returns false if the controller can't be found ---///
		bool Initialise(int ControllerID);

		///--- Updates the controller's information ---///
		void Update();

		///--- Returns the Position of the LeftAnalogue Stick ---///
		BOXVEC2 LeftStickPos() { return mLeftStickPos; }

		///--- Returns the Position of the RightAnalogue Stick ---///
		BOXVEC2 RightStickPos() { return mRightStickPos; }

		bool ButtonPressed(int button);
		bool ButtonReleased(int button);

		bool ButtonDown(int button);
		bool ButtonUp(int button);

		///--- Sets the vibration intensity of the right acctuator, range between 0 and 255 ---///
		void SetVibration(char leftIntensity, char rightIntensity);


		float LeftTrigger();
		float RightTrigger();

	private:

		BOXVEC2 mLeftStickPos;
		BOXVEC2 mRightStickPos;

		XINPUT_STATE mXinputState;
		XINPUT_STATE mXinputOldState;

		int mControllerID;

	};
}
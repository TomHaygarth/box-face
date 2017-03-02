

#include "XController.h"

namespace BoxFace
{

	bool XController::Initialise(int ControllerID)
	{

		DWORD dwResult;    
		
		mControllerID = ControllerID;

		ZeroMemory( &mXinputState, sizeof(XINPUT_STATE) );

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState( mControllerID, &mXinputState );

		// if the contorller is found
		if( dwResult == ERROR_SUCCESS )
		{
			return true;
		}
		else
		{
			return false; 
		}
		
	}

	void XController::Update()
	{
		// set the old state of our controller
		mXinputOldState = mXinputState;

		// get the current input state
		XInputGetState( mControllerID, &mXinputState );

		

		// if the left stick's X position is outside the dead zone
		if( mXinputState.Gamepad.sThumbLX - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > 0 || mXinputState.Gamepad.sThumbLX + XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < 0)
		{
			// apply it to the analog
			mLeftStickPos.X = mXinputState.Gamepad.sThumbLX/32767.0f;
		}
		else
		{
			mLeftStickPos.X = 0.0f;
		}

		// if the left stick's Y position is outside the dead zone
		if( mXinputState.Gamepad.sThumbLY - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > 0 || mXinputState.Gamepad.sThumbLY + XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < 0)
		{
			// apply it to the analog
			mLeftStickPos.Y = mXinputState.Gamepad.sThumbLY/32767.0f;
		}
		else
		{
			mLeftStickPos.Y = 0.0f;
		}

		// if the Right stick's X position is outside the dead zone
		if( mXinputState.Gamepad.sThumbRX - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > 0 || mXinputState.Gamepad.sThumbRX + XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < 0)
		{
			mRightStickPos.X = mXinputState.Gamepad.sThumbRX/32768.0f;
		}
		else
		{
			mRightStickPos.X = 0.0f;
		}

		// if the Right stick's Y position is outside the dead zone
		if( mXinputState.Gamepad.sThumbRY - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > 0 || mXinputState.Gamepad.sThumbRY + XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < 0)
		{
			mRightStickPos.Y = mXinputState.Gamepad.sThumbRY/32768.0f;
		}
		else
		{
			mRightStickPos.Y = 0.0f;
		}

		
		// copy the memory from the state to the analogue stick input
		// we add 16 to set the last 2 bytes of the float to the 2 bytes from sThumb.
		// This converts it to a value between -1 and 1


		//mRightStickPos.X = mXinputState.Gamepad.sThumbRX >> 8;
		//mRightStickPos.Y = mXinputState.Gamepad.sThumbRY >> 8;

		//memcpy(&mLeftStickPos.X, &mXinputState.Gamepad.sThumbLX, sizeof(short));
		//memcpy(&mLeftStickPos.Y, &mXinputState.Gamepad.sThumbLY, sizeof(short));

		//memcpy(&mRightStickPos.X+16, &mXinputState.Gamepad.sThumbRX, sizeof(short));
		//memcpy(&mRightStickPos.Y+16, &mXinputState.Gamepad.sThumbRY, sizeof(short));
	}



	bool XController::ButtonPressed(int button)
	{
		if((mXinputState.Gamepad.wButtons & button) & ~(mXinputOldState.Gamepad.wButtons & button))
		{
			return true;
		}

		return false;
	}

	bool XController::ButtonReleased(int button)
	{
		if(~(mXinputState.Gamepad.wButtons & button) & (mXinputOldState.Gamepad.wButtons & button))
		{
			return true;
		}

		return false;
	}
	bool XController::ButtonDown(int button)
	{
		if(mXinputState.Gamepad.wButtons & button)
		{
			return true;
		}

		return false;
	}

	bool XController::ButtonUp(int button)
	{
		if(~(mXinputState.Gamepad.wButtons & button))
		{
			return true;
		}

		return false;

	}

	void XController::SetVibration(char leftIntensity, char rightIntensity)
	{
		XINPUT_VIBRATION vibrationInfo;

		vibrationInfo.wLeftMotorSpeed = 257*leftIntensity;
		vibrationInfo.wRightMotorSpeed = 257*rightIntensity;

		XInputSetState(mControllerID, &vibrationInfo);
	}

	float XController::LeftTrigger()
	{
		return mXinputState.Gamepad.bLeftTrigger/255.0f;
	}

	float XController::RightTrigger()
	{
		return mXinputState.Gamepad.bRightTrigger/255.0f;
	}
}
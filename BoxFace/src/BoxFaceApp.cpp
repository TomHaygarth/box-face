

#include "BoxFaceApp.h"
#include <string>
#include <sstream>

#include "configuration\ButtonConfigManager.h"

bool BoxFaceApp::Initialise()
{
	if(!mXboxController.Initialise(0))
	{
		MessageBox(NULL, "No controller found!", NULL, MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	Max_Screen_X = 800;
	Max_Screen_Y = 800;

	// set the controller stick positions to register at neutral
	mLstickForward = false;
	mLstickBackward = false;
	mLstickLeft = false;
	mLstickRight = false;

	mRstickForward = false;
	mRstickBackward = false;

	// create a rectangle to draw our slider into (Rememeber the values are in viewport coords 0 to 1)
	BOXRECT rect;
	rect.top = 0.3f;
	rect.bottom = 0.35f;
	rect.left = 0.1f;
	rect.right = 0.4f;

	mMouseLookSlider = new UISlider(0.5f,rect);

	rect.top += 0.05f;
	rect.bottom += 0.05f;
	mSliderInfoText = new UIComponent("Mouse Sensitivety slider value: ", rect);

	mButtonConfig = new BoxFace::Configuration::ButtonConfigManager();

	if (!mButtonConfig->LoadConfigFile("config/buttons.cfg"))
	{
		MessageBox(NULL, "Failed to find button config file!", NULL, MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}

void BoxFaceApp::Unload()
{
	delete mButtonConfig;
	mButtonConfig = 0;
	delete mSliderInfoText;
	mSliderInfoText = 0;
	delete mMouseLookSlider;
	mMouseLookSlider = 0;
}

void BoxFaceApp::Update()
{
	mXboxController.Update();

	mXboxController.ButtonReleased(XINPUT_GAMEPAD_DPAD_UP);

	// use the back button to get the window we will direct all our messages to
	// can possibly replace this by just calling this function whenever the cursor leaves the screen rect http://msdn.microsoft.com/en-us/library/windows/desktop/ms633519(v=vs.85).aspx
	if(mXboxController.ButtonPressed(XINPUT_GAMEPAD_BACK))
	{
		// get the cursor position
		GetCursorPos(&mMousePos);

		mMsgWindow = NULL;

		mMsgWindow = WindowFromPoint(mMousePos);

		if(mMsgWindow == NULL)
		{
			MessageBox(NULL, "No Window Found!", NULL, MB_ICONEXCLAMATION | MB_OK);
		}

	}

	if(mXboxController.RightStickPos().X != 0 || mXboxController.RightStickPos().Y != 0)
	{
		
		// TODO: Fix bug where top left direction moves cursor faster
		// it is because the -ve float value is rounded down to -1 first, where all +ve values are rounded down so stays at 0 longer
		GetCursorPos(&mMousePos);
		mMousePos.x += static_cast<LONG>(mXboxController.RightStickPos().X*100.0f*mMouseLookSlider->GetValue());
		mMousePos.y -= static_cast<LONG>(mXboxController.RightStickPos().Y*100.0f*mMouseLookSlider->GetValue());

		//SendMessage(NULL, WM_MOUSEMOVE, 0,  LOWORD(mMousePos.x) + HIWORD(mMousePos.y));

		SetCursorPos(mMousePos.x,mMousePos.y);
	}

	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_START, VK_ESCAPE);
	
	char buttonKeyCode;

	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_A, mButtonConfig->TryGetChar("A", buttonKeyCode) ? buttonKeyCode : ' ');
	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_B, mButtonConfig->TryGetChar("B", buttonKeyCode) ? buttonKeyCode : 'E');
	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_X, mButtonConfig->TryGetChar("X", buttonKeyCode) ? buttonKeyCode : 'R');
	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_Y, mButtonConfig->TryGetChar("Y", buttonKeyCode) ? buttonKeyCode : 'Q');
	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_LEFT_SHOULDER, mButtonConfig->TryGetChar("L_SHOULDER", buttonKeyCode) ? buttonKeyCode : VK_SHIFT);
	ProcessButtonToKeyEvent(XINPUT_GAMEPAD_RIGHT_SHOULDER, mButtonConfig->TryGetChar("R_SHOULDER", buttonKeyCode) ? buttonKeyCode : VK_CONTROL);

	if(mXboxController.ButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT))
	{

		PostMessage(mMsgWindow, WM_MOUSEWHEEL , HIWORD(120), LOWORD(mMousePos.x) + HIWORD(mMousePos.y));
	}
	if(mXboxController.ButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT))
	{

		PostMessage(mMsgWindow, WM_MOUSEWHEEL , HIWORD(-120), LOWORD(mMousePos.x) + HIWORD(mMousePos.y));
	}

	char leftActuatorIntensity = static_cast<byte>(255 * mXboxController.LeftTrigger());
	char rightActuatorIntensity = static_cast<byte>(255 * mXboxController.RightTrigger());

	mXboxController.SetVibration(leftActuatorIntensity, rightActuatorIntensity);

	float rTrigger = mXboxController.RightTrigger();

	// TODO: Fix relative positions of the mouse clicks, as the coords have to be specified in terms of window coordinates and not screen coords
	// possibly use this to get the coords of the window first http://msdn.microsoft.com/en-us/library/windows/desktop/ms633519(v=vs.85).aspx (get window rect)
	// then minus the mouse pos from it
	if(rTrigger > 0.6f && mLButtonUp)
	{
		
		PostMessage(mMsgWindow, WM_LBUTTONDOWN , MK_LBUTTON, LOWORD(mMousePos.x) + HIWORD(mMousePos.y));
		// mouse button is nolonger up
		mLButtonUp = false;

	}

	// check if we've not reset the button up yet
	else if(rTrigger <= 0.6f && !mLButtonUp)
	{
		PostMessage(mMsgWindow, WM_LBUTTONUP , 0, LOWORD(mMousePos.x) + HIWORD(mMousePos.y));

		mLButtonUp = true;
	}

	if(mXboxController.LeftTrigger() > 0.6f)
	{
		
		PostMessage(mMsgWindow, WM_RBUTTONDOWN , MK_RBUTTON, LOWORD(mMousePos.x) + HIWORD(mMousePos.y));
		// mouse button is nolonger up
		mRButtonUp = false;
	}

	// check if we've not reset the button up yet
	else if(!mRButtonUp)
	{
		PostMessage(mMsgWindow, WM_RBUTTONUP , 0, LOWORD(mMousePos.x) + HIWORD(mMousePos.y));

		mRButtonUp = true;
	}

	// check if the left analog stick is pressed forward or back
	if(mXboxController.LeftStickPos().X >  0.6f)
	{
		mLstickRight = true;
	}
	else if (mXboxController.LeftStickPos().X <  -0.6f)
	{
		mLstickLeft = true;
	}

	if(mXboxController.LeftStickPos().Y < -0.6f)
	{
		mLstickBackward = true;
	}
	else if (mXboxController.LeftStickPos().Y >  0.6f)
	{
		mLstickForward = true;
	}



	if(mLstickForward)
	{
		char keyCode;
		if (!mButtonConfig->TryGetChar("L_STICK_UP", keyCode))
		{
			keyCode = 'W';
		}
		if(mXboxController.LeftStickPos().Y <=  0.6f)
		{
			mLstickForward = false;
			PostKeyUp(keyCode);
		}
		else
		{
			PostKeyDown(keyCode);
		}
	}

	else if(mLstickBackward)
	{
		char keyCode;
		if (!mButtonConfig->TryGetChar("L_STICK_DOWN", keyCode))
		{
			keyCode = 'S';
		}
		if(mXboxController.LeftStickPos().Y >= -0.6f)
		{
			mLstickBackward = false;
			PostKeyUp(keyCode);
		}
		else
		{
			PostKeyDown(keyCode);
		}
	}

	if(mLstickLeft)
	{
		char keyCode;
		if (!mButtonConfig->TryGetChar("L_STICK_LEFT", keyCode))
		{
			keyCode = 'A';
		}
		if(mXboxController.LeftStickPos().X >= -0.6f)
		{
			mLstickLeft = false;
			PostKeyUp(keyCode);
		}
		else
		{
			PostKeyDown(keyCode);
		}
	}

	else if(mLstickRight)
	{
		char keyCode;
		if (!mButtonConfig->TryGetChar("L_STICK_RIGHT", keyCode))
		{
			keyCode = 'D';
		}
		if(mXboxController.LeftStickPos().X <= 0.6f)
		{
			mLstickRight = false;
			PostKeyUp(keyCode);
		}
		else
		{
			PostKeyDown(keyCode);
		}
	}

	// if the user is using the up/down on the d-pad increase/decrease the mouse sensitivety
	if(mXboxController.ButtonDown(XINPUT_GAMEPAD_DPAD_UP) && mMouseLookSlider->GetValue() < 1.0f)
	{
		mMouseLookSlider->SetValue(mMouseLookSlider->GetValue() + 0.01f);
	}
	else if(mXboxController.ButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) && mMouseLookSlider->GetValue() > 0.0f)
	{
		mMouseLookSlider->SetValue(mMouseLookSlider->GetValue() - 0.01f);
	}

	// create a temporary string stream to input our slider value into  
	std::ostringstream tempString;
	tempString << mMouseLookSlider->GetValue();

	mSliderInfoText->SetText("Mouse Sensitivety slider value: "  + tempString.str());

	// sleep for 20ms
	Sleep(20);
}

void BoxFaceApp::Render(HDC &hdc, HDC &bitmapHDC)
{
	char leftStick[128];

	sprintf(leftStick, "LeftStick pos X: %f, Y: %f\nRightStick pos X: %f, Y: %f\nLeftTrig: %f\nRightTrig: %f", mXboxController.LeftStickPos().X, mXboxController.LeftStickPos().Y,
		mXboxController.RightStickPos().X, mXboxController.RightStickPos().Y, mXboxController.LeftTrigger(), mXboxController.RightTrigger());

	RECT rt;

	rt.left= 80;
	rt.top= 80;
	rt.right= 800;
	rt.bottom= 800;
	
	DrawText(hdc,leftStick,strlen(leftStick), &rt, DT_LEFT);

	mMouseLookSlider->Draw(hdc, Max_Screen_X, Max_Screen_Y);
	mSliderInfoText->Draw(hdc, Max_Screen_X, Max_Screen_Y);
}

void BoxFaceApp::ProcessButtonToKeyEvent(const int& controllerButton, const char& keyCode)
{
	if (mXboxController.ButtonDown(controllerButton))
	{
		PostKeyDown(keyCode);
	}
	else if (mXboxController.ButtonReleased(controllerButton))
	{
		PostKeyUp(keyCode);
	}
}

void BoxFaceApp::PostKeyPress(int Key, bool isExtended)
{
	int scan = MapVirtualKey(Key, 0);

	// Build the generic lparam to be used for WM_KEYDOWN/WM_KEYUP/WM_CHAR
	int lparam = 0x00000001 | (LPARAM)(scan << 16);         // Scan code, repeat=1

	if (isExtended)
		lparam = lparam | 0x01000000;       // Extended code if required

	PostMessage(mMsgWindow, WM_KEYDOWN, Key, lparam);
	//PostMessage(mMsgWindow, WM_CHAR, Key, lparam);

	//Sleep(1);

	lparam = 0x60000001 | (LPARAM)(scan << 16);
	PostMessage(mMsgWindow, WM_KEYUP, 0, lparam);
}


void BoxFaceApp::PostKeyDown(int Key, bool isExtended)
{
	int scan = MapVirtualKey(Key, 0);

	// Build the generic lparam to be used for WM_KEYDOWN/WM_KEYUP/WM_CHAR
	int lparam = 0x00000001 | (LPARAM)(scan << 16);         // Scan code, repeat=1

	if (isExtended)
		lparam = lparam | 0x01000000;       // Extended code if required

	PostMessage(mMsgWindow, WM_KEYDOWN, Key, lparam);
	//PostMessage(mMsgWindow, WM_CHAR, Key, lparam);
}

// this function doesn't seem to work for java? =/
void BoxFaceApp::PostKeyUp(int Key, bool isExtended)
{
	int scan = MapVirtualKey(Key, 0);

	//int lparam = 0xC0000001;// 0x60000001 | (LPARAM)(scan << 16); // new value sourced from http://stackoverflow.com/questions/7072717/how-to-post-a-wm-keyup-msg-without-triggerring-a-wm-char-msg 
	int lparam = 0xC0000001  | (LPARAM)(scan << 16);
	PostMessage(mMsgWindow, WM_KEYUP, Key, lparam);
}


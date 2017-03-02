#ifndef _BOX_FACE_APP
#define _BOX_FACE_APP

/*
	File: Main.cpp
	Author: Tom Haygarth
	Version: 0.1
	Updated: 20/03/2013

	The application is designed to use input gained from the XInput interface to emulate keyboard and mouse functionality.
	By mapping various keys and mouse directions onto the keys and analogue sticks.
*/

// include files
#include <windows.h>
#include <XInput.h>

#include "controller\XController.h"
#include "UI\UIComponent.h"
#include "UI\UISlider.h"

using namespace std;
using BoxFace::BOXVEC2;
using BoxFace::XController;


class BoxFaceApp
{
public:

	bool Initialise();

	void Update();

	void Render(HDC &hdc, HDC &bitmapHDC);

	void Unload();


private:

	float Max_Screen_X, Max_Screen_Y;

	XController mXboxController;

	POINT mMousePos;

	HWND mMsgWindow; // the window we will sen messages to

	bool mLstickForward;
	bool mLstickBackward;
	bool mLstickLeft;
	bool mLstickRight;

	bool mRstickForward;
	bool mRstickBackward;

	bool mLButtonUp;
	bool mRButtonUp;

	// Private functions

	void PostKeyPress(int Key, bool isExtended = false);
	void PostKeyDown(int Key, bool isExtended = false);
	void PostKeyUp(int Key, bool isExtended = false);

	UIComponent * mSliderInfoText;
	UISlider * mMouseLookSlider;
	
};

#endif
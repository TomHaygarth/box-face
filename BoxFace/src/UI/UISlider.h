/*
	File: UISlider.h
	Author: Tom Haygarth
	Version: 0.1
	Updated: 02/03/2014

	The UISlider is a simple UI object that acts as an adjustable slider. It inherits from the base class UIComponent and as a result is also drawn
	using viewport coordinates between 0 and 1. The value of the slider is returned as a float between 0 and 1 using the GetValue() fuction. 
*/

#pragma once

#include <Windows.h>
#include <string>
#include "UIComponent.h"

class UISlider : public UIComponent
{
public:

	/// <summary> simple constructor that sets the text and position of the image. </summary>
	/// <param name="val">Sets the text of the component.</param>
	/// <param name="rect">The rect the component will be drawn into</param>
	UISlider(float val, BOXRECT rect);

	void OnClick();

	void Draw(HDC &hdc, const float &screenWidth, const float &screenHeight) const;


protected:

};
/*
	File: UISlider.cpp
	Author: Tom Haygarth
	Version: 0.1
	Updated: 02/03/2014

	The UISlider is a simple UI object that acts as an adjustable slider. It inherits from the base class UIComponent and as a result is also drawn
	using viewport coordinates between 0 and 1. The value of the slider is returned as a float between 0 and 1 using the GetValue() fuction. 
*/


#include "UISlider.h"

UISlider::UISlider(float val, BOXRECT rect) : UIComponent("default!", rect)
{
	m_text = "default!";
	m_value = val;
	m_selected = false;
	m_drawRect = rect;
}

void UISlider::OnClick()
{
	m_selected = true;
}

void UISlider::Draw(HDC &hdc, const float &screenWidth, const float &screenHeight)  const
{
	int top = static_cast<LONG>(m_drawRect.top * screenHeight);
	int bottom = static_cast<LONG>(m_drawRect.bottom * screenHeight);
	int left = static_cast<LONG>(m_drawRect.left * screenWidth);
	int right = static_cast<LONG>(m_drawRect.right * screenWidth);

	int midPoint = top + static_cast<int>((bottom - top)*0.5f);

	// move to the left side of the drawing rectangle, and the centre point.
	MoveToEx(hdc, left, midPoint, static_cast<LPPOINT>(NULL));
    LineTo(hdc, right, midPoint);
   
	int markerPoint = left + static_cast<int>((right - left)*m_value);

	// move to the top side of the drawing rectangle, and the point.
	MoveToEx(hdc, markerPoint, top, static_cast<LPPOINT>(NULL));
	LineTo(hdc, markerPoint, bottom);
}
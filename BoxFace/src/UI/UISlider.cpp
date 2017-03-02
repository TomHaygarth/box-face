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

void UISlider::Draw(HDC &hdc,float &screenWidth, float &screenHeight)
{
	RECT rt;
	rt.top = m_drawRect.top * screenHeight;
	rt.bottom = m_drawRect.bottom * screenHeight;
	rt.left = m_drawRect.left * screenWidth;
	rt.right = m_drawRect.right * screenWidth;

	// move to the left side of the drawing rectangle, and the centre point.
	MoveToEx(hdc, (int) rt.left, (int) rt.top + ((rt.bottom -rt.top)*0.5f), (LPPOINT) NULL); 
    LineTo(hdc, (int) rt.right, (int) rt.top + ((rt.bottom -rt.top)*0.5f)); 
   
	// move to the top side of the drawing rectangle, and the point.
	MoveToEx(hdc, (int) rt.left +((rt.right-rt.left)*m_value), (int) rt.top, (LPPOINT) NULL);
	LineTo(hdc, (int)  rt.left +((rt.right-rt.left)*m_value), (int) rt.bottom);
}
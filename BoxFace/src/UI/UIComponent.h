/*
	File: UIComponent.h
	Author: Tom Haygarth
	Version: 0.1
	Updated: 01/03/2014

	The UIComponent is a simple component that contains the basic functionality of a UI element. It holds text to display. As well as having functionality for
	handling clicking of said object (to be implemented.)
	The position and size of the UIComponent object is specified in viewport coordinates between 0 and 1, where 0,0 is the top left corner of the screen. The 
	reason behind this is to allow all UIComponents to scale according to screen size/resolution.
*/

#pragma once

#include <Windows.h>
#include <string>

struct BOXRECT
{
		float top;
		float left;
		float bottom;
		float right;
};

class UIComponent
{
public:

	/// <summary> simple constructor that sets the text and position of the image. </summary>
	/// <param name="text">Sets the text of the component.</param>
	/// <param name="rect">The rect the component will be drawn into</param>
	UIComponent(std::string text, BOXRECT rect);

	std::string GetText() {return m_text;}
	void SetText(std::string text) {m_text = text;}

	BOXRECT GetDrawRect () {return m_drawRect;}
	void SetDrawRect (BOXRECT rect) {m_drawRect = rect;}

	void Select(bool select) {m_selected = select;}
	bool IsSelected() {return m_selected;}

	void SetValue(float val) {m_value = val;}
	float GetValue() {return m_value;}

	virtual void OnClick();

	virtual void Draw(HDC &hdc, const float &screenWidth, const float &screenHeight) const;


protected:

	std::string m_text;
	BOXRECT m_drawRect;

	bool m_selected;
	float m_value;
};
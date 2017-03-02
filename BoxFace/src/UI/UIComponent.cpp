


#include "UIComponent.h"

UIComponent::UIComponent(std::string text, BOXRECT rect)
{
	m_text = text;
	m_selected = false;
	m_drawRect = rect;
}

void UIComponent::OnClick()
{
	m_selected = true;
}

void UIComponent::Draw(HDC &hdc,float &screenWidth, float &screenHeight)
{
	RECT rt;
	rt.top = m_drawRect.top * screenHeight;
	rt.bottom = m_drawRect.bottom * screenHeight;
	rt.left = m_drawRect.left * screenWidth;
	rt.right = m_drawRect.right * screenWidth;

	if(m_selected)
	{
		SetTextColor(hdc,RGB(255,0,0));
	}
	else
	{
		SetTextColor(hdc,RGB(0,0,0));
	}

	DrawText(hdc, (m_text.c_str()), strlen(m_text.c_str()), &rt,DT_CENTER | DT_NOCLIP); 


}
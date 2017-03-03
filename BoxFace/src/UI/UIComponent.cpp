


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

void UIComponent::Draw(HDC &hdc, const float &screenWidth, const float &screenHeight)  const
{
	RECT rt;
	rt.top = static_cast<LONG>(m_drawRect.top * screenHeight);
	rt.bottom = static_cast<LONG>(m_drawRect.bottom * screenHeight);
	rt.left = static_cast<LONG>(m_drawRect.left * screenWidth);
	rt.right = static_cast<LONG>(m_drawRect.right * screenWidth);

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
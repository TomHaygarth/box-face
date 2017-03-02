#ifndef _UI_MANAGER_APP_
#define _UI_MANAGER_APP_

/*
	File: UIManager.h
	Author: Tom Haygarth
	Version: 0.1
	Updated: 01/03/2014

	The UIManager is designed to control all aspects of UI in a scene. It organises UI components into scenes. It updates the scene components.
	
*/

#include <map>
#include <vector>
#include "UIComponent.h"

class UIManager
{
public:

	void Initialise(HDC *hdc);

	void CreateScene(std::string SceneName);
	void SetCurrentScene(std::string SceneName);

	void AddComponentToScene(UIComponent ui_component);

	void Update(char KeyboardInput[256]);

private:

	std::map<std::string, std::vector<UIComponent>*> m_scene_map;

	std::vector<UIComponent> * m_current_scene;

	HDC *m_hdc;
};

#endif
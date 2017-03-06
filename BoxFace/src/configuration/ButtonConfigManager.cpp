#include "ButtonConfigManager.h"

#include <fstream>
#include <string>
#include <sstream>

namespace BoxFace::Configuration
{

	ButtonConfigManager::ButtonConfigManager()
	{
	}


	ButtonConfigManager::~ButtonConfigManager()
	{
	}

	bool ButtonConfigManager::LoadConfigFile(const std::string& fileName)
	{
		std::ifstream configFile;

		configFile.open(fileName);

		// if our config file doesn't exist
		if (!configFile.is_open())
		{
			// exit with error code 1
			return false;
		}

		// create local variables for the games properties
		int screenWidth = 0;
		int screenHeight = 0;

		std::string strBuff;
		std::string propName;

		// loop through each line of the file and grab the necessary data
		while (!configFile.eof())
		{
			// ignore any potential whitespace before getting the property name
			std::ws(configFile);
			std::getline(configFile, strBuff);

			//if the string starts with a '#' ignore the line as it's a comment
			if (strBuff[0] == '#')
			{
				continue;
			}

			// extract the property name from the string buffer
			std::istringstream iss(strBuff);
			std::getline(iss, strBuff, '=');

			// store the property name and clear the string buffer 
			propName = strBuff;
			strBuff = "";

			std::getline(iss, strBuff);

			if (strBuff.length() != 0)
			{
				mProperties[propName] = strBuff[0];
			}

		}

		return true;
	}

	bool ButtonConfigManager::TryGetChar(const std::string& key, char& out) const
	{
		if (mProperties.find(key) != mProperties.end())
		{
			out = mProperties.at(key);
			return true;
		}

		return false;
	}
}
#pragma once

#include <map>

#include "IConfigurationManager.h"

namespace BoxFace::Configuration
{
	class ButtonConfigManager : public IConfigurationManager
	{
	public:
		ButtonConfigManager();
		~ButtonConfigManager();

		bool LoadConfigFile(const std::string& fileName);

		bool TryGetChar(const std::string& key, char& out) const;

	private:

		std::map<std::string, char> mProperties;
	};
}
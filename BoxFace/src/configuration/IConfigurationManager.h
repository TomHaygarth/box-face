#pragma once

#include <string>

namespace BoxFace::Configuration
{
	class IConfigurationManager
	{
	public:
		
		virtual bool LoadConfigFile(const std::string& fileName) = 0;

		virtual bool TryGetChar(const std::string& key, char& out) const = 0;
	};
}

#pragma once
#include<unordered_map>
#include<memory>
namespace Engine
{
	class DataSystem
	{
	private:
		struct GameData
		{
			std::unordered_map<std::string, bool> boolData;
			std::unordered_map<std::string, int32_t> intData;
		};
		static std::shared_ptr<GameData> s_gameData;
	public:
		static void addBool(const std::string& tag, bool data) { s_gameData->boolData[tag] = data; }
		static bool& getBool(const std::string& tag) { return s_gameData->boolData[tag]; }
		static void addInt(const std::string& tag, int32_t data) { s_gameData->intData[tag] = data;}
		static int32_t& getInt(const std::string & tag) { return s_gameData->intData[tag]; }
	};
}
#include "engine_pch.h"
#include "systems/dataSystem.h"

namespace Engine
{
	std::shared_ptr<DataSystem::GameData> DataSystem::s_gameData = std::shared_ptr<GameData>(new GameData);
}
#pragma once

// entry point
#include "include/independent/core/entrypoint.h"
#include "engine.h"
#include "UILayer.h"
#include "sceneLayer.h"

class engineApp : public Engine::Application
{
public:
	engineApp(Engine::ApplicationProps props);
	~engineApp() override;
private:
};

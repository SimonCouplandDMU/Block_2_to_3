/** \file engineApp.cpp
*/
#include "engineApp.h"


engineApp::engineApp(Engine::ApplicationProps props) : Application(props)
{
	m_layerStack.push(new SceneLayer("Scene Layer", getEntities(), getRegistry()));
	m_layerStack.push(new UILayer("UI Layer"));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	ApplicationProps props;
	props.winProps.title = "Breakout";
	props.winProps.width = 1024;
	props.winProps.height = 800;
	props.fontFilePath = "./assets/fonts/CURLZ___.TTF";
	props.characterSize = 56;
	props.vertexCapacity3D= 1000000;
	props.batchSize3D = 1024;
	return new engineApp(props);
}
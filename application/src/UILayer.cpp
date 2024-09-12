#include "UILayer.h"

UILayer::UILayer(const char* name) : Layer(name)
{
	m_view = glm::mat4(1.f);
	m_proj = glm::ortho(0.f, 1024.f, 0.f, 800.f);

	m_swu["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_proj)));



	m_texture.reset(Texture::create("./assets/textures/block_ss.png"));

	float u = (1.f / 384.f);
	float v = (1.f / 258.f);
	glm::vec2 c(200.f, 10.f);
	float p = 9.f;
	ball = SubTexture(m_texture, glm::vec2(c.x * u - (p * u), c.y * v + (p * v)), glm::vec2(c.x * u + (p * u), c.y * v - (p * v)));
	
	glm::vec2 p2;

	p2 = glm::vec2( 80.f, 24.f ) * 0.5f;
	c = { 217.f, 27.f };
	c += p2 * 0.5f;
	scoreLabel = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(61.f, 19.f) * 0.5f;
	c = { 291.f, 25.f };
	c += p2;
	livesLabel = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(303.f, 40.f) * 0.5f;
	c = { 80.f, 163.f };
	c += p2;
	gameOverLabel = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(245.f, 45.f) * 0.5f;
	c = { 79.f, 97.f };
	c += p2;
	youWinLabel = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = {209, 45.f};
	c += p2;
	numberLabels[0] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 233, 45.f };
	c += p2;
	numberLabels[1] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 258, 45.f };
	c += p2;
	numberLabels[2] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 283, 45.f };
	c += p2;
	numberLabels[3] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 309, 45.f };
	c += p2;
	numberLabels[4] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 334, 45.f };
	c += p2;
	numberLabels[5] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 209, 64.f };
	c += p2;
	numberLabels[6] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 233, 64.f };
	c += p2;
	numberLabels[7] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 258, 64.f };
	c += p2;
	numberLabels[8] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	p2 = glm::vec2(13.f, 18.f) * 0.5f;
	c = { 283, 64.f };
	c += p2;
	numberLabels[9] = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));



	scoreLabelQuad = Quad::createCentreHalfExtents({ 115.f,30.f }, { 80.f, 24.f });
	numberQuads[0] = Quad::createCentreHalfExtents({215.f,26.f }, { 13.f, 18.f });
	numberQuads[1] = Quad::createCentreHalfExtents({245.f,26.f }, { 13.f, 18.f });
	numberQuads[2] = Quad::createCentreHalfExtents({ 275.f,26.f }, { 13.f, 18.f });
	numberQuads[3] = Quad::createCentreHalfExtents({ 305.f,26.f }, { 13.f, 18.f });
	numberQuads[4] = Quad::createCentreHalfExtents({ 335.f,26.f }, { 13.f, 18.f });

	livesLabelQuad = Quad::createCentreHalfExtents({ 765.f,30.f }, glm::vec2(61.f, 19.f));
	ballQuads[0] = Quad::createCentreHalfExtents({ 845.f,30.f }, glm::vec2(18.f, 18.f));
	ballQuads[1] = Quad::createCentreHalfExtents({ 895.f,30.f }, glm::vec2(18.f, 18.f));
	ballQuads[2] = Quad::createCentreHalfExtents({ 945.f,30.f }, glm::vec2(18.f, 18.f));

	gameOverQuad = Quad::createCentreHalfExtents({ 512.f,400.f }, glm::vec2(303.f, 40.f));
	youWinQuad = Quad::createCentreHalfExtents({ 512.f,400.f }, glm::vec2(245.f, 45.f));
}


void UILayer::onRender()
{

	Renderer2D::begin(m_swu);

	int score = Engine::DataSystem::getInt("score");

	Renderer2D::submit(scoreLabelQuad, scoreLabel);
	Renderer2D::submit(numberQuads[0], numberLabels[(score % 100000) / 10000]);
	Renderer2D::submit(numberQuads[1], numberLabels[(score % 10000) / 1000]);
	Renderer2D::submit(numberQuads[2], numberLabels[(score % 1000) / 100]);
	Renderer2D::submit(numberQuads[3], numberLabels[(score % 100) / 10]);
	Renderer2D::submit(numberQuads[4], numberLabels[0]);

	Renderer2D::submit(livesLabelQuad, livesLabel);
	if (Engine::DataSystem::getInt("lives") > 0) Renderer2D::submit(ballQuads[0], ball);
	if (Engine::DataSystem::getInt("lives") > 1) Renderer2D::submit(ballQuads[1], ball);
	if (Engine::DataSystem::getInt("lives") > 2) Renderer2D::submit(ballQuads[2], ball);
	if (Engine::DataSystem::getBool("gameover")) Renderer2D::submit(gameOverQuad, gameOverLabel);
	if (Engine::DataSystem::getBool("won")) Renderer2D::submit(youWinQuad, youWinLabel);


	Renderer2D::end();
}

void UILayer::onUpdate(float timestep)
{
}





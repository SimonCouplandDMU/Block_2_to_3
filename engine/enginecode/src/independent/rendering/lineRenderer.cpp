#include "engine_pch.h"
#include <glad/glad.h>
#include "independent/rendering/lineRenderer.h"
#include "independent/core/application.h"
#include <numeric>
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	VertexBufferLayout LineRendererVertex::layout = VertexBufferLayout({ ShaderDataType::Float4, {ShaderDataType::Byte4, 0, true} });

	std::shared_ptr<LineRenderer::InternalData> LineRenderer::s_data = nullptr;

	void LineRenderer::init(uint32_t batchSize)
	{
		auto& resources = Application::getInstance().getResourceManager();

		s_data.reset(new InternalData);

		s_data->batchSize = batchSize;

		s_data->shader = resources->addShader("./assets/shaders/line.glsl");

		s_data->UBO.reset(UniformBuffer::create(UniformBufferLayout({
			{"u_projection", ShaderDataType::Mat4},
			{"u_view", ShaderDataType::Mat4}
			})));

		s_data->vertices.resize(s_data->batchSize);

		std::vector<uint32_t> indices(s_data->batchSize);
		std::iota(indices.begin(), indices.end(), 0);

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		s_data->VAO.reset(VertexArray::create());
		VBO.reset(VertexBuffer::create(s_data->vertices.data(), sizeof(LineRendererVertex) * s_data->vertices.size(), LineRendererVertex::layout));
		IBO.reset(IndexBuffer::create(indices.data(), indices.size()));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->UBO->attachShaderBlock(s_data->shader, "b_camera");
	}

	void LineRenderer::begin(const SceneWideUniforms& swu)
	{
		// Reset drawcount
		s_data->drawCount = 0;

		// Bind the shader
		glUseProgram(s_data->shader->getID());

		glBindBuffer(GL_UNIFORM_BUFFER, s_data->UBO->getID());
		s_data->UBO->uploadData("u_projection", swu.at("u_projection").second);
		s_data->UBO->uploadData("u_view", swu.at("u_view").second);
	}

	void LineRenderer::submit(const glm::vec2& start, const glm::vec2& end, const glm::vec4& tint)
	{
		if (s_data->drawCount + 2 > s_data->batchSize) flush();

		uint32_t packedTint = RendererCommon::pack(tint);

		s_data->vertices[s_data->drawCount].position = glm::vec4(start.x, start.y, 0.f, 1.f);
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
		s_data->vertices[s_data->drawCount].position = glm::vec4(end.x, end.y, 0.f, 1.f);
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
	}

	void LineRenderer::submit(const glm::vec2& centre, const glm::vec2& halfExtents, float angle, const glm::vec4& tint) //!< Render a tinted box
	{
		if (s_data->drawCount + 8 > s_data->batchSize) flush();

		uint32_t packedTint = RendererCommon::pack(tint);

		glm::mat4 rotMat = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
		glm::vec4 c = glm::vec4(centre.x, centre.y, 0.f, 0.f);
		
		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(-halfExtents.x, -halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(halfExtents.x, -halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;

		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(-halfExtents.x, halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(halfExtents.x, halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;

		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(-halfExtents.x, -halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(-halfExtents.x, halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;

		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(halfExtents.x, -halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
		s_data->vertices[s_data->drawCount].position = c + (rotMat * glm::vec4(halfExtents.x, halfExtents.y, 0.f, 1.f));
		s_data->vertices[s_data->drawCount].tint = packedTint;
		s_data->drawCount++;
	}

	void LineRenderer::submit(const glm::vec2& centre, float radius, const glm::vec4& tint) //!< Render a tinted circle
	{
		if (s_data->drawCount + static_cast<int>(s_data->circleVertexCount * 2.f) > s_data->batchSize) flush();

		uint32_t packedTint = RendererCommon::pack(tint);

		float delta = (glm::pi<float>() * 2.f) / s_data->circleVertexCount;

		glm::vec4 point(centre.x + radius, centre.y, 0.f, 1.f);
		float angle = delta;

		for (int i = 0;i < static_cast<int>(s_data->circleVertexCount); i++)
		{
			s_data->vertices[s_data->drawCount].position = point;
			s_data->vertices[s_data->drawCount].tint = packedTint;
			s_data->drawCount++;
			point.x = centre.x + cos(angle) * radius;
			point.y = centre.y - sin(angle) * radius;
			s_data->vertices[s_data->drawCount].position = point;
			s_data->vertices[s_data->drawCount].tint = packedTint;
			s_data->drawCount++;
			angle += delta;
		}
	}

	void LineRenderer::end()
	{
		if (s_data->drawCount > 0) flush();
	}

	void LineRenderer::flush()
	{
		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->drawCount, 0);

		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer()->getID());

		glDrawElements(GL_LINES, s_data->drawCount, GL_UNSIGNED_INT, nullptr);
	}
}
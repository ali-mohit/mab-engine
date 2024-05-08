#pragma once

#include <imgui.h>
#include "MABEngine.h"

#include "MABEngine/Core/TimeStep.h"


class ExampleLayer : public MABEngine::Layers::Layer {
public:
	ExampleLayer();

	void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

	void OnImGuiRender() override;

	void OnEvent(MABEngine::Events::Event& event) override;
private:
	float m_Degree = 0;
	float m_CameraRotationZSpeed = 180.0f;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeed = 10.0f;

	std::shared_ptr<MABEngine::Renderer::Shader> m_Shader;
	std::shared_ptr<MABEngine::Renderer::VertexArray> m_VertexArray;

	MABEngine::Renderer::OrthographicCamera m_Camera;
};
#pragma once

#include <imgui.h>
#include "MABEngine.h"

#include "MABEngine/Core/TimeStep.h"


class ExampleLayer : public MABEngine::Layers::Layer {
public:
	ExampleLayer(uint32_t width, uint32_t height);

	void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

	void OnImGuiRender() override;

	void OnEvent(MABEngine::Events::Event& event) override;
private:
	void CreateRectangleObject();
	void CreateTrianleObject();
private:
	uint32_t m_Width;
	uint32_t m_Height;


	MABEngine::Ref<MABEngine::Renderer::Shader> m_Shader;
	MABEngine::Ref<MABEngine::Renderer::VertexArray> m_VertexArray;

	MABEngine::Ref<MABEngine::Renderer::Shader> m_BlueShader;
	MABEngine::Ref<MABEngine::Renderer::VertexArray> m_RectangleVertexArray;

	MABEngine::Camera::OrthographicCameraController m_CameraController;
};
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
	void CreateTriangleObject();
private:
	uint32_t m_Width;
	uint32_t m_Height;

	MABEngine::Renderer::ShaderLibrary m_ShaderLib;

	MABEngine::Ref<MABEngine::Textures::Texture2D> m_TextureCheckerBoard;
	MABEngine::Ref<MABEngine::Textures::Texture2D> m_TextureMabLogo;

	MABEngine::Ref<MABEngine::Renderer::Shader> m_SolidColorShader;
	MABEngine::Ref<MABEngine::Renderer::VertexArray> m_TriangleVertexArray;

	MABEngine::Ref<MABEngine::Renderer::VertexArray> m_RectangleVertexArray;

	MABEngine::Camera::OrthographicCameraController m_CameraController;
};
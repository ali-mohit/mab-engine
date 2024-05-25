#pragma

#include "MABEngine.h"

class SandBox2DLayer : public MABEngine::Layers::Layer {
public:
	SandBox2DLayer(uint32_t width, uint32_t height);

	void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

	void OnImGuiRender() override;

	void OnEvent(MABEngine::Events::Event& event) override;
private:
	void CreateRectangleObject();
private:
	uint32_t m_Width;
	uint32_t m_Height;

	MABEngine::Renderer::ShaderLibrary m_ShaderLib;

	MABEngine::Core::Ref<MABEngine::Renderer::Shader> m_SolidColorShader;
	MABEngine::Core::Ref<MABEngine::Renderer::VertexArray> m_RectangleVertexArray;

	MABEngine::Camera::OrthographicCameraController m_CameraController;

};

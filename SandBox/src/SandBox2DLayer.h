#pragma

#include <MABEngine.h>
#include <glm/glm.hpp>

class SandBox2DLayer : public MABEngine::Layers::Layer {
public:
	SandBox2DLayer(uint32_t width, uint32_t height);

	void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

	void OnImGuiRender() override;

	void OnEvent(MABEngine::Events::Event& event) override;
private:
	uint32_t m_Width;
	uint32_t m_Height;

	glm::vec3 m_SolidColor = { 0.2f, 0.3f, 0.8f };
	MABEngine::Camera::OrthographicCameraController m_CameraController;

};

#pragma

#include <MABEngine.h>
#include <glm/glm.hpp>

class SandBox2DLayer : public MABEngine::Layers::Layer {
public:
	SandBox2DLayer(uint32_t width, uint32_t height);

	void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

	virtual void OnAttach() override;

	void OnImGuiRender() override;

	void OnEvent(MABEngine::Events::Event& event) override;
private:
	uint32_t m_Width;
	uint32_t m_Height;

	glm::vec3 m_SolidColor1 = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_SolidColor2 = { 0.5f, 0.8f, 0.3f };
	MABEngine::Camera::OrthographicCameraController m_CameraController;

	MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_CheckerBoardTexture;
};

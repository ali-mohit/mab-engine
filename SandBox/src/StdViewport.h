#pragma once

#include <MABEngine/Core.h>
#include <MABEngine.h>

class MABENGINE_API StdViewPort : public MABEngine::Layers::Layer {
public:
	StdViewPort();
	~StdViewPort();

	virtual void OnImGuiRender() override;
private:
	float m_Degree = 0;
	float m_CameraRotationZSpeed = 180.0f;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeed = 10.0f;

	MABEngine::Ref<MABEngine::Renderer::Shader> m_Shader;
	MABEngine::Ref<MABEngine::Renderer::VertexArray> m_VertexArray;

	MABEngine::Camera::OrthographicCamera m_Camera;
};
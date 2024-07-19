#pragma once

#include <MABEngine/Core/Base.h>
#include <MABEngine.h>

namespace SandBoxLayers
{
	class MABENGINE_API DockSpaceView : public MABEngine::Layers::Layer {
	public:
		DockSpaceView(uint32_t width, uint32_t height);
		~DockSpaceView();

		void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

		virtual void OnAttach() override;

		virtual void OnImGuiRender() override;

		void OnEvent(MABEngine::Events::Event& event) override;
	private:
		void MakeSettingWindow();
	private:
		uint32_t m_Width;
		uint32_t m_Height;

		glm::vec3 m_SolidColor1 = { 0.2f, 0.3f, 0.8f };
		float m_rotationBox = 0.0f;
		bool IsDockSapceActive = true;
		bool m_ShowSettingBox = true;

		MABEngine::Camera::OrthographicCameraController m_CameraController;

		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_CheckerBoardTexture;
		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_SpriteSheet;
		MABEngine::Core::Ref<MABEngine::Textures::SubTexture2D> m_Castle;
	};
}
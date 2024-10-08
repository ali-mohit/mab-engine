#pragma once

#include <MABEngine/Core/Base.h>
#include <MABEngine.h>

namespace LightsAndShadows {
	namespace Layers
	{
		class MABENGINE_API MainLayer : public MABEngine::Layers::Layer {
		public:
			MainLayer(uint32_t width, uint32_t height);
			~MainLayer();

			void OnUpdate(MABEngine::Core::EngineTimeStep ts) override;

			virtual void OnAttach() override;

			virtual void OnImGuiRender() override;

			void OnEvent(MABEngine::Events::Event& event) override;
		private:
			void MakeSettingWindow();
			void MakeViewWindow();
		private:
			uint32_t m_Width;
			uint32_t m_Height;

			uint32_t m_ViewportWidth = 0;
			uint32_t m_ViewportHeight = 0;

			bool m_IsViewFocused = false;
			bool m_IsMouseHover = false;

			glm::vec3 m_SolidColor1 = { 0.2f, 0.3f, 0.8f };
			float m_rotationBox = 0.0f;
			bool m_IsDockSapceActive = true;
			bool m_ShowSettingBox = true;

			MABEngine::Camera::OrthographicCameraController m_OrthoCameraController;
			MABEngine::Camera::PerspectiveCameraController m_PersCameraController;

			MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_CheckerBoardTexture;
			MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_SpriteSheet;
			MABEngine::Core::Ref<MABEngine::Textures::SubTexture2D> m_Castle;

			MABEngine::Core::Ref<MABEngine::Scene::SceneManagement> m_Scene;
			MABEngine::Scene::Entity m_Square01;
			MABEngine::Scene::Entity m_Square02;

			MABEngine::Core::Ref<MABEngine::Renderer::FrameBuffer> m_FramBuffer;
		};
	}
}

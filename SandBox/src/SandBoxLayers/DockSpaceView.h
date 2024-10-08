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
		void MakeViewWindow();
		void SetRenderViewSize();
	private:
		uint32_t m_Width;
		uint32_t m_Height;

		uint32_t m_ViewportWidth;
		uint32_t m_ViewportHeight;
		ImVec2 m_CurrentSize;
		

		glm::vec3 m_SolidColor1 = { 0.2f, 0.3f, 0.8f };
		float m_rotationBox = 0.0f;
		bool m_IsDockSapceActive = true;
		bool m_ShowSettingBox = true;
		bool m_RenderViewSizeChanged = true;

		MABEngine::Camera::OrthographicCameraController m_OrtogonalCameraController;
		MABEngine::Camera::PerspectiveCameraController m_PerspectiveCameraController;

		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_CheckerBoardTexture;
		MABEngine::Core::Ref<MABEngine::Textures::Texture2D> m_SpriteSheet;
		MABEngine::Core::Ref<MABEngine::Textures::SubTexture2D> m_Castle;

		MABEngine::Core::Ref<MABEngine::Renderer::FrameBuffer> m_FramBuffer;
	};
}
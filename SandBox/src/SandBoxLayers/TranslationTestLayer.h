#pragma once

#include <MABEngine.h>

#include <glm/glm.hpp>

namespace SandBoxLayers
{
	class TranslationTestLayer : public MABLayers::Layer {
	public:
		TranslationTestLayer(uint32_t width, uint32_t height);
		~TranslationTestLayer();

		void OnUpdate(MABCore::EngineTimeStep ts) override;

		void OnImGuiRender() override;

		void OnEvent(MABEvents::Event& event) override;
	private:
		void CreateBoxObject();
		void CreateTriangleObject();
	private:
		uint32_t m_Width;
		uint32_t m_Height;

		MABRenderer::ShaderLibrary m_ShaderLib;

		MABCore::Ref<MABTextures::Texture2D> m_TextureCheckerBoard;

		MABCore::Ref<MABRenderer::Shader> m_SolidColorShader;
		MABCore::Ref<MABRenderer::VertexArray> m_BoxFacesVertexArray;
		MABCore::Ref<MABRenderer::VertexArray> m_BoxEdgesVertexArray;
		MABCore::Ref<MABRenderer::VertexArray> m_TriangleVertexArray;

		MABCamera::PerspectiveCameraController m_CameraController;
	};
}
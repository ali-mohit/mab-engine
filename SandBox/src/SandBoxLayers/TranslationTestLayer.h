#pragma once

#include <MABEngine.h>

#include <glm/glm.hpp>

#include "Tools/TranslationModule.h"

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
		void DrawBox(MABCore::Ref<MABRenderer::Shader> faceShader, MABCore::Ref<MABRenderer::Shader> lineShader);

		void CreateTriangleObject();

		void CreateGrid();
		void DrawGrid(MABCore::Ref<MABRenderer::Shader> lineShader);

		void CreateGizmo();
		void DrawGizmo(MABCore::Ref<MABRenderer::Shader> lineShader, glm::mat4 tranlation);
	private:
		uint32_t m_Width;
		uint32_t m_Height;

		MABRenderer::ShaderLibrary m_ShaderLib;

		MABCore::Ref<MABTextures::Texture2D> m_TextureCheckerBoard;

		MABCore::Ref<MABRenderer::Shader> m_SolidColorShader;
		
		MABCore::Ref<MABRenderer::VertexArray> m_BoxFacesVertexArray;
		MABCore::Ref<MABRenderer::VertexArray> m_BoxEdgesVertexArray;

		MABCore::Ref<MABRenderer::VertexArray> m_TriangleVertexArray;

		MABCore::Ref<MABRenderer::VertexArray> m_GridVertexArray;

		MABCore::Ref<MABRenderer::VertexArray> m_GizmoVertexArray;

		MABCamera::PerspectiveCameraController m_CameraController;


		glm::vec4 m_XColor = { 0.929f, 0.109f, 0.141f, 1.0f };
		glm::vec4 m_YColor = { 0.109f, 0.929f, 0.141f, 1.0f };
		glm::vec4 m_ZColor = { 0.050f, 0.654f, 0.909f, 1.0f };

		Tools::TranslationModule m_Child01;
		glm::vec3 m_Child01Pos = glm::vec3(0.0f);
		glm::vec3 m_Child01Rot = glm::vec3(0.0f);
		glm::vec3 m_Child01Scale = glm::vec3(1.0f);
		bool m_Child01AttachToParent01 = false;

		Tools::TranslationModule m_Parent01;
		glm::vec3 m_Parent01Pos = glm::vec3(0.0f);
		glm::vec3 m_Parent01Rot = glm::vec3(0.0f);
		glm::vec3 m_Parent01Scale = glm::vec3(1.0f);

	};
}
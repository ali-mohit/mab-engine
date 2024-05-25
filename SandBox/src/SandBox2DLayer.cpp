#include <mabengine_pch.h>
#include <MABEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "SandBox2DLayer.h"


SandBox2DLayer::SandBox2DLayer(uint32_t width, uint32_t height)
	:Layer("2D Layer Test"),
	m_Width(width),
	m_Height(height),
	m_CameraController(height != 0 ? (float)width / (float)height : 1.0f, 1.0f)
{
	m_CameraController.SetZRotationEnabled(true);

	CreateRectangleObject();
}

void SandBox2DLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
{
	auto solidShader = m_ShaderLib.GetShader("solid");

	m_CameraController.OnUpdate(ts);

	MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	MABEngine::Renderer::RenderCommand::Clear();

	MABEngine::Renderer::EngineRenderer::BeginScene(m_CameraController.GetCamera());

	//Submit Rectangle
	glm::mat4 rectangletransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	MABEngine::Renderer::EngineRenderer::Submit(solidShader, m_RectangleVertexArray, rectangletransform);

	MABEngine::Renderer::EngineRenderer::EndScene();

	//Renderer::EngineRenderer::Flush();
}

void SandBox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	if (ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SolidColor)))
	{
		SetRectangleColor();
	}
	ImGui::End();
}

void SandBox2DLayer::OnEvent(MABEngine::Events::Event& event)
{
	m_CameraController.OnEvent(event);
}

void SandBox2DLayer::CreateRectangleObject()
{
	m_RectangleVertexArray = MABEngine::Renderer::VertexArray::Create();
	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};

	MABEngine::Core::Ref<MABEngine::Renderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(MABEngine::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	MABEngine::Renderer::BufferLayout layout = {
		{ MABEngine::Renderer::ShaderDataType::Float3, "a_Position"},
	};
	vertexBuffer->SetLayout(layout);
	m_RectangleVertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };
	MABEngine::Core::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_RectangleVertexArray->AddIndexBuffer(indexBuffer);

	MABEngine::Renderer::ShaderPackageFile packageInfo(
		"solid",
		"assets/shaders/solid/",
		"solid."
	);
	auto solidShader = m_ShaderLib.Load(packageInfo);

	solidShader->Bind();
	solidShader->SetFloat4(
		"u_UniqueColor", glm::vec4(m_SolidColor, 1.0f)
	);
	solidShader->UnBind();

}

void SandBox2DLayer::SetRectangleColor()
{
	if (!m_ShaderLib.ShaderExists("solid"))
		return;

	auto solidShader = m_ShaderLib.GetShader("solid");
	solidShader->Bind();
	solidShader->SetFloat4(
		"u_UniqueColor", glm::vec4(m_SolidColor, 1.0f)
	);
	solidShader->UnBind();
}


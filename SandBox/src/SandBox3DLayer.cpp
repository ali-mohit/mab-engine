#include <mabengine_pch.h>
#include <MABEngine.h>
#include <MABEngine/Core/TimeStep.h>

#include <glm/gtc/matrix_transform.hpp>


#include "SandBox3DLayer.h"


SandBox3DLayer::SandBox3DLayer(uint32_t width, uint32_t height)
	:Layer("Example"),
	m_Width(width), 
	m_Height(height), 
	m_CameraController(height != 0 ? (float)width/(float)height: 1.0f, 1.0f)
{
	m_CameraController.SetZRotationEnabled(true);

	CreateTriangleObject();
	CreateRectangleObject();
}

void SandBox3DLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
{
	auto textureShader = m_ShaderLib.GetShader("basic-texture");

	m_CameraController.OnUpdate(ts);

	MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	MABEngine::Renderer::RenderCommand::Clear();

	MABEngine::Renderer::EngineRenderer::BeginScene(m_CameraController.GetCamera());

	//Submit Triangle
	glm::mat4 triangleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	triangleTransform = glm::translate(triangleTransform, glm::vec3(1.5, 0.0, -1.0));
	MABEngine::Renderer::EngineRenderer::Submit(m_SolidColorShader, m_TriangleVertexArray, triangleTransform);
	

	//Submit Rectangle
	glm::mat4 textureCheckerBoardtransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	glm::mat4 texturelogotransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

	m_TextureCheckerBoard->Bind();
	MABEngine::Renderer::EngineRenderer::Submit(textureShader, m_RectangleVertexArray, textureCheckerBoardtransform);
	textureShader->SetFloat4(
		"u_Color", glm::vec4(0.3f, 0.2f, 0.8f, 1.0f)
	);

	m_TextureMabLogo->Bind();
	MABEngine::Renderer::EngineRenderer::Submit(textureShader, m_RectangleVertexArray, texturelogotransform);

	MABEngine::Renderer::EngineRenderer::EndScene();

	//Renderer::EngineRenderer::Flush();
}

void SandBox3DLayer::OnImGuiRender()
{

}

void SandBox3DLayer::OnEvent(MABEngine::Events::Event& event)
{
	m_CameraController.OnEvent(event);
}

void SandBox3DLayer::CreateTriangleObject()
{
	m_TriangleVertexArray = MABEngine::Renderer::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.1f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
	};

	MABEngine::Core::Ref<MABEngine::Renderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(MABEngine::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	MABEngine::Renderer::BufferLayout layout = {
		{ MABEngine::Renderer::ShaderDataType::Float3, "a_Position"},
		{ MABEngine::Renderer::ShaderDataType::Float4, "a_Color"},
	};
	vertexBuffer->SetLayout(layout);
	m_TriangleVertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[3] = { 0, 1, 2 };
	MABEngine::Core::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_TriangleVertexArray->AddIndexBuffer(indexBuffer);

	MABEngine::Renderer::ShaderPackageFile packageInfo(
		"solidColor",
		"assets/shaders/solid/",
		"solid."
	);
	m_SolidColorShader = MABEngine::Renderer::Shader::Create(packageInfo);

	m_SolidColorShader->Bind();
	m_SolidColorShader->SetFloat4(
		"u_UniqueColor", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f)
	);
	m_SolidColorShader->UnBind();
}

void SandBox3DLayer::CreateRectangleObject()
{
	m_RectangleVertexArray = MABEngine::Renderer::VertexArray::Create();
	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	MABEngine::Core::Ref<MABEngine::Renderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(MABEngine::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	MABEngine::Renderer::BufferLayout layout = {
		{ MABEngine::Renderer::ShaderDataType::Float3, "a_Position"},
		{ MABEngine::Renderer::ShaderDataType::Float2, "a_TexCoord"},
	};
	vertexBuffer->SetLayout(layout);
	m_RectangleVertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };
	MABEngine::Core::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_RectangleVertexArray->AddIndexBuffer(indexBuffer);

	MABEngine::Renderer::ShaderPackageFile packageInfo(
		"basic-texture",
		"assets/shaders/basic-texture/",
		"basic-texture."
	);
	auto m_TextureShader = m_ShaderLib.Load(packageInfo);

	m_TextureCheckerBoard = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureMabLogo = MABEngine::Textures::Texture2D::Create("assets/textures/MabLogo_1080_Color.png");

	m_TextureShader->Bind();
	m_TextureShader->SetInt("u_Texture", 0);

}

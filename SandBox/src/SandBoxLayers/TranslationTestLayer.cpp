#include "mabengine_pch.h"

#include "SandBoxLayers/TranslationTestLayer.h"

#include <imgui.h>

namespace SandBoxLayers
{
	TranslationTestLayer::TranslationTestLayer(uint32_t width, uint32_t height)
		:Layer("Translation Test"),
		m_Width(width),
		m_Height(height)
	{
		m_CameraController = MABEngine::Camera::PerspectiveCameraController(
			MABEngine::Camera::CameraSpecification::CreateTargetCamera(
				45.0f, 0.01, 100.0f,
				width, height,
				{ 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, MABEngine::Camera::PerspectiveCamera::WORLD_UP
			)
		);

		CreateBoxObject();
		CreateTriangleObject();
	}

	TranslationTestLayer::~TranslationTestLayer()
	{
	}

	void TranslationTestLayer::OnUpdate(MABCore::EngineTimeStep ts)
	{
		auto translateCtrl = m_ShaderLib.GetShader("TranslateCtrl");

		m_CameraController.OnUpdate(ts);

		MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		MABEngine::Renderer::RenderCommand::Clear();

		
		MABRenderer::EngineRenderer::BeginScene(m_CameraController.GetCamera());

		//Submit Triangle
		glm::mat4 triangleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		triangleTransform = glm::translate(triangleTransform, glm::vec3(1.5, 0.0, -1.0));
		MABEngine::Renderer::EngineRenderer::Submit(m_SolidColorShader, m_TriangleVertexArray, triangleTransform);/**/

		glm::mat4 squareTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		squareTransform = glm::translate(squareTransform, glm::vec3(0.0f, 0.0f, 0.0f));

		//Submit Square faces
		translateCtrl->Bind();
		translateCtrl->SetInt("u_ShowEdge", 0);
		MABEngine::Renderer::EngineRenderer::Submit(translateCtrl, m_BoxFacesVertexArray, squareTransform);

		//Submit Square edges
		translateCtrl->Bind();
		translateCtrl->SetInt("u_ShowEdge", 1);
		MABEngine::Renderer::EngineRenderer::SubmitLines(translateCtrl, m_BoxEdgesVertexArray, squareTransform);


		MABEngine::Renderer::EngineRenderer::EndScene();
	}

	void TranslationTestLayer::OnImGuiRender()
	{
	}

	void TranslationTestLayer::OnEvent(MABEvents::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

	void TranslationTestLayer::CreateBoxObject()
	{
		m_BoxFacesVertexArray = MABRenderer::VertexArray::Create();
		m_BoxEdgesVertexArray = MABRenderer::VertexArray::Create();

		float vertices[8 * 9] = {
			// Vertex positions       // Texture UV  // Vertex color
			-1.0f, -1.0f, -1.0f,      0.0f, 0.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 1
			 1.0f, -1.0f, -1.0f,      1.0f, 0.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 2
			 1.0f,  1.0f, -1.0f,      1.0f, 1.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 3
			-1.0f,  1.0f, -1.0f,      0.0f, 1.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 4
			-1.0f, -1.0f,  1.0f,      0.0f, 0.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 5
			 1.0f, -1.0f,  1.0f,      1.0f, 0.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 6
			 1.0f,  1.0f,  1.0f,      1.0f, 1.0f,	 0.4f, 0.4f, 0.4f, 1.0f, // Vertex 7
			-1.0f,  1.0f,  1.0f,      0.0f, 1.0f, 	 0.4f, 0.4f, 0.4f, 1.0f  // Vertex 8
		};

		unsigned int faces[36] = {
			// Back face
			0, 1, 2,
			2, 3, 0,
			// Front face
			4, 5, 6,
			6, 7, 4,
			// Left face
			0, 4, 7,
			7, 3, 0,
			// Right face
			1, 5, 6,
			6, 2, 1,
			// Top face
			3, 2, 6,
			6, 7, 3,
			// Bottom face
			0, 1, 5,
			5, 4, 0
		};

		unsigned int edges[24] = {
			// Back face
			0, 1, 
			1, 2,
			2, 3,
			3, 0,
			// Front face
			4, 5, 
			5, 6,
			6, 7, 
			7, 4,
			// Left face
			0, 4,
			7, 3,
			// Right face
			1, 5,
			6, 2
		};

		MABCore::Ref<MABRenderer::VertexBuffer> squareVertex;
		squareVertex.reset(MABRenderer::VertexBuffer::Create(vertices, sizeof(vertices)));
		MABRenderer::BufferLayout layout = {
			{ MABRenderer::ShaderDataType::Float3, "a_Position" },
			{ MABRenderer::ShaderDataType::Float2, "a_TextureCoordinate" },
			{ MABRenderer::ShaderDataType::Float4, "a_Color" }
		};
		squareVertex->SetLayout(layout);
		
		MABCore::Ref<MABRenderer::IndexBuffer> indexFacesBuffer;
		indexFacesBuffer.reset(MABRenderer::IndexBuffer::Create(faces, sizeof(faces) / sizeof(uint32_t)));
		
		MABCore::Ref<MABRenderer::IndexBuffer> indexEdgesBuffer;
		indexEdgesBuffer.reset(MABRenderer::IndexBuffer::Create(edges, sizeof(edges) / sizeof(uint32_t)));


		m_BoxFacesVertexArray->AddVertexBuffer(squareVertex);
		m_BoxFacesVertexArray->SetIndexBuffer(indexFacesBuffer);
		

		m_BoxEdgesVertexArray->AddVertexBuffer(squareVertex);
		m_BoxEdgesVertexArray->SetIndexBuffer(indexEdgesBuffer);

		MABEngine::Renderer::ShaderPackageFile packageInfo(
			"TranslateCtrl",
			"assets/shaders/translate-ctrl/",
			"translate-ctrl."
		);
		auto m_shader = m_ShaderLib.Load(packageInfo);
		
		m_shader->Bind();
		m_shader->SetInt("u_ShowEdge", 0);
		m_shader->SetFloat4("u_EdgeColor", glm::vec4{ 0.1f, 0.1f, 0.1f, 1.0f });

	}

	void TranslationTestLayer::CreateTriangleObject()
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
		m_TriangleVertexArray->SetIndexBuffer(indexBuffer);

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

}
#include <mabengine_pch.h>
#include <MABEngine.h>

#include "ExampleLayer.h"
#include "MABEngine/Core/TimeStep.h"

#include <glm/gtc/matrix_transform.hpp>

// TODO: Must be removed
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/Textures/OpenGLTexture2D.h"


ExampleLayer::ExampleLayer(uint32_t width, uint32_t height)
	:Layer("Example"),
	m_Width(width), 
	m_Height(height), 
	m_CameraController(height != 0 ? (float)width/(float)height: 1.0f, 1.0f)
{
	m_CameraController.SetZRotationEnabled(true);

	CreateTriangleObject();
	CreateRectangleObject();
}

void ExampleLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	MABEngine::Renderer::RenderCommand::Clear();

	MABEngine::Renderer::EngineRenderer::BeginScene(m_CameraController.GetCamera());

	
	std::dynamic_pointer_cast<MABEngine::Renderer::OpenGLShader>(m_TextureShader)->UploadUniformFloat4(
		"u_Color", glm::vec4(0.3f, 0.2f, 0.8f, 1.0f)
	);
	glm::mat4 textureCheckerBoardtransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	glm::mat4 texturelogotransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));

	m_TextureCheckerBoard->Bind();
	MABEngine::Renderer::EngineRenderer::Submit(m_TextureShader, m_RectangleVertexArray, textureCheckerBoardtransform);


	m_TextureMabLogo->Bind();
	MABEngine::Renderer::EngineRenderer::Submit(m_TextureShader, m_RectangleVertexArray, texturelogotransform);


	//Submit Triangle
	std::dynamic_pointer_cast<MABEngine::Renderer::OpenGLShader>(m_SolidColorShader)->UploadUniformFloat4(
		"u_UniqueColor", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f)
	);
	glm::mat4 triangleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	triangleTransform = glm::translate(triangleTransform, glm::vec3(1.0, 1.0, 0));
	MABEngine::Renderer::EngineRenderer::Submit(m_SolidColorShader, m_TriangleVertexArray, triangleTransform);

	MABEngine::Renderer::EngineRenderer::EndScene();

	//Renderer::EngineRenderer::Flush();
}

void ExampleLayer::OnImGuiRender()
{

}

void ExampleLayer::OnEvent(MABEngine::Events::Event& event)
{
	m_CameraController.OnEvent(event);
}

void ExampleLayer::CreateTriangleObject()
{
	m_TriangleVertexArray = MABEngine::Renderer::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.1f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
	};

	MABEngine::Ref<MABEngine::Renderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(MABEngine::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	MABEngine::Renderer::BufferLayout layout = {
		{ MABEngine::Renderer::ShaderDataType::Float3, "a_Position"},
		{ MABEngine::Renderer::ShaderDataType::Float4, "a_Color"},
	};
	vertexBuffer->SetLayout(layout);
	m_TriangleVertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[3] = { 0, 1, 2 };
	MABEngine::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_TriangleVertexArray->AddIndexBuffer(indexBuffer);

	std::string vertextSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform	mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			uniform vec4 u_UniqueColor;

			void main() {
				color = u_UniqueColor;
			}
		)";

	m_SolidColorShader = MABEngine::Renderer::Shader::Create(vertextSrc, fragmentSrc);
}

void ExampleLayer::CreateRectangleObject()
{
	m_RectangleVertexArray = MABEngine::Renderer::VertexArray::Create();
	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};

	MABEngine::Ref<MABEngine::Renderer::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(MABEngine::Renderer::VertexBuffer::Create(vertices, sizeof(vertices)));
	MABEngine::Renderer::BufferLayout layout = {
		{ MABEngine::Renderer::ShaderDataType::Float3, "a_Position"},
		{ MABEngine::Renderer::ShaderDataType::Float2, "a_TexCoord"},
	};
	vertexBuffer->SetLayout(layout);
	m_RectangleVertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };
	MABEngine::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_RectangleVertexArray->AddIndexBuffer(indexBuffer);

	std::string vertextSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform	mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec2 v_TexCoord;

			void main() {
				v_Position = a_Position;
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main() {
				//color = u_Color;
				//color = vec4(v_Position, 1.0f);
				//color = vec4(v_TexCoord, 0.0f, 1.0f);
				color = texture(u_Texture, v_TexCoord);
			}
		)";

	m_TextureShader = MABEngine::Renderer::Shader::Create(vertextSrc, fragmentSrc);

	m_TextureCheckerBoard = MABEngine::Textures::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureMabLogo = MABEngine::Textures::Texture2D::Create("assets/textures/MabLogo_1080_Color.png");

	std::dynamic_pointer_cast<MABEngine::Renderer::OpenGLShader>(m_TextureShader)->Bind();
	std::dynamic_pointer_cast<MABEngine::Renderer::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

}

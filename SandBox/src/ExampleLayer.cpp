#include <mabengine_pch.h>
#include <MABEngine.h>

#include "ExampleLayer.h"
#include "MABEngine/Core/TimeStep.h"

// TODO: Must be removed
#include "Platform/OpenGL/OpenGLShader.h"


ExampleLayer::ExampleLayer()
	:Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
{
	m_VertexArray.reset(MABEngine::Renderer::VertexArray::Create());

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
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	// Index Buffer
	unsigned int indices[3] = { 0, 1, 2 };
	MABEngine::Ref<MABEngine::Renderer::IndexBuffer> indexBuffer;
	indexBuffer.reset(MABEngine::Renderer::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->AddIndexBuffer(indexBuffer);

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
			
			uniform vec4 u_Color;

			void main() {
				color = u_Color;
			}
		)";

	m_Shader.reset(MABEngine::Renderer::Shader::Create(vertextSrc, fragmentSrc));
}

void ExampleLayer::OnUpdate(MABEngine::Core::EngineTimeStep ts)
{
	if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_Left))
		m_CameraPosition.x -= m_CameraSpeed * ts;
	else if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_Right))
		m_CameraPosition.x += m_CameraSpeed * ts;
	
	if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_Up))
		m_CameraPosition.y += m_CameraSpeed * ts;
	else if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_Down))
		m_CameraPosition.y -= m_CameraSpeed * ts;

	if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_A))
		m_Degree += m_CameraRotationZSpeed * ts;
	else if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_Z))
		m_Degree -= m_CameraRotationZSpeed * ts;

	if (MABEngine::Inputs::Input::IsKeyPressed(MABEngine::Inputs::Mab_Key_F))
	{
		m_Degree = 0;
		m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	}


	m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotationZ(m_Degree);

	MABEngine::Renderer::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	MABEngine::Renderer::RenderCommand::Clear();

	MABEngine::Renderer::EngineRenderer::BeginScene(m_Camera);

	std::dynamic_pointer_cast<MABEngine::Renderer::OpenGLShader>(m_Shader)->UploadUniformFloat4(
		"u_Color", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f)
	);
	MABEngine::Renderer::EngineRenderer::Submit(m_Shader, m_VertexArray);

	MABEngine::Renderer::EngineRenderer::EndScene();

	//Renderer::EngineRenderer::Flush();
}

void ExampleLayer::OnImGuiRender()
{

}

void ExampleLayer::OnEvent(MABEngine::Events::Event& event)
{
}

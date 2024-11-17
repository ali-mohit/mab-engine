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
				45.0f, 0.01, 1000.0f,
				width, height,
				{ 20.0f, 15.0f, 20.0f }, { 0.0f, 0.0f, 0.0f }, MABEngine::Camera::PerspectiveCamera::WORLD_UP
			)
		);

		MABEngine::Renderer::ShaderPackageFile translatePackageInfo(
			"TranslateCtrl",
			"assets/shaders/translate-ctrl/",
			"translate-ctrl."
		);
		auto m_shader = m_ShaderLib.Load(translatePackageInfo);

		MABEngine::Renderer::ShaderPackageFile linePackageInfo(
			"Lines",
			"assets/shaders/lines/",
			"lines."
		);
		auto m_lineShader = m_ShaderLib.Load(linePackageInfo);
		MABEngine::Renderer::EngineRenderer::SetLineWidth(2.0f);

		CreateBoxObject();
		CreateTriangleObject();
		CreateGrid();
		CreateGizmo();
	}

	TranslationTestLayer::~TranslationTestLayer()
	{
	}

	void TranslationTestLayer::OnUpdate(MABCore::EngineTimeStep ts)
	{
		auto translateCtrl = m_ShaderLib.GetShader("TranslateCtrl");
		auto lineShader = m_ShaderLib.GetShader("Lines");

		m_CameraController.OnUpdate(ts);

		MABEngine::Renderer::RenderCommand::SetClearColor({ 0.36f, 0.36f, 0.36f, 1 });
		MABEngine::Renderer::RenderCommand::Clear();

		
		MABRenderer::EngineRenderer::BeginScene(m_CameraController.GetCamera());

		//Submit Triangle
		/*glm::mat4 triangleTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		triangleTransform = glm::translate(triangleTransform, glm::vec3(1.5, 0.0, -1.0));
		MABEngine::Renderer::EngineRenderer::Submit(m_SolidColorShader, m_TriangleVertexArray, triangleTransform);/**/

		DrawGrid(lineShader);

		DrawBox(translateCtrl, lineShader);

		DrawGizmo(lineShader, m_Child01.GetGlobalTranslation());
		
		DrawGizmo(lineShader, m_Parent01.GetGlobalTranslation());

		MABEngine::Renderer::EngineRenderer::EndScene();
	}

	void TranslationTestLayer::OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::PushID(0);
		// Position control
		if (ImGui::DragFloat3("Position", glm::value_ptr(m_Child01Pos), 0.1f)) {
			m_Child01.SetPosition(m_Child01Pos);
		}

		// Rotation control (in degrees)
		if (ImGui::DragFloat3("Rotation (Degrees)", glm::value_ptr(m_Child01Rot), 0.1f)) {
			m_Child01.SetRotationInDegree(m_Child01Rot); // Set rotation in degrees
		}

		// Scale control
		if (ImGui::DragFloat3("Scale", glm::value_ptr(m_Child01Scale), 0.1f)) {
			m_Child01.SetScale(m_Child01Scale);
		}

		//m_Child01AttachToParent01
		if (ImGui::Checkbox("Attaching to Parent01", &m_Child01AttachToParent01)) {
			if (m_Child01AttachToParent01)
				m_Parent01.AddChild(&m_Child01);
			else
				m_Child01.SetParent(nullptr);

			m_Child01Pos = m_Child01.GetPosition();
			m_Child01Rot = m_Child01.GetRotation();
			m_Child01Scale = m_Child01.GetScale();

		}
		ImGui::PopID();

		ImGui::Separator();
		
		ImGui::SeparatorText("Parent 01");

		ImGui::PushID(1);
		// Position control
		if (ImGui::DragFloat3("Position", glm::value_ptr(m_Parent01Pos), 0.1f)) {
			m_Parent01.SetPosition(m_Parent01Pos);
		}

		// Rotation control (in degrees)
		if (ImGui::DragFloat3("Rotation (Degrees)", glm::value_ptr(m_Parent01Rot), 0.1f)) {
			m_Parent01.SetRotationInDegree(m_Parent01Rot); // Set rotation in degrees
		}

		// Scale control
		if (ImGui::DragFloat3("Scale", glm::value_ptr(m_Parent01Scale), 0.1f)) {
			m_Parent01.SetScale(m_Parent01Scale);
		}
		ImGui::PopID();

		ImGui::End();
	}

	void TranslationTestLayer::OnEvent(MABEvents::Event& event)
	{
		m_CameraController.OnEvent(event);
	}

	void TranslationTestLayer::CreateBoxObject()
	{
		m_BoxFacesVertexArray = MABRenderer::VertexArray::Create();
		m_BoxEdgesVertexArray = MABRenderer::VertexArray::Create();

		{
			float vertices[8 * 9] = {
				// Vertex positions       // Texture UV  // Vertex color
				-1.0f, -1.0f, -1.0f,      0.0f, 0.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 1
				 1.0f, -1.0f, -1.0f,      1.0f, 0.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 2
				 1.0f,  1.0f, -1.0f,      1.0f, 1.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 3
				-1.0f,  1.0f, -1.0f,      0.0f, 1.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 4
				-1.0f, -1.0f,  1.0f,      0.0f, 0.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 5
				 1.0f, -1.0f,  1.0f,      1.0f, 0.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 6
				 1.0f,  1.0f,  1.0f,      1.0f, 1.0f,	 0.63f, 0.63f, 0.63f, 1.0f, // Vertex 7
				-1.0f,  1.0f,  1.0f,      0.0f, 1.0f, 	 0.63f, 0.63f, 0.63f, 1.0f  // Vertex 8
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

			MABCore::Ref<MABRenderer::VertexBuffer> squareVertex;
			squareVertex.reset(MABRenderer::VertexBuffer::Create(vertices, sizeof(vertices)));
			MABRenderer::BufferLayout layout = {
				{ MABRenderer::ShaderDataType::Float3, "a_Position" },
				{ MABRenderer::ShaderDataType::Float2, "a_TextureCoordinate" },
				{ MABRenderer::ShaderDataType::Float4, "a_Color" }
			};
			squareVertex->SetLayout(layout);
			m_BoxFacesVertexArray->AddVertexBuffer(squareVertex);

			MABCore::Ref<MABRenderer::IndexBuffer> indexFacesBuffer;
			indexFacesBuffer.reset(MABRenderer::IndexBuffer::Create(faces, sizeof(faces) / sizeof(uint32_t)));
			m_BoxFacesVertexArray->SetIndexBuffer(indexFacesBuffer);

			m_BoxFacesVertexArray->UnBind();
		}
		
		{
			float vertices2[8 * 7] = {
				// Vertex positions       // Vertex color
				-1.0f, -1.0f, -1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 1
				 1.0f, -1.0f, -1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 2
				 1.0f,  1.0f, -1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 3
				-1.0f,  1.0f, -1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 4
				-1.0f, -1.0f,  1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 5
				 1.0f, -1.0f,  1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 6
				 1.0f,  1.0f,  1.0f,      0.1f, 0.1f, 0.1f, 1.0f, // Vertex 7
				-1.0f,  1.0f,  1.0f,      0.1f, 0.1f, 0.1f, 1.0f  // Vertex 8
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

			MABCore::Ref<MABRenderer::VertexBuffer> squareVertex2;
			squareVertex2.reset(MABRenderer::VertexBuffer::Create(vertices2, sizeof(vertices2)));
			MABRenderer::BufferLayout layout2 = {
				{ MABRenderer::ShaderDataType::Float3, "a_Position" },
				{ MABRenderer::ShaderDataType::Float4, "a_Color" }
			};
			squareVertex2->SetLayout(layout2);
			m_BoxEdgesVertexArray->AddVertexBuffer(squareVertex2);

			MABCore::Ref<MABRenderer::IndexBuffer> indexEdgesBuffer;
			indexEdgesBuffer.reset(MABRenderer::IndexBuffer::Create(edges, sizeof(edges) / sizeof(uint32_t)));
			m_BoxEdgesVertexArray->SetIndexBuffer(indexEdgesBuffer);

			m_BoxEdgesVertexArray->UnBind();
		}
	}

	void TranslationTestLayer::DrawBox(MABCore::Ref < MABRenderer::Shader> faceShader, MABCore::Ref < MABRenderer::Shader> lineShader) {
		glm::mat4 squareTransform = m_Child01.GetGlobalTranslation();

		//Submit Square faces
		MABEngine::Renderer::EngineRenderer::Submit(faceShader, m_BoxFacesVertexArray, squareTransform);

		MABEngine::Renderer::EngineRenderer::SetLineWidth(1.0f);
		//Submit Square edges
		MABEngine::Renderer::EngineRenderer::SubmitLines(lineShader, m_BoxEdgesVertexArray, squareTransform);

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

	void TranslationTestLayer::CreateGrid()
	{
		m_GridVertexArray = MABEngine::Renderer::VertexArray::Create();

		std::vector<float> vertices;
		std::vector<uint32_t> edges;
		float begin = -15.0f;

		float xS = begin;
		float xE = std::abs(begin);

		float zS = begin;
		float zE = std::abs(begin);

		float colorS = 0.3f;
		float colorM = 0.7f;
		glm::vec4 xColor = m_XColor;
		glm::vec4 yColor = m_YColor;
		glm::vec4 zColor = m_ZColor;
		glm::vec4 nColor = { 0.250f, 0.25f, 0.25f, 1.0f };
		//Vertically
		float edgeCount = 0;
		for (int i = 0; i <= std::abs(begin) * 2; i++) {
			float z = begin + i;

			glm::vec4 color = (z == 0 ? xColor : nColor);
			//Vertex 01
			{
				//Position
				vertices.push_back(xS);
				vertices.push_back(0.0f);
				vertices.push_back(z);

				//Color
				vertices.push_back(color.r);
				vertices.push_back(color.g);
				vertices.push_back(color.b);
				vertices.push_back(color.a);
			}

			//Vertex02
			{
				//Position
				vertices.push_back(xE);
				vertices.push_back(0.0f);
				vertices.push_back(z);

				//Color
				vertices.push_back(color.r);
				vertices.push_back(color.g);
				vertices.push_back(color.b);
				vertices.push_back(color.a);
			}

			edges.push_back(edgeCount);
			edges.push_back(edgeCount + 1);

			edgeCount+=2;
		}

		//Horizantally
		for (int i = 0; i <= std::abs(begin) * 2; i++) {
			float x = begin + i;
			glm::vec4 color = (x == 0 ? zColor : nColor);
			//Vertex 01
			{
				//Position
				vertices.push_back(x);
				vertices.push_back(0.0f);
				vertices.push_back(zS);

				//Color
				vertices.push_back(color.r);
				vertices.push_back(color.g);
				vertices.push_back(color.b);
				vertices.push_back(color.a);
			}

			//Vertex02
			{
				//Position
				vertices.push_back(x);
				vertices.push_back(0.0f);
				vertices.push_back(zE);

				//Color
				vertices.push_back(color.r);
				vertices.push_back(color.g);
				vertices.push_back(color.b);
				vertices.push_back(color.a);
			}

			edges.push_back(edgeCount);
			edges.push_back(edgeCount + 1);

			edgeCount += 2;
		}

		MABCore::Ref<MABRenderer::VertexBuffer> squareVertex2;
		squareVertex2.reset(MABRenderer::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float)));
		MABRenderer::BufferLayout layout2 = {
			{ MABRenderer::ShaderDataType::Float3, "a_Position" },
			{ MABRenderer::ShaderDataType::Float4, "a_Color" }
		};
		squareVertex2->SetLayout(layout2);
		m_GridVertexArray->AddVertexBuffer(squareVertex2);

		MABCore::Ref<MABRenderer::IndexBuffer> indexEdgesBuffer;
		indexEdgesBuffer.reset(MABRenderer::IndexBuffer::Create(edges.data(), edges.size() ));
		m_GridVertexArray->SetIndexBuffer(indexEdgesBuffer);

		m_GridVertexArray->UnBind();
	}

	void TranslationTestLayer::DrawGrid(MABCore::Ref<MABRenderer::Shader> lineShader)
	{
		glm::mat4 gridTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		gridTransform = glm::translate(gridTransform, glm::vec3(0.0f, 0.0f, 0.0f));

		MABEngine::Renderer::EngineRenderer::SetLineWidth(1.0f);
		//Submit Grid
		MABEngine::Renderer::EngineRenderer::SubmitLines(lineShader, m_GridVertexArray, gridTransform);

	}

	void TranslationTestLayer::CreateGizmo()
	{
		m_GizmoVertexArray = MABRenderer::VertexArray::Create();

		{
			float vertices[6 * 7] = {
				 // Vertex positions       // Vertex color
				 0.0f,  0.0f,  0.0f,      m_XColor.r, m_XColor.g, m_XColor.b, m_XColor.a, // Vertex 0
				 2.0f,  0.0f,  0.0f,      m_XColor.r, m_XColor.g, m_XColor.b, m_XColor.a, // Vertex 1

				 // Vertex positions       // Vertex color
				 0.0f,  0.0f,  0.0f,      m_YColor.r, m_YColor.g, m_YColor.b, m_YColor.a, // Vertex 2
				 0.0f,  2.0f,  0.0f,      m_YColor.r, m_YColor.g, m_YColor.b, m_YColor.a, // Vertex 3

				 // Vertex positions       // Vertex color
				 0.0f,  0.0f,  0.0f,      m_ZColor.r, m_ZColor.g, m_ZColor.b, m_ZColor.a, // Vertex 4
				 0.0f,  0.0f,  2.0f,      m_ZColor.r, m_ZColor.g, m_ZColor.b, m_ZColor.a, // Vertex 5

			};

			unsigned int edges[6] = {
				// X
				0, 1,
				// Y
				2, 3,
				// Z
				4, 5
			};

			MABCore::Ref<MABRenderer::VertexBuffer> gizmo;
			gizmo.reset(MABRenderer::VertexBuffer::Create(vertices, sizeof(vertices)));
			MABRenderer::BufferLayout layout2 = {
				{ MABRenderer::ShaderDataType::Float3, "a_Position" },
				{ MABRenderer::ShaderDataType::Float4, "a_Color" }
			};
			gizmo->SetLayout(layout2);
			m_GizmoVertexArray->AddVertexBuffer(gizmo);

			MABCore::Ref<MABRenderer::IndexBuffer> indexEdgesBuffer;
			indexEdgesBuffer.reset(MABRenderer::IndexBuffer::Create(edges, sizeof(edges) / sizeof(uint32_t)));
			m_GizmoVertexArray->SetIndexBuffer(indexEdgesBuffer);

			m_GizmoVertexArray->UnBind();
		}
	}

	void TranslationTestLayer::DrawGizmo(MABCore::Ref<MABRenderer::Shader> lineShader, glm::mat4 tranlation)
	{	
		MABEngine::Renderer::EngineRenderer::SetDepthTest(false);

		//Submit Gizmo
		MABEngine::Renderer::EngineRenderer::SubmitLines(lineShader, m_GizmoVertexArray, tranlation);

		MABEngine::Renderer::EngineRenderer::SetDepthTest(true);
	}

}
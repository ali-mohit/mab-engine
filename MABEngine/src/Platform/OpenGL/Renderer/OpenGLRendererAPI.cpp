#include "mabengine_pch.h"
#include "OpenGLRendererAPI.h"

#include "MABEngine/Renderer/RenderModeType.h"
#include "MABEngine/Renderer/RenderFaceMode.h"
#include "MABEngine/Renderer/SceneDataType.h"

#include <glad/glad.h>

namespace MABEngine {

	namespace Renderer {
		void OpenGLRendererAPI::Init()
		{
			MAB_PROFILE_FUNCTION();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}
		
		uint32_t OpenGLRendererAPI::GetMaxNumberOfTextureImageUnit()
		{
			GLint maxTextureUnit = 0;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnit);
			return maxTextureUnit;
		}

		uint32_t OpenGLRendererAPI::GetMaxFrameBufferSize()
		{
			GLint maxRenderbufferSize;
			glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);

			return maxRenderbufferSize;
		}

		void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.b, color.g, color.a);
		}

		void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			glViewport(x, y, width, height);
		}
		
		void OpenGLRendererAPI::Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLRendererAPI::SetPipelineConfig(const PipelineConfig& pipelineConfig)
		{
			uint8_t renderMode = GL_FILL;
			switch (pipelineConfig.RenderMode)
			{
			case RenderModeType::Shaded:
				renderMode = GL_FILL;
				break;
			case RenderModeType::WireFrame:
				renderMode = GL_LINE;
				break;
			case RenderModeType::Vertices:
				renderMode = GL_POINT;
				break;
			default:
				MAB_CORE_ASSERT(true, "Render mode type not found");
			}

			uint8_t faceMode = GL_FRONT_AND_BACK;
			switch (pipelineConfig.FaceMode)
			{
			case RenderFaceMode::FrontFaceMode:
				faceMode = GL_FRONT;
				break;
			case RenderFaceMode::BackFaceMode:
				faceMode = GL_BACK;
				break;
			case RenderFaceMode::FrontAndBackFaceMode:
				faceMode = GL_FRONT_AND_BACK;
				break;
			default:
				MAB_CORE_ASSERT(true, "Face mode not found");
			}

			glPolygonMode(faceMode, renderMode);
		}

		void OpenGLRendererAPI::DrawIndexed(const Core::Ref<VertexArray>& vertexArray, uint32_t indexCount)
		{
			uint32_t count = indexCount > 0 ? indexCount : vertexArray->GetIndexBuffer()->GetCount();

			vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}

		void OpenGLRendererAPI::DrawLines(const Core::Ref<VertexArray>& vertexArray, uint32_t vertexCount)
		{
			uint32_t count = vertexCount > 0 ? vertexCount : vertexArray->GetIndexBuffer()->GetCount();

			vertexArray->Bind();
			glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, nullptr);
		}

	}
}
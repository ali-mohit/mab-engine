#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/RenderModeType.h"
#include "MABEngine/Renderer/RenderFaceMode.h"

#include <glm/glm.hpp>

namespace MABEngine {

	namespace Renderer {

		struct MABENGINE_API PipelineConfig {
			RenderModeType RenderMode = RenderModeType::Shaded;
			RenderFaceMode FaceMode = RenderFaceMode::FrontAndBackFaceMode;
			float PointSize = 3.0f;

			bool IsChanged = false;
		};

		struct MABENGINE_API SceneDataType {
			glm::mat4 ViewProjectionMatrix;
			
			PipelineConfig PipelineConfig;
		};
	}
}
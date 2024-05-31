#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/Shader.h"

namespace MABEngine {

	namespace Renderer {
		
		struct MABENGINE_API EngineRenderer2dStorage {
			Core::Ref<VertexArray> QuadVertexArray;
			Core::Ref<Shader> FlatColorShader;
			Core::Ref<Shader> TextureShader;
		};

	}
}
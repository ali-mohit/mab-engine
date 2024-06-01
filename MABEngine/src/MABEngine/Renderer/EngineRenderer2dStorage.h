#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Textures/Texture2D.h"

namespace MABEngine {

	namespace Renderer {
		
		struct MABENGINE_API EngineRenderer2dStorage {
			Core::Ref<VertexArray> QuadVertexArray;
			Core::Ref<Shader> TextureShader;
			Core::Ref<Textures::Texture2D> WhiteTexture;
		};

	}
}
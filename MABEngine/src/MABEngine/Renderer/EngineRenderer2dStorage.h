#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Renderer/GraphicContext.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/QuadVertexInfo.h"
#include "MABEngine/Renderer/RenderCommand.h"
#include "MABEngine/Textures/Texture2D.h"

#include <map>

namespace MABEngine {

	namespace Renderer {
		
		struct MABENGINE_API EngineRenderer2dStorage {
			const uint32_t MAX_QUADS = 100000;
			const uint32_t MAX_VERTICES = MAX_QUADS * 4;
			const uint32_t MAX_INDICES = MAX_QUADS * 6;
			uint32_t MAX_TEXTURE_UNIT = RenderCommand::GetMaxNumberOfTextureImageUnit();

			Core::Ref<VertexArray> QuadVertexArray;
			Core::Ref<VertexBuffer> QuadVertexBuffer;
			Core::Ref<IndexBuffer> QuadIndexBuffer;

			Core::Ref<Shader> ShaderObject;
			Core::Ref<Textures::Texture2D> WhiteTexture;

			QuadVertexInfo* QuadVertexInfoBase = nullptr;
			QuadVertexInfo* QuadVertexInfoPtr = nullptr;

			uint32_t QuadIndexCount = 0;
			uint32_t QuadEdgeCount = 0;
			uint32_t* QuadIndexEdgeBase = nullptr;

			glm::vec4 VertexPositionTemplate[4];

			std::map<std::string, Core::Ref<Textures::Texture2D>> TextureLib;
			std::map<std::string, uint32_t> TextureLibIndex;
			uint32_t QuadTextureIndex = 0;

			uint32_t AddTextureInToLib(const Core::Ref<Textures::Texture2D>& texture) {
				MAB_CORE_ASSERT(
					TextureLib.size() < MAX_TEXTURE_UNIT,
					"The maximum number of textures that can be added in a single draw has been exceeded."
				);

				if (TextureLib.find(texture->ID()) == TextureLib.end())
				{
					TextureLib[texture->ID()] = texture;
					TextureLibIndex[texture->ID()] = QuadTextureIndex;
					QuadTextureIndex++;
				}

				MAB_CORE_ASSERT(
					TextureLibIndex.find(texture->ID()) != TextureLibIndex.end(),
					"TextureIndex not found!"
				);
				
				return TextureLibIndex[texture->ID()];
			}
			void ClearTextureLib(const Core::Ref<Textures::Texture2D>& texture) {
				TextureLib.clear();
				TextureLibIndex.clear();
				QuadTextureIndex = 0;

			}

		};

	}
}
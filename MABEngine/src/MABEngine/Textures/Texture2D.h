#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Textures/Texture.h"

#include <string>

namespace MABEngine {
	namespace Textures {

		class MABENGINE_API Texture2D : public Texture
		{
		public:

			virtual uint32_t GetRendererId() const = 0;
			virtual uint32_t GetChannels() const = 0;

			static Core::Ref<Texture2D> Create(uint32_t width, uint32_t height);
			static Core::Ref<Texture2D> Create(const std::string& path);

		};

	}
}

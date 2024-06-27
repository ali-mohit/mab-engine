#pragma once

#include <random>
#include <glm/glm.hpp>

namespace Utilities {

	class Random {
	public:
		static void Init() {
			s_RandomEngine.seed(std::random_device()());
		}

		static uint32_t Uint() {
			return s_Distribution(s_RandomEngine);
		}

		static uint32_t Uint(uint32_t min, uint32_t max) {
			return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
		}

		static float Float() {
			return (float)s_Distribution(s_RandomEngine) / (float)(std::numeric_limits<uint32_t>::max());
		}

		static glm::vec3 Vec3() {
			return glm::vec3(Float(), Float(), Float());
		}

		static glm::vec3 Vec3(float min, float max) {
			return glm::vec3(
				(Float() * (max - min)) + min,
				(Float() * (max - min)) + min, 
				(Float() * (max - min)) + min
			);
		}

	private:
		static thread_local std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};

}
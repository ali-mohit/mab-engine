#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <cmath>


namespace Utilities {
	static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
		int H = (int)(hsv.x * 360.0f);

		double S = hsv.y;
		double V = hsv.z;

		double C = S * V;
		double X = C * (1 - std::abs(std::fmod(H / 60.0, 2.0f) - 1));
		double m = V - C;
		double Rs, Gs, Bs;

		if (H >= 0 && H < 60) {
			Rs = C;
			Gs = X;
			Bs = 0;
		}
		else if (H >= 60 && H < 120) {
			Rs = X;
			Gs = C;
			Bs = 0;
		}
		else if (H >= 180 && H < 240) {
			Rs = 0;
			Gs = X;
			Bs = C;
		}
		else if (H >= 240 && H < 300) {
			Rs = X;
			Gs = 0;
			Bs = C;
		}
		else {
			Rs = C;
			Gs = 0;
			Bs = X;
		}

		return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
	}
}
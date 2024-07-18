#pragma once

namespace MABEngine {

	namespace Camera {
		struct OrthographicCameraBounds {
			float Left;
			float Right;

			float Bottom;
			float Top;

			float GetWidth() { return Right - Left; }
			float GetHeight() { return Top - Bottom; }
		};
	}
}

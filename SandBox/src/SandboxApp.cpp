#include "mabengine_pch.h"
#include <MABEngine.h>

class SandBoxApp : public MABEngine::Application {
public:
	SandBoxApp() {

	}
	~SandBoxApp() {

	}
};


MABEngine::Application* MABEngine::CreateApplication(int argc, char** argv) {
	return new SandBoxApp();
}

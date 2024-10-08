#pragma once

// For use MABEngine Applications

#include "MABEngine/Core/Base.h"

#include "MABEngine/Core/TimeStep.h"
#include "MABEngine/Core/Application.h"
#include "MABEngine/Core/Settings.h"
#include "MABEngine/Core/ApplicationProps.h"
#include "MABEngine/Core/Application.h"

#include "MABEngine/Layers/Layer.h"
#include "MABEngine/Layers/ImGui/ImGuiLayer.h"

#include "MABEngine/Logging/Log.h"

#include "MABEngine/Events/Event.h"
#include "MABEngine/Events/ApplicationEvent.h"
#include "MABEngine/Events/KeyEvent.h"
#include "MABEngine/Events/MouseEvent.h"

#include "MABEngine/Inputs/Input.h"
#include "MABEngine/Inputs/KeyboardCodes.h"
#include "MABEngine/Inputs/MouseButtonCodes.h"

#include "MABEngine/Renderer/RenderAPIType.h"
#include "MABEngine/Renderer/QuadVertexInfo.h"
#include "MABEngine/Renderer/Shader.h"
#include "MABEngine/Renderer/ShaderDataType.h"
#include "MABEngine/Renderer/ShaderFileType.h"
#include "MABEngine/Renderer/ShaderPackageFile.h"
#include "MABEngine/Renderer/ShaderLibrary.h"
#include "MABEngine/Renderer/BufferElement.h"
#include "MABEngine/Renderer/BufferLayout.h"
#include "MABEngine/Renderer/IndexBuffer.h"
#include "MABEngine/Renderer/VertexArray.h"
#include "MABEngine/Renderer/EngineRenderer2dStorage.h"
#include "MABEngine/Renderer/EngineRenderer.h"
#include "MABEngine/Renderer/EngineRenderer2D.h"
#include "MABEngine/Renderer/RendererAPI.h"
#include "MABEngine/Renderer/RenderCommand.h"
#include "MABEngine/Renderer/FrameBufferSpecification.h"
#include "MABEngine/Renderer/FramBuffer.h"
#include "MABEngine/Renderer/GraphicCardInfo.h"

#include "MABEngine/Textures/Texture.h"
#include "MABEngine/Textures/Texture2D.h"
#include "MABEngine/Textures/SubTexture2D.h"

#include "MABEngine/Camera/CameraTypeEnum.h"
#include "MABEngine/Camera/CameraSpecification.h"
#include "MABEngine/Camera/OrthographicCamera.h"
#include "MABEngine/Camera/OrthographicCameraBounds.h"
#include "MABEngine/Camera/OrthographicCameraController.h"
#include "MABEngine/Camera/PerspectiveCamera.h"
#include "MABEngine/Camera/PerspectiveCameraController.h"

#include "MABEngine/Components/IDComponent.h"
#include "MABEngine/Components/TagComponent.h"
#include "MABEngine/Components/TransformComponent.h"
#include "MABEngine/Components/TextComponent.h"
#include "MABEngine/Components/SpriteRendererComponent.h"
#include "MABEngine/Components/ComponentGroup.h"

#include "MABEngine/Scene/Entity.h"
#include "MABEngine/Scene/Utilities.h"
#include "MABEngine/Scene/SceneManagement.h"
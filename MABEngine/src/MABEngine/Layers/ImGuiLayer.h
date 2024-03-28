#pragma once

#include "MABEngine/Core.h"
#include "MABEngine/Layers/Layer.h"

namespace MABEngine {
    namespace Layers {

        class MABENGINE_API ImGuiLayer : public Layer
        {
        public:
            ImGuiLayer();
            ImGuiLayer(std::string layerName);

            virtual ~ImGuiLayer() override;

            virtual void OnAttach() override;
            virtual void OnDettach() override;
            virtual void OnUpdate() override;
            virtual void OnEvent(Events::Event& event) override;

        private:
            float m_Time = 0.0f;
        };

    }
}



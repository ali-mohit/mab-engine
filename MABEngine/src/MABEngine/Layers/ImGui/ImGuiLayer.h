#pragma once

#include "MABEngine/Core/Base.h"
#include "MABEngine/Events/Event.h"
#include "MABEngine/Layers/Layer.h"

namespace MABEngine {
    namespace Layers {
        static bool isImGuiGlfwInitialized = false;

        class MABENGINE_API ImGuiLayer : public Layer
        {
        public:
            ImGuiLayer();
            ImGuiLayer(std::string layerName);

            virtual ~ImGuiLayer() override;

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnEvent(Events::Event& e) override;
            virtual void OnImGuiRender() override;

            void Begin();
            
            void End();

            inline const bool& GetBlockEvents() const { return m_BlockEvents; }
            inline void SetBlockEvents(bool block) { m_BlockEvents = block; }
        private:
            bool m_BlockEvents = true;
        };

    }
}



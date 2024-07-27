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

            inline const bool& GetBlockMouseEvents() const { return m_BlockMouseEvents; }
            inline void SetBlockMouseEvents(bool block) { m_BlockMouseEvents = block; }

            inline const bool& GetBlockKeyboardEvents() const { return m_BlockKeyboardEvents; }
            inline void SetBlockKeyboardEvents(bool block) { m_BlockKeyboardEvents = block; }
        private:
            bool m_BlockMouseEvents = true;
            bool m_BlockKeyboardEvents = true;
        };

    }
}



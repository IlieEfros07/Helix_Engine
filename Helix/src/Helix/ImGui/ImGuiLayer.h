#pragma once

#include "Helix/Layer.h"
#include "Helix/Events/ApplicationEvent.h"
#include "Helix/Events/KeyEvent.h"
#include "Helix/Events/MouseEvent.h"

namespace Helix {
	class HELIX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		virtual void Begin();
		virtual void End();
	private:
		float m_Time = 0.0f;
	};
}
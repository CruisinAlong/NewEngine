#pragma once

#include "Sign/Layer.h"

namespace Sign {
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}


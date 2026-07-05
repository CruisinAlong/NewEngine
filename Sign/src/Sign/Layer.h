#pragma once
#include <memory>

#include "Events/Event.h"
#include "Sign/Timestep.h"
namespace Sign {
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDettach() {}

		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate(Timestep dt) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

		template<std::derived_from<Layer> T, typename... Args>
		void TransitionTo(Args&& ... args) {
			QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
		}

	private:
		void QueueTransition(std::unique_ptr<Layer> layer);
	};
}
#include "AppLayer.h"

AppLayer::AppLayer()
{
	std::println("App Layer Created");
}

void AppLayer::OnUpdate(float ts)
{
	if (Sign::Input::IsKeyPressed(Sign::Key::A)) {
		std::println("A");
	}
	
	//std::println("{} {}", Sign::Input::GetMouseX(), Sign::Input::GetMouseY());
}

void AppLayer::OnEvent(Sign::Event& event)
{
	if (event.GetEventType() == Sign::EventType::KeyPressed) {
		auto& e = (Sign::KeyPressedEvent&)event;
		std::println("{}", (char)e.GetKeyCode());
	}
}

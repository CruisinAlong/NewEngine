#pragma once
#include "Sign/Layer.h"
#include <print>
#include "Sign/Input.h"
#include "Sign/Events/Event.h"
#include "Sign/Events/InputEvents.h"
class AppLayer : public Sign::Layer
{
public:
	AppLayer();

	virtual void OnUpdate(float ts) override;
	virtual void OnEvent(Sign::Event& event) override;
};


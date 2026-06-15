#include "Sign/Application.h"
#include "Sign/Core.h"
#include "AppLayer.h"
int main() {
	Sign::PrintWorld();


	Sign::Application application{};
	application.PushLayer(new AppLayer());
	application.Run();
}
#include "Sign/Application.h"
#include "Sign/Core.h"
#include "AppLayer.h"
int main() {
	Sign::PrintWorld();

	Sign::ApplicationSpecifications specifications = {};
	specifications.name = "DirectXEngine";
	specifications.WindowSpec.Width = 1024;
	specifications.WindowSpec.Height = 768;
	Sign::Application application(specifications);
	application.PushLayer(new AppLayer());
	application.Run();
}
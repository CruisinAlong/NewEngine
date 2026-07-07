#include "EditorLayer.h"
#include "Sign/EntryPoint.h"
class Editor : public Sign::Application {
public:
	Editor(const Sign::ApplicationSpecifications& specs)
		: Sign::Application(specs)
	{

		PushLayer(new EditorLayer);
	}
};

Sign::Application* Sign::CreateApplication() {
	Sign::ApplicationSpecifications specifications = {};
	specifications.name = "DirectXEngine";
	specifications.WindowSpec.Width = 1024;
	specifications.WindowSpec.Height = 768;
	return new Editor(specifications);
}
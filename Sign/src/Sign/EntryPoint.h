#pragma once

#ifdef SIGN_PLATFORM_WINDOWS

extern Sign::Application* Sign::CreateApplication();
int main(int argc, char** argv) {

	auto app = Sign::CreateApplication();
	app->Run();
	delete app;
}
#endif
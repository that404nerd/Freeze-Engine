#include "core/Application.h"

inline const std::string ENGINE_STARTUP_MESSAGE = "Freeze Engine v0.5_DEV";

int main() 
{
  Freeze::Application *application = new Freeze::Application();
  FZ_INFO(ENGINE_STARTUP_MESSAGE);

  application->OnInit(1280, 720, ENGINE_STARTUP_MESSAGE);
  application->Run();

  delete application;
}

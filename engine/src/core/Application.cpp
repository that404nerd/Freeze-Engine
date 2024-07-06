#include "Application.h"

namespace Freeze
{

  void Application::OnInit(uint32_t width, uint32_t height, const std::string &title)
  {
    m_Window = std::make_unique<Window>();
    m_Window->CreateWindow(width, height, title);
    m_Window->CreateWindowContext();
    m_Window->InitCallbacks();
    m_Window->SetEventCallbackFunction(Application::OnEvent);

    InitGLEW();

    Renderer2D::InitRenderer();
    Audio::InitAudioSystem();

    m_ImGuiContext->CreateImGuiContext(m_Window->GetWindowInstance());
    
    Physics::PhysicsModule::InitPhysicsWorld();

    m_Sandbox = std::make_shared<Sandbox>();
    m_Sandbox->OnInit();
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    
    auto OnResizeHandler = [](WindowResizeEvent& event) {
      OnResize(event); // Assuming OnResize is a member function of Window
      return true;
    };

    auto OnCloseHandler = [](WindowCloseEvent& event) {
        Window::DestroyWindow(); // Assuming DestroyWindow is a static member function
        return true;
    };


    // Dispatch the event using the lambda
    dispatcher.Dispatch<WindowResizeEvent>(OnResizeHandler);
  }

  void Application::Run()
  {
    float lastFrame = 0.0f;

    while (!m_Window->IsWindowClosed())
    {
     float currentFrame = glfwGetTime();
      float deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      RenderCommands::SetRenderColor(glm::vec4(0.161, 0.161, 0.133, 1.0f));
      RenderCommands::RenderClear();

      Renderer2D::StartBatch();

      // ALWAYS UPDATE IMGUI BEFORE DOING SANDBOX STUFF!!!
      m_ImGuiContext->UpdateImGui();
      m_Sandbox->OnImGui();

      Physics::PhysicsModule::UpdatePhysicsWorld(deltaTime);
      m_Sandbox->OnUpdate(deltaTime);

      // Renderer2D::Flush();
      
      // Render ImGui Stuff
      m_ImGuiContext->RenderImGui();

      glfwPollEvents();
      glfwSwapBuffers(m_Window->GetWindowInstance());    
    }  
  }

  void Application::OnResize(WindowResizeEvent& event)
  {
    event = WindowResizeEvent(Window::GetWindowWidth(), Window::GetWindowHeight()); 
    glViewport(0, 0, event.GetWidth(), event.GetHeight());
    FZ_INFO("Window is resizing: {}, {}", event.GetWidth(), event.GetHeight());
  }

  bool Application::InitGLEW()
  {
    GLenum err = glewInit();
    if (!glewInit())
    {
      FZ_ERROR("GLEW failed to initialise");
      FZ_EXIT();
      return false;
    }

    return true;
  }

  Application::~Application()
  {
    Audio::DestroyAudioSystem();
    Renderer2D::ShutdownRenderer();
    Physics::PhysicsModule::DestroyPhysicsWorld();
  }


};

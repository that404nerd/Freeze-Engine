#include "Application.h"

namespace Freeze
{

  void Application::OnInit(uint32_t width, uint32_t height, const std::string &title)
  {
    m_Window = std::make_unique<Freeze::Window>();
    m_Window->CreateWindow(width, height, title);
    m_Window->CreateWindowContext();

    InitGLEW();
    SetEngineViewport();
    // EnableOpenGLDebug();
    Renderer2D::InitRenderer();

    m_ImGuiContext->CreateImGuiContext(m_Window->GetWindowInstance());

    Physics::PhysicsModule::InitPhysicsWorld();

    m_Sandbox = std::make_shared<Sandbox>();
    m_Sandbox->OnInit();
  }

  void Application::Run()
  {
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(m_Window->GetWindowInstance()))
    {
      float currentFrame = glfwGetTime();
      float deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      m_Sandbox->OnEvent(m_Window->GetWindowInstance(), deltaTime);

      RenderCommands::SetRenderColor(glm::vec4(0.161, 0.161, 0.133, 1.0f));
      RenderCommands::RenderClear();

      Renderer2D::StartBatch();

      // ALWAYS UPDATE IMGUI BEFORE DOING SANDBOX STUFF!!!
      m_ImGuiContext->UpdateImGui();

      m_Sandbox->OnImGui();

      Physics::PhysicsModule::UpdatePhysicsWorld(deltaTime);

      m_Sandbox->OnUpdate(m_Window->GetWindowInstance(), deltaTime);

      Renderer2D::Flush();

      // Render ImGui Stuff
      m_ImGuiContext->RenderImGui();

      // Then swap the buffers and check for events
      glfwSwapBuffers(m_Window->GetWindowInstance());
      glfwPollEvents();

    }
  }

  void Application::SetEngineViewport()
  {
    glViewport(0, 0, m_Window->GetWindowWidth(), m_Window->GetWindowHeight());
    glfwSetFramebufferSizeCallback(m_Window->GetWindowInstance(),
                                   framebuffer_size_callback);
  }

  bool Application::InitGLEW()
  {
    if (glewInit() != GLEW_OK)
    {
      FZ_ERROR("GLEW failed to initialise");
      FZ_EXIT();
    }

    return true;
  }

  Application::~Application()
  {
    Renderer2D::ShutdownRenderer();
    Physics::PhysicsModule::DestroyPhysicsWorld();
  }

  // Callback functions
  inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height)
  {
    glViewport(0, 0, width, height);
  }

};

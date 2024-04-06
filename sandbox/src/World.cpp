#include "World.h"

World::World()
    : m_Camera(std::make_shared<Freeze::Camera>(glm::vec4(0.0f, 960.0f, 0.0f, 540.0f)))
                                                         // left, right, bottom, top
{
}

void World::Init()
{
  InitPlatformData();
  m_Player->CreateEntity();
}

void World::InitPlatformData()
{
  // Initialise the platform data
  m_Platform->CreateBody({50.0f, 10.0f}, {0.0f, -25.0f});
}

void World::OnImGui()
{
  ImGui::SliderFloat("Camera Rotation", &m_CamRotationDefVal, 0.0f, 360.0f);
  m_Camera->SetRotation(m_CamRotationDefVal);

  float camPosfl[2] = {m_CamDefPos.x, m_CamDefPos.y}; // fl -> float
  if (ImGui::SliderFloat2("Camera Position", camPosfl, -500.0f, 500.0f))
    m_Camera->SetPosition({camPosfl[0], camPosfl[1], 0.0f});

  ImGui::Text("Cam X Coordinate: %f", m_Camera->GetPosition().x);
  ImGui::Text("Cam Y Coordinate: %f", m_Camera->GetPosition().y);
  ImGui::Text("Cam Z Coordinate: %f", m_Camera->GetPosition().z);
}

void World::RenderPlatform()
{
  m_Platform->RenderBody(m_Camera->GetProjectionViewMatrix(), {1.0f, 1.0f, 1.0f, 1.0f});
}

void World::Update(GLFWwindow *window, float deltaTime)
{
  // RenderPlatform();

  float MAX_CAM_SPEED = 400.0f;

  /* Camera movement testing */

  if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_PAGE_DOWN))
  {
    m_Camera->SetPosition({m_CamSpeed -= MAX_CAM_SPEED * deltaTime, 0.0f, 0.0f});
  }
  if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_PAGE_UP))
  {
    m_Camera->SetPosition({m_CamSpeed += MAX_CAM_SPEED * deltaTime, 0.0f, 0.0f});
  }

  // m_Player->RenderEntity(m_Camera->GetProjectionViewMatrix());
}

World::~World() {}

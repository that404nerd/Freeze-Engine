#include "World.h"

World::World()
      :m_Camera(std::make_shared<Freeze::Camera>(glm::vec4(-16.0f, 16.0f, -9.0f, 9.0f)))
{
}

void World::Init()
{
  InitPlatformData();
  m_Player->CreateEntity();
}

void World::InitPlatformData()
{
  m_Platform->CreateBody({ 20.0f, 1.0f }, { 0.0f, 0.0f });
}

void World::OnImGui()
{
  ImGui::SliderFloat("Camera Rotation", &m_CamRotationDefVal, 0.0f, 360.0f);
  m_Camera->SetRotation(m_CamRotationDefVal);

  ImGui::Text("Cam X Coordinate: %f", m_Camera->GetPosition().x);
  ImGui::Text("Cam Y Coordinate: %f", m_Camera->GetPosition().y);
}

void World::RenderPlatform()
{
  m_Platform->RenderBody({1.0f, 1.0f, 1.0f, 1.0f});
}

void World::Update(float deltaTime)
{
  RenderPlatform();

  float MAX_CAM_SPEED = 10.0f;

  /* Camera movement testing */

  if (Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_A))
  {
    m_Camera->SetPosition({m_CamSpeed -= MAX_CAM_SPEED * deltaTime, 0.0f, 0.0f});
  }
  if (Freeze::KeyboardInput::IsKeyPressed(GLFW_KEY_D))
  {
    m_Camera->SetPosition({m_CamSpeed += MAX_CAM_SPEED * deltaTime, 0.0f, 0.0f});
  }

  m_Player->RenderEntity();
}

World::~World() {}
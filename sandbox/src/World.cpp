#include "World.h"
#include "physics/Box2DDebugRenderer.h"

World::World()
  :m_Camera(std::make_shared<Freeze::Camera>(glm::vec4(-20.0f, 20.0f, -12.0f, 12.0f)))
{
}

void World::Init()
{
  Freeze::Audio::LoadAudioFile(Freeze::Utils::GetFilePath("sandbox/assets/music/e1m1_doom.wav"));

  InitPlatformData();
  m_Player->CreateEntity();
  m_Enemy->CreateEntity();
}

void World::OnEvent(Freeze::Event& e)
{
  
}

void World::InitPlatformData()
{
  m_Platform->CreateBody({ 200.0f, 1.0f }, { 0.0f, -1.0f });
}

void World::OnImGui()
{
  ImGui::SliderFloat("Camera Rotation", &m_CamRotationDefVal, 0.0f, 360.0f);
  m_Camera->SetRotation(m_CamRotationDefVal);

  ImGui::Text("Camera X Coordinate: %f", m_Camera->GetPosition().x);
  ImGui::Text("Camera Y Coordinate: %f", m_Camera->GetPosition().y);

  if(ImGui::Button("Play Audio"))
  {
    FZ_INFO(Freeze::Audio::IsPlaying());
    Freeze::Audio::PlayAudio();
  }
  if(ImGui::Button("Pause Audio"))
    Freeze::Audio::PauseAudio();
}

void World::Update(float dt)
{
  m_Platform->GetBody()->SetTransform(m_Platform->GetBody()->GetPosition(), m_Platform->GetBody()->GetAngle());
  m_QuadShape->DrawRotatedQuad({ m_Platform->GetBody()->GetPosition().x, m_Platform->GetBody()->GetPosition().y }, 
                               { m_Platform->GetBodyData()->Size.x, m_Platform->GetBodyData()->Size.y }, m_Platform->GetBody()->GetAngle(),
                               { 1.0f, 1.0f, 1.0f, 1.0f });

  m_Player->RenderEntity(dt);
  m_Enemy->RenderEntity(dt);
}

World::~World() {}

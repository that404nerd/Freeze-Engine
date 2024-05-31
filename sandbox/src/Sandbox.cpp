#include "Sandbox.h"

Sandbox::Sandbox() : m_Camera(std::make_shared<Freeze::Camera>((glm::vec4(-20.0f, 20.0f, -12.0f, 12.0f)))) {}

void Sandbox::OnInit()
{
  Freeze::EnableOpenGLDebug();
  
  m_Body->SetFriction(0.3f);
  m_Body->SetDensity(0.3f);
  m_Body->CreateBody({ 2.0f, 2.0f }, { 1.0f, 5.0f }, 45.0f);

  Freeze::Audio::LoadAudioFile(Freeze::Utils::GetFilePath("sandbox/assets/music/e1m1_doom.wav"));

  m_PlatformBody->CreateBody({ 200.0f, 1.0f }, { 0.0f, -1.0f });
}

void Sandbox::OnEvent(Freeze::Event& event)
{
}

void Sandbox::OnImGui()
{
  ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 410, 10), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_Always);
  ImGui::Begin("Debug", &m_OpenImGuiWindow);

  if (ImGui::Button("Show Colliders"))
  {
     showColliders = true;
  }

  if (showColliders)
  {
     Freeze::Physics::PhysicsModule::GetPhysicsWorld()->DebugDraw();
     if (ImGui::Button("Hide Colliders"))
     {
         showColliders = false;
     }
  }

  ImGui::Dummy(ImVec2(0.0f, 10.0f));

  if(ImGui::Button("Play Audio"))
    Freeze::Audio::PlayAudio();

  if(ImGui::Button("Pause Audio"))
    Freeze::Audio::PauseAudio();

  const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
  const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model
  
  ImGui::Dummy(ImVec2(0.0f, 10.0f));
  ImGui::Text("OS: %s", Freeze::Utils::GetOSName());
  ImGui::Text("GPU: %s, %s", vendor, renderer);

  ImGui::End();
}

void Sandbox::OnUpdate(float dt)
{
  float entityRotation = m_Body->GetBody()->GetAngle();
  float platformRotation = m_PlatformBody->GetBody()->GetAngle();

  Freeze::Renderer2D::DrawRotatedQuad({ m_Body->GetBody()->GetPosition().x, m_Body->GetBody()->GetPosition().y }, 
                                      { m_Body->GetBodyData()->Size.x, m_Body->GetBodyData()->Size.y }, 
                                      entityRotation,
                                      { 0.6f, 0.1f, 0.3f, 1.0f });

  Freeze::Renderer2D::DrawRotatedQuad({ m_PlatformBody->GetBody()->GetPosition().x, m_PlatformBody->GetBody()->GetPosition().y }, 
                                      { m_PlatformBody->GetBodyData()->Size.x, m_PlatformBody->GetBodyData()->Size.y }, 
                                      platformRotation,
                                      { 0.3f, 0.2f, 0.5f, 1.0f });

  Freeze::Renderer2D::DrawTriangle({ 5.0f, 1.0f }, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.1f, 1.0f });
  Freeze::Renderer2D::Flush();
}

Sandbox::~Sandbox()
{
}


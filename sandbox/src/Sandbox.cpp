#include "Sandbox.h"
#include "core/Entity.h"
#include "physics/InitPhysics.h"

Sandbox::Sandbox() : m_Camera(std::make_shared<Freeze::Camera>((glm::vec4(-20.0f, 20.0f, -12.0f, 12.0f)))) {}

void Sandbox::OnInit()
{
  Freeze::EnableOpenGLDebug();
  
  m_Body->SetDensity(0.3f);
  m_Body->CreateBody({ 2.0f, 2.0f }, { 1.0f, 5.0f }, 45.0f);

  Freeze::Audio::LoadAudioFile(Freeze::Utils::GetFilePath("sandbox/assets/music/e1m1_doom.wav"));

  // m_Texture->CreateTexture();
  // m_Texture->LoadTextureFile(Freeze::Utils::GetFilePath("sandbox/assets/textures/block.png"));
  // m_Texture->BindTexture();

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
  
  ImGui::Dummy(ImVec2(0.0f, 10.0f));

  ImGui::End();
}

void Sandbox::OnUpdate(float dt)
{
  float bodyRotation = m_Body->GetBody()->GetAngle();
  float platformRotation = m_PlatformBody->GetBody()->GetAngle();

  auto view = Freeze::Physics::PhysicsModule::GetPhysicsEntManager().GetRegistry().view<Freeze::PhysicsComponent>(); // WTF???
  
  for(auto entity : view)
  {
    auto& physComp = view.get<Freeze::PhysicsComponent>(entity);
    if (!physComp.Body) continue; 

    physComp.Positions = physComp.Body->GetPosition();
    physComp.Rotation = physComp.Body->GetAngle();

    Freeze::Renderer2D::DrawRotatedQuad({ physComp.Positions.x, physComp.Positions.y },
                                        { physComp.Size.x, physComp.Size.y },
                                        physComp.Rotation, 
                                        { 0.3f, 0.2f, 0.5f, 1.0f });
  }
  
  Freeze::Renderer2D::Flush();
}

Sandbox::~Sandbox()
{
}


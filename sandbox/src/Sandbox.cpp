#include "Sandbox.h"

Sandbox::Sandbox() {}

void Sandbox::OnInit()
{
  Freeze::EnableOpenGLDebug();
  
  m_World->OnInit();
}

void Sandbox::OnEvent(Freeze::Event& event)
{
}

void Sandbox::OnImGui()
{
}

void Sandbox::OnUpdate(float dt)
{
  m_World->OnUpdate(dt); 
  
  Freeze::Renderer2D::Flush();
}

Sandbox::~Sandbox()
{
}


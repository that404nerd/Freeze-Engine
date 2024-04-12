#include "Sandbox.h"

Sandbox::Sandbox() {}

void Sandbox::OnInit()
{
    // Load World Data First
    m_World->Init();
}

void Sandbox::OnEvent(GLFWwindow *window, float dt)
{
    m_World->GetPlayerInstance()->MovePlayer(window, dt);    
}

void Sandbox::OnImGui()
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 410, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400.0f, 240.0f), ImGuiCond_Always);

    ImGui::Begin("Settings", &m_OpenImGuiWindow, ImGuiWindowFlags_NoMove);
    m_World->GetPlayerInstance()->OnImGui(); 

    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    m_World->OnImGui();

    ImGui::End();
}

void Sandbox::OnUpdate(GLFWwindow* window, float dt)
{
    m_World->Update(window, dt);
}

Sandbox::~Sandbox()
{
}


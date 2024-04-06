#include "Player.h"

Player::Player() : Entity("Player"), m_X(0.0f), m_Y(0.0f) {
    FZ_INFO("Entity: {}", PrintEntityName());
    m_PhysicsEntity = std::make_shared<Freeze::Physics::DynamicBody>();
    m_PhysicsEntity1 = std::make_shared<Freeze::Physics::DynamicBody>();
}

void Player::CreateEntity() {
    ///////////// 2D BODY (NOT BOX2D) ////////////////////
    // m_FreezeQuad->CreateQuad(440.0f, 300.0f, "", ""); // TODO: "" -> //
    // DEFAULT_SHADERS
    /////////////////////////////////////////////////////

    ////////// BOX2D QUAD //////////////////

    float x = 0.0f;
    float y = 20.0f;

    m_PhysicsEntity->SetFriction(0.3f);
    m_PhysicsEntity->SetDensity(0.3f);
    m_PhysicsEntity->SetRestitution(0.6f);
    m_PhysicsEntity->CreateBody({10.0f, 10.0f}, {x, y});

    for (int i = 0; i < 4; i++) {
        m_PhysicsEntity1->SetFriction(0.3f);
        m_PhysicsEntity1->SetDensity(0.3f);
        m_PhysicsEntity1->SetRestitution(0.4f);
        m_PhysicsEntity1->CreateBody({5.0f, 5.0f}, {x + 4.0f, y + 3.0f});
    }

    // FZ_INFO("Before deleting: {}",
    // Freeze::Physics::DynamicBody::GetTotalDynamicBodies());
    // m_PhysicsEntity1->DeleteBody((b2Body*)this);
    // FZ_INFO("After deleting: {}",
    // Freeze::Physics::DynamicBody::GetTotalDynamicBodies());
}

void Player::MovePlayer(GLFWwindow *window, float dt) {
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_D)) // Move Right
    {
        m_X += 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_A)) // Move Left
    {
        m_X -= 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_SPACE)) {
        m_Y += 500.0f * dt;
    }
    if (Freeze::KeyboardInput::IsKeyPressed(window, GLFW_KEY_S)) {
        m_Y -= 500.0f * dt;
    }
}

void Player::OnImGui() {
    ImGui::ColorEdit4("Color", playerColors);

    ImGui::Text("X Coord: %f", m_X);
    ImGui::Text("Y Coord: %f", m_Y);


    std::shared_ptr<Freeze::Physics::DynamicBody> body;

    if (ImGui::Button("Create new body (DYNAMIC)")) {
        body = std::make_shared<Freeze::Physics::DynamicBody>();
        body->SetFriction(0.4f);
        body->SetDensity(0.5f);
        body->SetRestitution(0.6f);

        body->CreateBody({5.0f, 5.0f}, {0.0f, 0.0f});
    }

    if (ImGui::Button("Delete dynamic body")) {
        body->DeleteBody();
    }
}

void Player::RenderEntity(const glm::mat4 &projectionMatrix) {
    m_PhysicsEntity->RenderBody(projectionMatrix, {0.4f, 0.1f, 0.7f, 1.0f});
}

Player::~Player() {}

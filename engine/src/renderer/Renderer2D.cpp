#include "Renderer2D.h"

namespace Freeze {

  void RenderCommands::SetRenderColor(const glm::vec4& color)
  {
      glClearColor(color.r, color.g, color.b, color.a);
  }

  void RenderCommands::RenderClear()
  {
      glClear(GL_COLOR_BUFFER_BIT);
  }

  ///////////////////////// Quad Rendering //////////////////////////////////

  FreezeQuad::FreezeQuad()
  {
    m_QuadRendererData = new QuadRendererData();
  }

  void FreezeQuad::CreateQuad(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
    
    // TODO: Change the coordinates to be dynamic. Must work for any camera positions. 

    m_QuadRendererData->m_QuadCoords = new float[12] {
          100.0f,           100.0f,           0.0f,  // top left
          100.0f + width,   100.0f,           0.0f,  // top right
          100.0f + width,   100.0f + height,  0.0f,  // bottom right
          100.0f,           100.0f + height,  0.0f   // bottom left
    };

    m_QuadRendererData->m_QuadIndices = new uint32_t[6]{
        0,  1,  3,
        1,  2,  3
    };

    // Lol this sucks... i need to manually assign the sizes due to them being dynamically allocated rather stack allocated (but that's fine)
    m_QuadRendererData->m_ElementBuffer->AddElementBuffer(m_QuadRendererData->m_QuadIndices, 6 * sizeof(uint32_t), GL_STATIC_DRAW);
    m_QuadRendererData->m_ElementBuffer->BindElementBuffer();

    m_QuadRendererData->m_VertexArray->AddVertexArray(1);
    m_QuadRendererData->m_VertexArray->BindVertexArray();

    m_QuadRendererData->m_VertexBuffer->AddVertexBuffer(m_QuadRendererData->m_QuadCoords, 12 * sizeof(float), GL_STATIC_DRAW);
    m_QuadRendererData->m_VertexBuffer->BindVertexBuffer();
    
    // TODO: This thing needs to be abstracted away (for more flexiblity)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    if(vertexShaderFile != "" && fragmentShaderFile != "")
    {
      FZ_INFO("Using custom quad shaders");
      m_QuadRendererData->m_RendererShader->LoadShadersFromFiles(Freeze::Utils::GetFilePath(vertexShaderFile), 
                                                            Freeze::Utils::GetFilePath(fragmentShaderFile));
    }                                                          
    else
      FZ_INFO("Using default quad shaders");
      m_QuadRendererData->m_RendererShader->LoadShadersFromFiles(Freeze::Utils::GetFilePath("engine/assets/shaders/Quad.vert"), 
                                                                  Freeze::Utils::GetFilePath("engine/assets/shaders/Quad.frag"));
    }

  void FreezeQuad::RenderQuad(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color) 
  {
    m_QuadRendererData->m_RendererShader->UseShader();


    glm::mat4 newPosMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(positions.x, positions.y, 0.0f));

    m_Positions.x = positions.x;
    m_Positions.y = positions.y;

    m_QuadRendererData->m_RendererShader->SetMatrix4fv(m_QuadRendererData->m_RendererShader->GetUniformLocation("a_ProjectionMatrix"), projectionMatrix);
    m_QuadRendererData->m_RendererShader->SetVector4f(m_QuadRendererData->m_RendererShader->GetUniformLocation("u_Color"), color);
    m_QuadRendererData->m_RendererShader->SetMatrix4fv(m_QuadRendererData->m_RendererShader->GetUniformLocation("a_NewPosMatrix"), newPosMatrix);

    m_QuadRendererData->m_VertexArray->BindVertexArray();
    m_QuadRendererData->m_ElementBuffer->BindElementBuffer();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  FreezeQuad::~FreezeQuad()
  {
    delete[] m_QuadRendererData->m_QuadCoords;
    delete[] m_QuadRendererData->m_QuadIndices;
    delete m_QuadRendererData;
  }

  ///////////////////////// Triangle Rendering ///////////////////////////////

  FreezeTriangle::FreezeTriangle()
  {
    m_TriangleRendererData = new TriangleRendererData();
  }

  void FreezeTriangle::CreateTriangle(float width, float height, const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
  {
    // TODO: Change the coordinates to be dynamic. Must work for any camera positions. 

    m_TriangleRendererData->m_TriangleCoords = new float[9] {
      -90.0f,          -90.0f,            0.0f,  // top point
       90.0f + width,  -90.0f + height,   0.0f,  // bottom right
       0.0f,            90.0f + height,   0.0f   // bottom left
    };

    m_TriangleRendererData->m_VertexArray->AddVertexArray(1);
    m_TriangleRendererData->m_VertexArray->BindVertexArray();

    m_TriangleRendererData->m_VertexBuffer->AddVertexBuffer(m_TriangleRendererData->m_TriangleCoords, 9 * sizeof(float), GL_STATIC_DRAW);
    m_TriangleRendererData->m_VertexBuffer->BindVertexBuffer();
    
    // This thing needs to be abstracted away (for more flexiblity)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    if(vertexShaderFile != "" && fragmentShaderFile != "")
    {
      FZ_INFO("Using custom triangle shaders");
      m_TriangleRendererData->m_RendererShader->LoadShadersFromFiles(Freeze::Utils::GetFilePath(vertexShaderFile), 
                                                            Freeze::Utils::GetFilePath(fragmentShaderFile));
    }
    else
      FZ_INFO("Using default triangle shaders");
      m_TriangleRendererData->m_RendererShader->LoadShadersFromFiles(Freeze::Utils::GetFilePath("engine/assets/shaders/Triangle.vert"), 
                                                                  Freeze::Utils::GetFilePath("engine/assets/shaders/Triangle.frag"));
  }

  void FreezeTriangle::RenderTriangle(const glm::mat4& projectionMatrix, const glm::vec2& positions, const glm::vec4& color) 
  {
    m_TriangleRendererData->m_RendererShader->UseShader();

    glm::mat4 newPosMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(positions.x, positions.y, 0.0f));

    m_TriangleRendererData->m_RendererShader->SetMatrix4fv(m_TriangleRendererData->m_RendererShader->GetUniformLocation("a_ProjectionMatrix"), projectionMatrix);
    m_TriangleRendererData->m_RendererShader->SetVector4f(m_TriangleRendererData->m_RendererShader->GetUniformLocation("u_Color"), color);
    m_TriangleRendererData->m_RendererShader->SetMatrix4fv(m_TriangleRendererData->m_RendererShader->GetUniformLocation("a_NewPosMatrix"), newPosMatrix);

    m_TriangleRendererData->m_VertexArray->BindVertexArray();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  FreezeTriangle::~FreezeTriangle() {
    delete[] m_TriangleRendererData->m_TriangleCoords;

    delete m_TriangleRendererData;
  }

};  // namespace Freeze

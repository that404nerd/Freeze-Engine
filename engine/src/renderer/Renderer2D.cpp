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

  //////////////////////////////////////////// 2D Batch Rendering //////////////////////////////////////////////////////

  struct QuadVertex {
    // Vertex has a position, color for now..
    glm::vec3 Position;
    glm::vec4 Color; 
  };

  struct TriangleVertex {
    // Vertex has a position, color for now.. (Same as the Quad)
    glm::vec3 Position;
    glm::vec4 Color;
  };

  struct Renderer2DData {
    static const int MaxQuads = 1000;
    static const int MaxQuadVertices = MaxQuads * 4;
    static const int MaxQuadIndices = MaxQuads * 6; // Each quad has 6 indices

    static const int MaxTriangles = 900;
    static const int MaxTriangleVertices = MaxTriangles * 3;
    static const int MaxTriangleIndices = MaxQuads * 3; // Each quad has 3 indices

    std::shared_ptr<VertexBuffer> QuadVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> QuadVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<Shader> QuadShader = std::make_shared<Shader>();

    std::shared_ptr<VertexBuffer> TriangleVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> TriangleVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<Shader> TriangleShader = std::make_shared<Shader>();

    uint32_t QuadIndexCount = 0;
    QuadVertex* QuadVertexBufferStart = nullptr; // Stores the base address of the vertex (Starting address)
    QuadVertex* QuadVertexBufferCurrent = nullptr; // Tracks the current address of the vertex

    uint32_t TriangleIndexCount = 0;
    TriangleVertex* TriangleVertexBufferStart = nullptr;
    TriangleVertex* TriangleVertexBufferCurrent = nullptr;
  };

  static Renderer2DData* m_RendererData = nullptr;

  void Renderer2D::InitRenderer()
  {
      // This will not happen but pointers are unpredictable....
      if (m_RendererData != nullptr)
        FZ_ASSERT("Renderer Data Already Initialised....");

      m_RendererData = new Renderer2DData();

      // Generate an Vertex Array
      m_RendererData->QuadVertexArray->AddVertexArray();
      m_RendererData->QuadVertexArray->BindVertexArray();

      // Generate an Vertex buffer with size of QuadVertex * MaxQuadVertices (not allocate)
      m_RendererData->QuadVertexBuffer->AddVertexBuffer(sizeof(QuadVertex) * m_RendererData->MaxQuadVertices, GL_DYNAMIC_DRAW);

      // Position
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Position));
      glEnableVertexAttribArray(0);

      // Color
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, Color));
      glEnableVertexAttribArray(1);

      m_RendererData->QuadVertexBufferStart = new QuadVertex[m_RendererData->MaxQuadVertices]; // Set the QuadBufferBase pointer to the beginning address

      uint32_t* quadIndices = new uint32_t[m_RendererData->MaxQuadIndices]; // Create a indices pointer for setting it in the index buffer

      uint32_t offsetQuad = 0; // Define an offset
      for (int i = 0; i < m_RendererData->MaxQuadIndices; i += 6)
      {
          // Increment the indices data in this order // 0, 1, 2, 2, 3, 0 (for a quad) and repeat until MaxIndices
          quadIndices[i + 0] = offsetQuad;
          quadIndices[i + 1] = offsetQuad + 1;
          quadIndices[i + 2] = offsetQuad + 2;

          quadIndices[i + 3] = offsetQuad + 2;
          quadIndices[i + 4] = offsetQuad + 3;
          quadIndices[i + 5] = offsetQuad;

          offsetQuad += 4; // Increment the offset by 4 because the next row's elements will differ by 4 by the respective above values
      }

      std::shared_ptr<IndexBuffer> QuadIndexBuffer = std::make_shared<IndexBuffer>();
      QuadIndexBuffer->AddIndexBuffer(quadIndices, m_RendererData->MaxQuadIndices, GL_STATIC_DRAW);
      QuadIndexBuffer->BindIndexBuffer();

      m_RendererData->QuadVertexArray->UnbindVertexArray();
      QuadIndexBuffer->UnbindIndexBuffer();

      delete[] quadIndices;

      // Load the default shaders
      m_RendererData->QuadShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Quad.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Quad.frag"));

      /////////////////////// Triangle Rendering ///////////////////////////
      m_RendererData->TriangleVertexArray->AddVertexArray();
      m_RendererData->TriangleVertexArray->BindVertexArray();

      // Generate an Vertex buffer with size of TriangleVertex * MaxTriangleVertices (not allocate)
      m_RendererData->TriangleVertexBuffer->AddVertexBuffer(sizeof(TriangleVertex) * m_RendererData->MaxTriangleVertices, GL_DYNAMIC_DRAW);

      // Position
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), (const void*)offsetof(TriangleVertex, Position));
      glEnableVertexAttribArray(0);

      // Color
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), (const void*)offsetof(TriangleVertex, Color));
      glEnableVertexAttribArray(1);

      m_RendererData->TriangleVertexBufferStart = new TriangleVertex[m_RendererData->MaxTriangleVertices]; // Set the TriangleBase pointer to the beginning address

      uint32_t* triangleIndices = new uint32_t[m_RendererData->MaxTriangleIndices]; // Create a indices pointer for setting it in the index buffer

      uint32_t offsetTriangle = 0; // Define an offset
      for (int i = 0; i < m_RendererData->MaxTriangleIndices; i += 3)
      {
          // Increment the indices data in this order 0, 2, 1 (for a triangle) and repeat until MaxIndices
          triangleIndices[i + 0] = offsetTriangle;
          triangleIndices[i + 1] = offsetTriangle + 2;
          triangleIndices[i + 2] = offsetTriangle + 1;

          offsetTriangle += 3; // Increment the offset by 3 because the next row's elements will differ by 3 by the respective above values
      }

      std::shared_ptr<IndexBuffer> TriangleIndexBuffer = std::make_shared<IndexBuffer>();
      TriangleIndexBuffer->AddIndexBuffer(triangleIndices, m_RendererData->MaxTriangleIndices, GL_STATIC_DRAW);
      TriangleIndexBuffer->BindIndexBuffer();

      m_RendererData->TriangleVertexArray->UnbindVertexArray();
      TriangleIndexBuffer->UnbindIndexBuffer();

      delete[] triangleIndices;

      // Load the default shaders
      m_RendererData->TriangleShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Triangle.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Triangle.frag"));
  }

  void Renderer2D::StartBatch()
  {
    m_RendererData->QuadIndexCount = 0;
    m_RendererData->QuadVertexBufferCurrent = m_RendererData->QuadVertexBufferStart;

    m_RendererData->TriangleIndexCount = 0;
    m_RendererData->TriangleVertexBufferCurrent = m_RendererData->TriangleVertexBufferStart;
  }

  void Renderer2D::Flush()
  {
    if (m_RendererData->QuadIndexCount) // Check if not zero
    {
        // The below gives us the data that needs to be renderer (Current - Initial)
        uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData->QuadVertexBufferCurrent - (uint8_t*)m_RendererData->QuadVertexBufferStart);
        m_RendererData->QuadVertexBuffer->SetVertexBufferData(m_RendererData->QuadVertexBufferStart, dataSize);
        m_RendererData->QuadShader->UseShader();

        m_RendererData->QuadShader->SetMatrix4fv(m_RendererData->QuadShader->GetUniformLocation("a_ProjectionMatrix"), Camera::GetProjectionViewMatrix());
        m_RendererData->QuadShader->SetVector4f(m_RendererData->QuadShader->GetUniformLocation("a_QuadColor"), m_RendererData->QuadVertexBufferStart->Color);

        m_RendererData->QuadVertexArray->BindVertexArray();

        glDrawElements(GL_TRIANGLES, m_RendererData->QuadIndexCount, GL_UNSIGNED_INT, nullptr);
    }

    if (m_RendererData->TriangleIndexCount) // Check if not zero
    {
      // The below gives us the data that needs to be renderer (Current - Initial)
      uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData->TriangleVertexBufferCurrent - (uint8_t*)m_RendererData->TriangleVertexBufferStart);
      m_RendererData->TriangleVertexBuffer->SetVertexBufferData(m_RendererData->TriangleVertexBufferStart, dataSize);
      m_RendererData->TriangleShader->UseShader();

      m_RendererData->TriangleShader->SetMatrix4fv(m_RendererData->TriangleShader->GetUniformLocation("a_ProjectionMatrix"), Camera::GetProjectionViewMatrix());
      m_RendererData->TriangleShader->SetVector4f(m_RendererData->TriangleShader->GetUniformLocation("f_TriangleColor"), m_RendererData->TriangleVertexBufferStart->Color);

      m_RendererData->TriangleVertexArray->BindVertexArray();

      glDrawElements(GL_TRIANGLES, m_RendererData->TriangleIndexCount, GL_UNSIGNED_INT, nullptr);
    }
  }

  void Renderer2D::NextBatch()
  {
    Flush();
    StartBatch();
  }

  void Renderer2D::EndBatch()
  {
    uint32_t sizeQuad = (uint32_t)((uint8_t*)m_RendererData->QuadVertexBufferCurrent - (uint8_t*)m_RendererData->QuadVertexBufferStart);
    m_RendererData->QuadVertexBuffer->BindVertexBuffer();
    m_RendererData->QuadVertexBuffer->SetVertexBufferData(m_RendererData->QuadVertexBufferStart, sizeQuad); // Set the vertex buffer data to the beginning of the buffer

    uint32_t sizeTriangle = (uint32_t)((uint8_t*)m_RendererData->TriangleVertexBufferCurrent - (uint8_t*)m_RendererData->TriangleVertexBufferStart);
    m_RendererData->TriangleVertexBuffer->BindVertexBuffer();
    m_RendererData->TriangleVertexBuffer->SetVertexBufferData(m_RendererData->TriangleVertexBufferStart, sizeTriangle); // Set the vertex buffer data to the beginning of the buffer
  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  { 
    // If the index count exceeds MaxIndex (which could happen...)
    if(m_RendererData->QuadIndexCount >= m_RendererData->MaxQuadIndices)
    {
      EndBatch(); // Reset the data to the beginning of the buffer
      NextBatch(); // Render what's left and start batching again
    }
    
    // Calculate the half-width and half-height of the rectangle
    float halfWidth = size.x / 2.0f;
    float halfHeight = size.y / 2.0f;

    // Calculate the positions of the vertices based on the provided position and size (need to follow the order below)
    m_RendererData->QuadVertexBufferCurrent->Position = { position.x - halfWidth, position.y - halfHeight, 0.0f }; // bottom left
    m_RendererData->QuadVertexBufferCurrent->Color = color;
    m_RendererData->QuadVertexBufferCurrent++;

    m_RendererData->QuadVertexBufferCurrent->Position = { position.x + halfWidth, position.y - halfHeight, 0.0f }; // bottom right
    m_RendererData->QuadVertexBufferCurrent->Color = color;
    m_RendererData->QuadVertexBufferCurrent++;

    m_RendererData->QuadVertexBufferCurrent->Position = { position.x + halfWidth, position.y + halfHeight, 0.0f }; // top right
    m_RendererData->QuadVertexBufferCurrent->Color = color;
    m_RendererData->QuadVertexBufferCurrent++;

    m_RendererData->QuadVertexBufferCurrent->Position = { position.x - halfWidth, position.y + halfHeight, 0.0f }; // top left
    m_RendererData->QuadVertexBufferCurrent->Color = color;
    m_RendererData->QuadVertexBufferCurrent++;

    m_RendererData->QuadIndexCount += 6;
  }

  void Renderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  { 
    // If the index count exceeds MaxIndex (which could happen...)
    if(m_RendererData->TriangleIndexCount >= m_RendererData->MaxTriangleIndices)
    {
      EndBatch(); // Reset the data to the beginning of the buffer
      NextBatch(); // Render what's left and start batching again
    }

    // Assuming that the left corner (the first vertex) is (0, 0)
    m_RendererData->TriangleVertexBufferCurrent->Position = { position.x, position.y, 0.0f };
    m_RendererData->TriangleVertexBufferCurrent->Color = color;
    m_RendererData->TriangleVertexBufferCurrent++;

    m_RendererData->TriangleVertexBufferCurrent->Position = { position.x + size.x, position.y, 0.0f };
    m_RendererData->TriangleVertexBufferCurrent->Color = color;
    m_RendererData->TriangleVertexBufferCurrent++;

    m_RendererData->TriangleVertexBufferCurrent->Position = { position.x + size.x * 0.5f, position.y + size.y, 0.0f };
    m_RendererData->TriangleVertexBufferCurrent->Color = color;
    m_RendererData->TriangleVertexBufferCurrent++;

    m_RendererData->TriangleIndexCount += 3;
  }

  void Renderer2D::ShutdownRenderer()
  {
    delete[] m_RendererData->QuadVertexBufferStart;
    m_RendererData->QuadShader->DeleteShaders();
    m_RendererData->QuadShader->UnbindShader();

    delete[] m_RendererData->TriangleVertexBufferStart;
    m_RendererData->TriangleShader->DeleteShaders();
    m_RendererData->TriangleShader->UnbindShader();

    delete m_RendererData;
    m_RendererData = nullptr;
  }

};  // namespace Freeze

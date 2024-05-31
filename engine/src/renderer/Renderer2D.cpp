#include "Renderer2D.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"
#include <glm/ext/matrix_transform.hpp>

// TODO: Call Flush() at the end of a scene and creation of scenes

namespace Freeze {

  void RenderCommands::SetRenderColor(const glm::vec4& color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void RenderCommands::RenderClear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  struct Point {
    glm::vec3 Position;
    glm::vec4 Color;
  };

  struct LineVertex {
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
  
    // Some pre-defined constants
    const int MaxVertices = MaxQuadVertices + MaxTriangleVertices;
    const int MaxIndices = MaxQuadIndices + MaxTriangleIndices;
  
    std::shared_ptr<VertexBuffer> QuadVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> QuadVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<IndexBuffer> QuadIndexBuffer = std::make_shared<IndexBuffer>();
    std::shared_ptr<Shader> QuadShader = std::make_shared<Shader>();

    std::shared_ptr<VertexBuffer> TriangleVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> TriangleVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<IndexBuffer> TriangleIndexBuffer = std::make_shared<IndexBuffer>();
    std::shared_ptr<Shader> TriangleShader = std::make_shared<Shader>();

    std::shared_ptr<VertexBuffer> PointVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> PointVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<Shader> PointShader = std::make_shared<Shader>();

    std::shared_ptr<VertexBuffer> LineVertexBuffer = std::make_shared<VertexBuffer>();
    std::shared_ptr<VertexArray> LineVertexArray = std::make_shared<VertexArray>();
    std::shared_ptr<Shader> LineShader = std::make_shared<Shader>();

    uint32_t QuadIndexCount = 0;
    QuadVertex* QuadVertexBufferStart = nullptr; // Stores the base address of the vertex (Starting address)
    QuadVertex* QuadVertexBufferCurrent = nullptr; // Tracks the current address of the vertex

    uint32_t TriangleIndexCount = 0;
    TriangleVertex* TriangleVertexBufferStart = nullptr;
    TriangleVertex* TriangleVertexBufferCurrent = nullptr;

    uint32_t PointCount = 0;
    Point* PointVertexBufferStart = nullptr;
    Point* PointVertexBufferCurrent = nullptr;

    uint32_t LineVertexCount = 0;
    LineVertex* LineVertexBufferStart = nullptr;
    LineVertex* LineVertexBufferCurrent = nullptr;
  };

  static Renderer2DData* m_RendererData = nullptr;

  void Renderer2D::InitRenderer()
  {
      // This will not happen but idk why not
      if (m_RendererData != nullptr)
        FZ_ASSERT("Renderer Data Already Initialised....");

      m_RendererData = new Renderer2DData();

      ////////////////////////////////////////////////////////////////// Quad Rendering //////////////////////////////////////////////////////

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

      m_RendererData->QuadIndexBuffer->AddIndexBuffer(quadIndices, m_RendererData->MaxQuadIndices, GL_STATIC_DRAW);
      m_RendererData->QuadIndexBuffer->BindIndexBuffer();

      m_RendererData->QuadVertexArray->UnbindVertexArray();
      m_RendererData->QuadIndexBuffer->UnbindIndexBuffer();

      delete[] quadIndices;

      // Load the default shaders
      m_RendererData->QuadShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Quad.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Quad.frag"));

      /////////////////////////////////////////////// Triangle Rendering ///////////////////////////////////////////////////////
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

      m_RendererData->TriangleIndexBuffer->AddIndexBuffer(triangleIndices, m_RendererData->MaxTriangleIndices, GL_STATIC_DRAW);
      m_RendererData->TriangleIndexBuffer->BindIndexBuffer();

      m_RendererData->TriangleVertexArray->UnbindVertexArray();
      m_RendererData->TriangleIndexBuffer->UnbindIndexBuffer();

      delete[] triangleIndices;

      // Load the default shaders
      m_RendererData->TriangleShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Triangle.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Triangle.frag"));
    
      ///////////////////////////////////////// Point Rendering /////////////////////////////////////////////
      m_RendererData->PointVertexArray->AddVertexArray();
      m_RendererData->PointVertexArray->BindVertexArray();

      m_RendererData->PointVertexBuffer->AddVertexBuffer(sizeof(Point) * m_RendererData->MaxVertices, GL_DYNAMIC_DRAW);
      m_RendererData->PointVertexBuffer->BindVertexBuffer();

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (const void*)offsetof(Point, Position));
      glEnableVertexAttribArray(0);

      // Color
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (const void*)offsetof(Point, Color));
      glEnableVertexAttribArray(1);

      m_RendererData->PointVertexBufferStart = new Point[m_RendererData->MaxVertices]; // Set the TriangleBase pointer to the beginning address

      m_RendererData->PointVertexArray->UnbindVertexArray();

      // Load the default shaders
      m_RendererData->PointShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Point.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Point.frag"));
      
      ////////////////////////////////////////////// Line Rendering ////////////////////////////////////////////////
      m_RendererData->LineVertexArray->AddVertexArray();
      m_RendererData->LineVertexArray->BindVertexArray();

      m_RendererData->LineVertexBuffer->AddVertexBuffer(sizeof(LineVertex) * (m_RendererData->MaxVertices), GL_DYNAMIC_DRAW);
      m_RendererData->LineVertexBuffer->BindVertexBuffer();

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, Position));
      glEnableVertexAttribArray(0);

      // Color
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, Color));
      glEnableVertexAttribArray(1);

      m_RendererData->LineVertexBufferStart = new LineVertex[m_RendererData->MaxVertices];

      m_RendererData->LineVertexArray->UnbindVertexArray();

      m_RendererData->LineShader->LoadShadersFromFiles(Utils::GetFilePath("engine/assets/shaders/Line.vert"),
                                                       Utils::GetFilePath("engine/assets/shaders/Line.frag"));

  }

  void Renderer2D::StartBatch()
  {
    m_RendererData->QuadIndexCount = 0;
    m_RendererData->QuadVertexBufferCurrent = m_RendererData->QuadVertexBufferStart;

    m_RendererData->TriangleIndexCount = 0;
    m_RendererData->TriangleVertexBufferCurrent = m_RendererData->TriangleVertexBufferStart;

    m_RendererData->PointCount = 0;
    m_RendererData->PointVertexBufferCurrent = m_RendererData->PointVertexBufferStart;
    
    m_RendererData->LineVertexCount = 0;
    m_RendererData->LineVertexBufferCurrent = m_RendererData->LineVertexBufferStart;
  }

  void Renderer2D::Flush()
  {
    if (m_RendererData->QuadIndexCount) // Check if not zero
    {
      uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData->QuadVertexBufferCurrent - (uint8_t*)m_RendererData->QuadVertexBufferStart);
      m_RendererData->QuadVertexBuffer->SetVertexBufferData(m_RendererData->QuadVertexBufferStart, dataSize);
      m_RendererData->QuadShader->UseShader();

      m_RendererData->QuadShader->SetMatrix4fv(m_RendererData->QuadShader->GetUniformLocation("a_ProjectionMatrix"), Camera::GetProjectionViewMatrix());
      m_RendererData->QuadShader->SetVector4f(m_RendererData->QuadShader->GetUniformLocation("a_QuadColor"), m_RendererData->QuadVertexBufferStart->Color);
      
      m_RendererData->QuadVertexArray->BindVertexArray();
      m_RendererData->QuadIndexBuffer->BindIndexBuffer();

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
      m_RendererData->TriangleIndexBuffer->BindIndexBuffer();
      
      glDrawElements(GL_TRIANGLES, m_RendererData->TriangleIndexCount, GL_UNSIGNED_INT, nullptr);
    }

    if(m_RendererData->PointCount)
    {
      uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData->PointVertexBufferCurrent - (uint8_t*)m_RendererData->PointVertexBufferStart);
      m_RendererData->PointVertexBuffer->SetVertexBufferData(m_RendererData->PointVertexBufferStart, dataSize);
      m_RendererData->PointShader->UseShader();

      m_RendererData->PointShader->SetMatrix4fv(m_RendererData->PointShader->GetUniformLocation("a_ProjectionMatrix"), Camera::GetProjectionViewMatrix());
      m_RendererData->PointShader->SetVector4f(m_RendererData->PointShader->GetUniformLocation("f_PointColor"), m_RendererData->PointVertexBufferStart->Color);

      m_RendererData->PointVertexArray->BindVertexArray();

      glPointSize(3.0f); // For better visualisation
      glDrawArrays(GL_POINTS, 0, m_RendererData->PointCount);
    }

    if(m_RendererData->LineVertexCount)
    {
      uint32_t dataSize = (uint32_t)((uint8_t*)m_RendererData->LineVertexBufferCurrent - (uint8_t*)m_RendererData->LineVertexBufferStart);
      m_RendererData->LineVertexBuffer->SetVertexBufferData(m_RendererData->LineVertexBufferStart, dataSize);
      m_RendererData->LineShader->UseShader();

      m_RendererData->LineShader->SetMatrix4fv(m_RendererData->LineShader->GetUniformLocation("a_ProjectionMatrix"), Camera::GetProjectionViewMatrix());
      m_RendererData->LineShader->SetVector4f(m_RendererData->LineShader->GetUniformLocation("f_LineColor"), m_RendererData->LineVertexBufferStart->Color);

      m_RendererData->LineVertexArray->BindVertexArray();
      
      glLineWidth(m_Width);
      glDrawArrays(GL_LINES, 0, m_RendererData->LineVertexCount);
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
    
    uint32_t sizePoint = (uint32_t)((uint8_t*)m_RendererData->PointVertexBufferCurrent - (uint8_t*)m_RendererData->PointVertexBufferStart);
    m_RendererData->PointVertexBuffer->BindVertexBuffer();
    m_RendererData->PointVertexBuffer->SetVertexBufferData(m_RendererData->PointVertexBufferStart, sizePoint); // Set the vertex buffer data to the beginning of the buffer

    uint32_t sizeLine = (uint32_t)((uint8_t*)m_RendererData->LineVertexBufferCurrent - (uint8_t*)m_RendererData->LineVertexBufferStart);
    m_RendererData->LineVertexBuffer->BindVertexBuffer();
    m_RendererData->LineVertexBuffer->SetVertexBufferData(m_RendererData->LineVertexBufferStart, sizeLine); // Set the vertex buffer data to the beginning of the buffer
  }
  
  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    
    if(m_RendererData->QuadIndexCount >= m_RendererData->MaxQuadIndices)
    {
      EndBatch(); // Reset the data to the beginning of the buffer
      NextBatch(); // Render what's left and start batching again
    }

    // Calculate transformation matrix
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)); // Ensure correct scale along z-axis

    // Define quad vertices in object space
    glm::vec4 quadVertices[4] = {
        glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), // Top-left
        glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),  // Bottom-left
        glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),   // Bottom-right
        glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f)   // Top-right
    };

    // Update vertex buffer with transformed vertices
    for (int i = 0; i < 4; ++i) {
        m_RendererData->QuadVertexBufferCurrent->Position = transform * quadVertices[i];
        m_RendererData->QuadVertexBufferCurrent->Color = color;
        m_RendererData->QuadVertexBufferCurrent++;
    }

    // Update index count
    m_RendererData->QuadIndexCount += 6;
  }


  void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {

    if(m_RendererData->QuadIndexCount >= m_RendererData->MaxQuadIndices)
    {
      EndBatch(); // Reset the data to the beginning of the buffer
      NextBatch(); // Render what's left and start batching again
    }

    // Calculate transformation matrix
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)); 
 

    glm::vec4 quadVertices[4] = {
        glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), // Top-left
        glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),  // Bottom-left
        glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),   // Bottom-right
        glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f)   // Top-right
    };

    // Update vertex buffer with transformed vertices
    for (int i = 0; i < 4; ++i) {
        m_RendererData->QuadVertexBufferCurrent->Position = transform * quadVertices[i];
        m_RendererData->QuadVertexBufferCurrent->Color = color;
        m_RendererData->QuadVertexBufferCurrent++;
    }

    // Update index count
    m_RendererData->QuadIndexCount += 6;
  }

  void Renderer2D::DrawTexturedQuad(const std::string& filepath, const glm::vec2& position, const glm::vec2& size)
  {
    if(m_RendererData->QuadIndexCount >= m_RendererData->MaxQuadIndices)
    {
      EndBatch();
      NextBatch();
    }
  }


  void Renderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  { 
    // If the index count exceeds MaxIndex (which could happen...)
    if(m_RendererData->TriangleIndexCount >= m_RendererData->MaxTriangleIndices)
    {
      EndBatch(); // Reset the data to the beginning of the buffer
      NextBatch(); // Render what's left and start batching again
    }
    
    // Calculate transformation matrix
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f)); 

    glm::vec4 triangleVertices[4] = {
        glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), // Bottom left
        glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),  // Bottom right
        glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),   // Top
    };

    // Update vertex buffer with transformed vertices
    for (int i = 0; i < 3; i++) {
        m_RendererData->TriangleVertexBufferCurrent->Position = transform * triangleVertices[i];
        m_RendererData->TriangleVertexBufferCurrent->Color = color;
        m_RendererData->TriangleVertexBufferCurrent++;
    }

    m_RendererData->TriangleIndexCount += 3;

  }

  void Renderer2D::DrawPoint(const glm::vec2& position, const glm::vec4& color)
  {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));

    glm::vec4 pointVertex =  { 0.0f, 0.0f, 0.0f, 0.0f };

    m_RendererData->PointVertexBufferCurrent->Position = transform * pointVertex;
    m_RendererData->PointVertexBufferCurrent->Color = color;
    m_RendererData->PointVertexBufferCurrent++;

    // Update index count
    m_RendererData->PointCount += 1;
  }

  void Renderer2D::SetLineWidth(float width)
  {
    m_Width = width;
  }

  void Renderer2D::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color)
  {
    glm::vec4 lineVertex[] = {
        glm::vec4(start, 0.0f, 1.0f),
        glm::vec4(end, 0.0f, 1.0f)
    };

    for (int i = 0; i < 2; i++) {
        m_RendererData->LineVertexBufferCurrent->Position = lineVertex[i];
        m_RendererData->LineVertexBufferCurrent->Color = color;
        m_RendererData->LineVertexBufferCurrent++;
    }

    // Update index count
    m_RendererData->LineVertexCount += 2;
  }

  void Renderer2D::ShutdownRenderer()
  {
    delete[] m_RendererData->QuadVertexBufferStart;
    m_RendererData->QuadShader->DeleteShaders();
    m_RendererData->QuadShader->UnbindShader();

    delete[] m_RendererData->TriangleVertexBufferStart;
    m_RendererData->TriangleShader->DeleteShaders();
    m_RendererData->TriangleShader->UnbindShader();
    
    delete[] m_RendererData->PointVertexBufferStart;
    m_RendererData->PointShader->DeleteShaders();
    m_RendererData->PointShader->UnbindShader();

    delete[] m_RendererData->LineVertexBufferStart;
    m_RendererData->LineShader->DeleteShaders();
    m_RendererData->LineShader->UnbindShader();

    delete m_RendererData;
    m_RendererData = nullptr;
  }

}; 

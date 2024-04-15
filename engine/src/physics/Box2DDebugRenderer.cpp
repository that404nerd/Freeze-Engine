#include "Box2DDebugRenderer.h"

namespace Freeze {

    Box2DDebugRenderer::Box2DDebugRenderer(const uint32_t DrawFlags)
    {
        SetFlags(DrawFlags);
    }

    void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
    {
      // FZ_INFO("DEBUG RENDER: Rendering solid polygon with: {} vertices", vertexCount);

      glColor4f(color.r, color.g, color.b, 1.0f); // Use the provided color

      // Set the rendering mode to draw outlines
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      // Render the solid polygon outline
      glBegin(GL_LINE_LOOP);
      for (int32 i = 0; i < vertexCount; ++i) {
          glVertex2f(vertices[i].x, vertices[i].y);
      }
      glEnd();

      // Restore the rendering mode
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    Box2DDebugRenderer::~Box2DDebugRenderer() {}
};

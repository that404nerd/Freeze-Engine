#include "Box2DDebugRenderer.h"

namespace Freeze {

    Box2DDebugRenderer::Box2DDebugRenderer(const uint32_t DrawFlags)
    {
        SetFlags(DrawFlags);
    }

    void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
    {
        glm::vec4 lineColor = { color.r, color.g, color.b, color.a };
        
        // Loop through the vertices and draw lines between consecutive vertices
        for(int i = 0; i < vertexCount; i++)
        {
            const glm::vec2 start = { vertices[i].x, vertices[i].y };
            const glm::vec2 end = { vertices[(i + 1) % vertexCount].x, vertices[(i + 1) % vertexCount].y };
            Renderer2D::SetLineWidth(2.0f);
            Renderer2D::DrawLine(start, end, lineColor);
        }
    }
    Box2DDebugRenderer::~Box2DDebugRenderer() {}
};

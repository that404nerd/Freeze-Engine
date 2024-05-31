#pragma once

#include <GL/glew.h>
#include <box2d/box2d.h>
#include <memory>

#include "core/Core.h"
#include "renderer/Renderer2D.h"

namespace Freeze {

	class Box2DDebugRenderer : public b2Draw {
	public:
		Box2DDebugRenderer(const uint32_t DrawFlags);

		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {};
		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color&color) override;
		void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override {};
		void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override {};
		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {};
		void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override {};
		void DrawTransform(const b2Transform& xf) override {};

		~Box2DDebugRenderer();
	};
};

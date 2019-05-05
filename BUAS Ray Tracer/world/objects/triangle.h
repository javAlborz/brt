#pragma once
#include "sceneobject.h"

namespace brt
{
#define TOTAL_TRIANGLE_VERTICES 3

	class triangle : public sceneobject
	{
	public:
		triangle(const vec3& pos, std::shared_ptr<material> mat, const vec3 vertices[3]);
		virtual ~triangle();

		virtual vec3 get_normal_at(const vec3& point) const override;

		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) override;
	
	private:
		vec3 m_vertices[TOTAL_TRIANGLE_VERTICES];
		vec3 m_normal;
	};
}
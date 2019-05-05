#pragma once
#include "sceneobject.h"

namespace brt
{
	class sphere : public sceneobject
	{
	public:
		sphere(const vec3& pos, float radius, std::shared_ptr<material> mat);
		virtual ~sphere();

		virtual vec3 get_normal_at(const vec3& point) const override;

		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) override;

	private:
		float m_radius;
	};
}
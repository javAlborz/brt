#pragma once
#include "../entity.h"

#include <memory>

#include "../../math/mathlibrary.h"

#include "../../rendering/materials/material.h"

namespace sf
{
	class Color;
}

namespace brt
{
	struct ray;
	struct intersection;

	class sceneobject : public entity
	{
	public:
		sceneobject(const vec3& pos, std::shared_ptr<material> mat);
		virtual ~sceneobject();

		virtual vec3 get_normal_at(const vec3& point) const = 0;
		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) = 0;

		std::shared_ptr<material> get_object_material() { return m_mat; }

	protected:
		vec3 calculate_intersection_point(float t, const vec3& origin, const vec3& direction);
	
	protected:
		std::shared_ptr<material> m_mat;
	};
}
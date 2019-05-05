#pragma once
#include "sceneobject.h"

namespace brt
{
	class plane : public sceneobject
	{
	public:
		plane(const vec3& pos, const vec3& normal, std::shared_ptr<material> mat);
		virtual ~plane();

		virtual vec3 get_normal_at(const vec3& point) const override;

		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) override;

	protected:
		bool has_plane_intersection(const vec3& origin, const vec3& dir, intersection& info);

	protected:
		vec3 m_normal;
	};
}
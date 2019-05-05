#include "plane.h"

#include "../../ray/ray.h"
#include "../../ray/intersection.h"

namespace brt
{
	plane::plane(const vec3& pos, const vec3& normal, std::shared_ptr<material> mat)
		: sceneobject(pos, mat), m_normal(normal)
	{
	}


	plane::~plane()
	{
	}

	// TODO: find a more elegant solution that doesn't need a point parameter
	vec3 plane::get_normal_at(const vec3&) const // normal is the same over the entire plane, no point variable needed
	{
		return m_normal;
	}

	bool plane::has_intersection(const vec3& origin, const vec3& dir, intersection& info)
	{
		return has_plane_intersection(origin, dir, info);
	}

	bool plane::has_plane_intersection(const vec3& origin, const vec3& dir, intersection & info)
	{
		float denom = dir.dot(m_normal);
		if (denom != 0.f) // if ray not parallel to plane (denum will be zero when r.dir and normal are perpendicular)
		{
			float dist = -(m_normal.dot(origin - position)) / denom;
			if (dist >= 0.f) // if in front of camera
			{
				info.object = this;
				info.distance = dist;
				info.intersectionpoint = calculate_intersection_point(dist, origin, dir);
				return true;
			}
		}

		return false;
	}
}

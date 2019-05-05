#include "aabb.h"

#include "../../ray/ray.h"
#include "../../ray/intersection.h"

#include "../../debugging/debugtools.h"

#define NORMAL_BIAS 1.0001f

namespace brt
{
	aabb::aabb(const vec3& pos, const vec3 bounds[2], std::shared_ptr<material> mat) : sceneobject(pos, mat)
	{
		m_localbounds[0] = bounds[0];
		m_localbounds[1] = bounds[1];
	}

	aabb::aabb(const vec3& size, std::shared_ptr<material> mat) : sceneobject(vec3(), mat)
	{
		m_localbounds[0] = size * -1.f;
		m_localbounds[1] = size;
	}

	aabb::~aabb()
	{

	}

	vec3 aabb::get_normal_at(const vec3 & atpos) const
	{
		// algorithm from https://blog.johnnovak.net/2016/10/22/the-nim-raytracer-project-part-4-calculating-box-normals/
		// this way the normal can be calculated without any if statements.

		vec3 c = (m_localbounds[0] + m_localbounds[1]) * 0.5f;
		vec3 p = get_transformation_matrix().inverse_transform_vector(atpos) - position - c; // "- transform.position()" because bounds are local. transforming world position to position in objects coordinate system
		vec3 d = (m_localbounds[0] - m_localbounds[1]) * 0.5f;

		return vec3(
			static_cast<float>(static_cast<int>((p.m_X / abs(d.m_X)) * NORMAL_BIAS)),
			static_cast<float>(static_cast<int>((p.m_Y / abs(d.m_Y)) * NORMAL_BIAS)),
			static_cast<float>(static_cast<int>((p.m_Z / abs(d.m_Z)) * NORMAL_BIAS))).normalize(); // take int part of float, so rounding down, conversion here is intentional.
	}

	bool aabb::has_intersection(const vec3& origin, const vec3& dir, intersection & info)
	{
		// settled for algorithm from scratchapixel because of its efficiency.
		// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

		vec3 invdir = vec3(dir).invert(); // 1 / ray_dir, 1/0 will be positive infinity

		float tmin, tmax, tymin, tymax;
		tmin = (get_bound(invdir.m_X < 0).m_X - origin.m_X) * invdir.m_X;
		tmax = (get_bound(1 - (invdir.m_X < 0)).m_X - origin.m_X) * invdir.m_X;
		tymin = (get_bound(invdir.m_Y < 0).m_Y - origin.m_Y) * invdir.m_Y;
		tymax = (get_bound(1 - (invdir.m_Y < 0)).m_Y - origin.m_Y) * invdir.m_Y;

		if ((tmin > tymax) || (tymin > tmax))
			return false;
		if (tymin > tmin)
			tmin = tymin;
		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (get_bound(invdir.m_Z < 0).m_Z - origin.m_Z) * invdir.m_Z;
		float tzmax = (get_bound(1 - (invdir.m_Z < 0)).m_Z - origin.m_Z) * invdir.m_Z;

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;
		if (tzmin > tmin)
			tmin = tzmin;
		if (tzmax < tmax)
			tmax = tzmax;

		if (tmin > 0)
		{
			info.object = this;
			info.distance = tmin;
			info.intersectionpoint = get_transformation_matrix().transform_vector(calculate_intersection_point(tmin, origin, dir)); // transform to world position
			return true;
		}
		return false;
	}
}
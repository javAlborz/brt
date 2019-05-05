#include "sphere.h"

#include "../../ray/ray.h"

namespace brt
{
	sphere::sphere(const vec3& pos, float radius, std::shared_ptr<material> mat) :
		sceneobject(pos, mat), m_radius(radius)
	{
	}

	sphere::~sphere()
	{

	}

	vec3 sphere::get_normal_at(const vec3& point) const
	{
		// n = (p-c) / r
		return ((point - position) / m_radius).normalize();
	}

	bool sphere::has_intersection(const vec3& origin, const vec3& dir, intersection& info)
	{
		vec3 local = origin - position;
		//float a = 1; // normalizedvec.dot(normalizedvec) = 1 = r.get_direction().dot(r.get_direction());   leaving this out of formula since its unnecessary
		float b = 2.f * (local).dot(dir);
		float c = (local).dot(local) - pow(m_radius, 2);
		float discriminant = pow(b, 2) - 4 * c; // discriminant = b^2 - 4ac, a=1 so leaving this out

		if (discriminant < 0.f) // ray missed sphere
		{
			return false;
		}

		float root1 = ((-1.f * b - sqrt(discriminant)) / 2.f) - FLOAT_EPSILON;
		if (root1 > 0.f)
		{
			info.distance = root1; // root1 is smallest positive root, first root of intersection
		}
		else
		{
			float root2 = ((sqrt(discriminant) - b) / 2.f) - FLOAT_EPSILON;
			if (root2 <= 0.f)
			{
				return false;
			}
			info.distance = root2; // root2 is smallest positive root, second root of the intersection
		}

		info.object = this;
		info.intersectionpoint = calculate_intersection_point(info.distance, origin, dir);
		info.hasintersection = true;
		return true;
	}
}
#include "quadrilateral.h"

#include "../../ray/intersection.h"

namespace brt
{
	quadrilateral::quadrilateral(const vec3& pos, const vec3& normal, std::shared_ptr<material> mat, const vec3 localverts[TOTAL_QUADRILATERAL_VERTICES]) : plane(pos, normal, mat)
	{
		// TODO: assert(all vertices coplanar)

		for (int i = 0; i < TOTAL_QUADRILATERAL_VERTICES; i++)
		{
			m_localverts[i] = localverts[i];
		}
	}

	quadrilateral::~quadrilateral()
	{
	}

	vec3 quadrilateral::get_normal_at(const vec3&) const
	{
		return m_normal;
	}

	bool quadrilateral::has_intersection(const vec3& origin, const vec3& dir, intersection& info)
	{
		if (has_plane_intersection(origin, dir, info)) // TODO: fix messy code that only works on one dimension, the one that I need
		{
			float width = abs((m_localverts[0] - m_localverts[1]).length());
			float height = abs((m_localverts[0] - m_localverts[2]).length());

			vec3 localinterpoint = info.intersectionpoint - transform.position();
			if (localinterpoint.m_X >= 0.f && localinterpoint.m_X < width &&
				localinterpoint.m_Z >= 0.f && localinterpoint.m_Z < height)
			{
				return true;
			}
		}
		return false;
	}
}
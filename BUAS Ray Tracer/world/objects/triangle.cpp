#include "triangle.h"

#include "../../ray/ray.h"
#include "../../ray/intersection.h"

namespace brt
{
	triangle::triangle(const vec3& pos, std::shared_ptr<material> mat, const vec3 vertices[TOTAL_TRIANGLE_VERTICES]) : sceneobject(pos, mat)
	{
		for (int i = 0; i < TOTAL_TRIANGLE_VERTICES; i++)
		{
			m_vertices[i] = vertices[i];
		}

		vec3 line01 = m_vertices[1] - m_vertices[0]; // edge 0
		vec3 line02 = m_vertices[2] - m_vertices[0]; // edge 1
		m_normal = line01.cross(line02).normalize();
	}

	triangle::~triangle()
	{
	}

	// TODO: find a more elegant solution that doesn't need a point parameter
	vec3 triangle::get_normal_at(const vec3&) const // normal is the same over the entire triangle, no point variable needed
	{
		return m_normal;
	}

	bool triangle::has_intersection(const vec3& origin, const vec3& dir, intersection & info)
	{
		float a = dir.dot(m_normal);
		if (!mathlibrary::are_numbers_equal_epsilon(a, 0.f)) // if not parallel: if !(normal is perpendicular to raydir)
		{
			float D = m_normal.dot(m_vertices[0]); // D = distance from origin (0,0,0) to the plane (if we trace a line from origin to the plane, parallel to the plane's normal)

			float t = -(m_normal.dot(origin) + D) / a; // a can't be zero, checked earlier
			
			if (t >= 0.f) // if in front of camera
			{
				// inside-outside test
				vec3 possibleintersectionpoint = calculate_intersection_point(t, origin, dir);

				vec3 edge0 = m_vertices[1] - m_vertices[0];
				vec3 vp0 = possibleintersectionpoint - m_vertices[0];

				vec3 edge1 = m_vertices[2] - m_vertices[1];
				vec3 vp1 = possibleintersectionpoint - m_vertices[1];

				vec3 edge2 = m_vertices[0] - m_vertices[2];
				vec3 vp2 = possibleintersectionpoint - m_vertices[2];

				if (m_normal.dot(edge0.cross(vp0)) >= 0.f &&
					m_normal.dot(edge1.cross(vp1)) >= 0.f &&
					m_normal.dot(edge2.cross(vp2)) >= 0.f )
				{
					info.object = this;
					info.distance = t;
					info.intersectionpoint = possibleintersectionpoint;
					return true; // ray hits the triangle
				}
			}
		}
		return false;
	}
}
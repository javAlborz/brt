#pragma once
#include "plane.h"

namespace brt
{
#define TOTAL_QUADRILATERAL_VERTICES 4

	class quadrilateral : public plane // TODO: currently quadrilateral is a rectangle, might want to add support for other quadrilaterals, and have quadrilateral be an abstract class
	{
	public:
		quadrilateral(const vec3& pos, const vec3& normal, std::shared_ptr<material> mat, const vec3 localverts[TOTAL_QUADRILATERAL_VERTICES]);
		virtual ~quadrilateral();

		virtual vec3 get_normal_at(const vec3& point) const override;

		virtual bool has_intersection(const vec3& origin, const vec3& dir, intersection& info) override;

	protected:
		// 0 1
		// 2 3
		vec3 m_localverts[TOTAL_QUADRILATERAL_VERTICES];
	};
}
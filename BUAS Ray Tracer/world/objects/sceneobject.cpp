#include "sceneobject.h"

namespace brt
{
	sceneobject::sceneobject(const vec3& pos, std::shared_ptr<material> mat) : entity(pos), m_mat(mat)
	{
	}

	sceneobject::~sceneobject()
	{
	}

	vec3 sceneobject::calculate_intersection_point(float t, const vec3& origin, const vec3& direction)
	{
		return origin + direction * t;
	}
}
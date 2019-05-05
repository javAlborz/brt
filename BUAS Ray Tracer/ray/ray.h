#pragma once
#include <vector>

#include "../math/MathLibrary.h"

#include "intersection.h"

namespace brt
{
	class scene;

	struct ray
	{
		ray(const vec3& origin, const vec3& localdir);

		vec3 origin;
		vec3 direction;
	};
}
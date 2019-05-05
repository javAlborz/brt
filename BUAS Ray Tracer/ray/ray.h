#pragma once
#include "../math/MathLibrary.h"

namespace brt
{
	struct ray
	{
		ray(const vec3& origin, const vec3& localdir);

		vec3 origin;
		vec3 direction;
	};
}
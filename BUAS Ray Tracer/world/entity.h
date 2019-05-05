#pragma once
#include "../math/MathLibrary.h"

namespace brt
{
	class entity
	{
	public:
		entity();
		explicit entity(const vec3 &pos);
		virtual ~entity();

		virtual void update(float) {}

	public:
		mat4 transform;
	};
}
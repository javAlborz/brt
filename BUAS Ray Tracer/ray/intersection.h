#pragma once
#include "../math/MathLibrary.h"

namespace brt
{
	class sceneobject;

	struct intersection
	{
		intersection();

		bool hasintersection;
		float distance;
		sceneobject* object;
		vec3 intersectionpoint;
	};
}
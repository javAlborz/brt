#include "intersection.h"

#include "../world/objects/sceneobject.h"

namespace brt
{
	intersection::intersection() : hasintersection(false), distance(0.f), object(nullptr), intersectionpoint(vec3())
	{
	}
}
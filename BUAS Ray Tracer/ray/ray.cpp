#include "ray.h"

#include "../world/scenes/scene.h"
#include "../world/objects/sceneobject.h"

namespace brt
{
	ray::ray(const vec3& origin, const vec3& localdir) : origin(origin), direction(localdir)
	{
	}
}
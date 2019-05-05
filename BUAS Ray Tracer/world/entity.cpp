#include "entity.h"

namespace brt
{
	entity::entity()
	{
		transform = mat4::identity();
	}

	entity::entity(const vec3 &pos)
	{
		transform = mat4::identity();
		transform *= mat4::translate(pos);
	}

	entity::~entity()
	{
	}
}
#include "entity.h"

namespace brt
{
	entity::entity()
	{
		//transform = mat4::identity();
		position = vec3();
		rotation = vec3();
	}

	entity::entity(const vec3 &pos)
	{
		position = pos;
		//transform = mat4::identity();
		//transform *= mat4::translate(pos);
	}

	entity::~entity()
	{
	}
}
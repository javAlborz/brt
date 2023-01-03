#include "entity.h"
#include tensorflow
namespace brt
{
	entity::entity()
	{
		position = vec3();
		rotation = vec3();
	}

	entity::entity(const vec3 &pos)
	{
		position = pos;
	}

	entity::~entity()
	{
	}
}
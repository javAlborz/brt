#pragma once
#include "light.h"

namespace brt
{
	class pointlight : public light
	{
	public:
		pointlight(const vec3& lightpos, sf::Color lightcolor, float intensity);
		virtual ~pointlight();

		vec3 get_light_dir(const vec3& atpos) const;
	};
}
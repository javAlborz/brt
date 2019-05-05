#pragma once
#include "light.h"

namespace brt
{
	class directionallight : public light
	{
	public:
		directionallight(const vec3& unitlightdir, sf::Color lightcolor, float intensity);
		virtual ~directionallight();

		vec3 get_light_dir() const;

	private:
		vec3 m_lightdir;
	};
}
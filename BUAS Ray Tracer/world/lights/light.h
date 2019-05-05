#pragma once
#include "../entity.h"

#include <SFML/Graphics.hpp>

enum LTYPE
{
	LTYPE_NONE = 0,
	LTYPE_POINT,
	LTYPE_DIRECTIONAL,
	LTYPE_COUNT
};

namespace brt
{
	class light : public entity
	{
	public:
		light(sf::Color lightcolor, float intensity);
		light(const vec3& pos, sf::Color lightcolor, float intensity);
		virtual ~light();

		sf::Color get_light_color() const { return m_lightcolor; }

		float get_light_intensity() const { return m_lightintensity; }

		LTYPE m_ltype; // TODO: this should only be set in constructor, restrict access

	protected:
		sf::Color m_lightcolor;
		float m_lightintensity;
	};
}
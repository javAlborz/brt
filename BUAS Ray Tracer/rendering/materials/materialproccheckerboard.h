#pragma once
#include "material.h"


namespace brt
{
	struct materialproccheckerboard : material
	{
		materialproccheckerboard(float tilesize, sf::Color color1, sf::Color color2) :
			m_tilesize(tilesize), m_color1(color1), m_color2(color2)
		{
			m_mattype = MTYPE_PROCCHECKERBOARD;
		}

		sf::Color get_color_at(float u, float v) // could do without the else statements and just a return at the end but this is better readable
		{
			assert(m_tilesize > 0);

			if ((mathlibrary::modulo(v / m_tilesize) < 0.5f) ^ (mathlibrary::modulo(u / m_tilesize) < 0.5f)) // ^ = XOR operator, either/or
			{
				return m_color1;
			}
			else
			{
				return m_color2;
			}
		}

	private:
		float m_tilesize;
		sf::Color m_color1;
		sf::Color m_color2;
	};
}
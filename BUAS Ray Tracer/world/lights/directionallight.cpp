#include "directionallight.h"

namespace brt
{
	directionallight::directionallight(const vec3 & unitlightdir, sf::Color lightcolor, float intensity) :
		light(lightcolor, intensity), m_lightdir(unitlightdir)
	{
		m_ltype = LTYPE_DIRECTIONAL;
	}

	directionallight::~directionallight()
	{

	}

	vec3 directionallight::get_light_dir() const
	{
		return m_lightdir;
	}
}
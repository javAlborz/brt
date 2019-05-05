#include "light.h"

namespace brt
{
	light::light(color lightcolor, float intensity)
		: entity(), m_lightcolor(lightcolor), m_lightintensity(intensity)
	{
	}

	light::light(const vec3& pos, color lightcolor, float intensity)
		: entity(pos), m_lightcolor(lightcolor), m_lightintensity(intensity)
	{
	}

	light::~light()
	{
	}
}
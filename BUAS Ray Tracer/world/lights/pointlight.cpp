#include "pointlight.h"

namespace brt
{
	pointlight::pointlight(const vec3 & lightpos, color lightcolor, float intensity) :
		light(lightpos, lightcolor, intensity)
	{
		m_ltype = LTYPE::POINT;
	}

	pointlight::~pointlight()
	{

	}

	vec3 pointlight::get_light_dir(const vec3 & atpos) const
	{
		return (position - atpos).normalize();
	}

}
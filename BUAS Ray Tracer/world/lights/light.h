#pragma once
#include "../entity.h"

#include "../../math/color.h"

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
		light(color lightcolor, float intensity);
		light(const vec3& pos, color lightcolor, float intensity);
		virtual ~light();

		color get_light_color() const { return m_lightcolor; }

		float get_light_intensity() const { return m_lightintensity; }

		LTYPE m_ltype; // TODO: this should only be set in constructor, restrict access

	protected:
		color m_lightcolor;
		float m_lightintensity;
	};
}
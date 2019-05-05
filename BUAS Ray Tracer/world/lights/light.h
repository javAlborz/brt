#pragma once
#include "../entity.h"

#include "../../math/color.h"

enum class LTYPE
{
	NONE = 0,
	POINT,
	DIRECTIONAL,
	COUNT
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

		LTYPE GetLightType() const { return m_ltype; }

	protected:
		LTYPE m_ltype;

		color m_lightcolor;
		float m_lightintensity;
	};
}
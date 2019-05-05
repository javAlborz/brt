#pragma once
#include "material.h"
#include "../../math/color.h"

#define SPECNONE			0.f
#define SPECEGGSHELL		10.f
#define SPECMIDLYSHINY		100.f
#define SPECREALLYGLOSSY	1000.f
#define SPECNEARLYMIRROR	10000.f

#define REFLECTNONE			0.f
#define REFLECTALL			1.f

#define REFRACTIVENONE		1.f // equal to air
#define REFRACTIVEWATER		1.3f
#define REFRACTIVEGLASS		1.5f
#define REFRACTIVEDIAMOND	1.8f

namespace brt
{
	struct materialdefault : material
	{
		materialdefault() :
			m_diffusecolor(color()), m_specularintensity(SPECMIDLYSHINY), m_specularcolor(color()), m_reflectionintensity(REFLECTNONE), m_refractive(false), m_refractiveindex(REFRACTIVENONE)
		{
			m_mattype = MTYPE_DEFAULT;
		}

		materialdefault(color diffusecolor, float specularintensity = SPECNONE, color specularcolor = color(), float reflectionintensity = REFLECTNONE, bool refractive = false, float refractiveindex = REFRACTIVENONE) :
			m_diffusecolor(diffusecolor), m_specularintensity(specularintensity), m_specularcolor(specularcolor), m_reflectionintensity(reflectionintensity), m_refractive(refractive), m_refractiveindex(refractiveindex)
		{
			m_mattype = MTYPE_DEFAULT;
		}

		color m_diffusecolor;

		float m_specularintensity;
		color m_specularcolor;

		float m_reflectionintensity;

		bool m_refractive;
		float m_refractiveindex;
	};
}
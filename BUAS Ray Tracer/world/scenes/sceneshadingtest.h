#pragma once
#include "scene.h"

namespace brt
{
	class sceneshadingtest : public scene
	{
	public:
		sceneshadingtest(raytracer* application);
		virtual ~sceneshadingtest();

	private:
		void build_scene();
	};
}
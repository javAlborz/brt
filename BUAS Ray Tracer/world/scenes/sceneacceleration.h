#pragma once
#include "scene.h"

namespace brt
{
	class sceneacceleration : public scene
	{
	public:
		sceneacceleration(raytracer* application);
		virtual ~sceneacceleration();

	private:
		void build_scene();
	};
}
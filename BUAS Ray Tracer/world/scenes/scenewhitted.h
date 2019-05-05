#pragma once
#include "scene.h"

namespace brt
{
	class scenewhitted : public scene
	{
	public:
		scenewhitted(raytracer* application);
		virtual ~scenewhitted();

	private:
		void build_scene();
	};
}
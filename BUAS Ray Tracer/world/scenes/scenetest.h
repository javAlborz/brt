#pragma once
#include "scene.h"

namespace brt
{
	class scenetest : public scene
	{
	public:
		scenetest(raytracer* application);
		virtual ~scenetest();

	private:
		void build_scene();
	};
}
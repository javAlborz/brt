#pragma once
#include "scene.h"

namespace brt
{
	class scenecornell : public scene
	{
	public:
		scenecornell(raytracer* application);
		virtual ~scenecornell();

	private:
		void build_scene();
	};
}
#pragma once
#include "scene.h"

class vec3;

namespace brt
{
	class sceneboxes : public scene
	{
	public:
		sceneboxes(raytracer* application);
		virtual ~sceneboxes();

	private:
		void build_scene();

		void spawn_group(float raddir, float disttocenter);
			
		/// find a position for the box in the area where boxes are placed
		vec3 find_box_pos();
	};
}
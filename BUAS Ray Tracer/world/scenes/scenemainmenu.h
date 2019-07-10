#pragma once
#include "scene.h"

namespace brt
{
	class scenemainmenu : public scene
	{
	public:
		scenemainmenu(raytracer* application);
		virtual ~scenemainmenu();

		virtual void update(float deltat) override;

	private:
		void build_scene();

		float m_imageScaling;
	};
}
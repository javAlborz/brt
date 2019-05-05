#pragma once
#include "../world/entity.h"

#define SKYCOLOR color(85.f, 89.f, 107.f)
#define GLOBALAMBIENTCOLOR color(40.f, 40.f, 40.f)

namespace sf
{
	class Color;
	class Image;
}

namespace brt
{
	struct ray;
	class scene;
	class raytracer;
	class sceneobject;
	class light;
	struct color;

	class camera : public entity
	{
	public:
		camera(const vec3& lookpos, const vec3& campos, const vec3& up, float screenwidth, float screeneheight);
		~camera();

		virtual void update(float deltat) override;

		const float get_aspect_ratio() const;

		const float get_screen_width() const;
		const float get_screen_height() const;

		const vec3 get_cam_dir() const;
		const vec3 get_cam_right() const;
		const vec3 get_cam_down() const;

	public:
		float m_screenwidth, m_screenheight;
		vec3 m_camdir, m_camright, m_camdown;

		// TODO: implement near and far? proper view frustrum
	};
}
#include "camera.h"
#include "SFML/Window/Keyboard.hpp"

#define CAMMOVESPEED 1.f
#define CAMMOVEBOOSTSPEED 4.f

namespace brt
{
	camera::camera(const vec3 & lookpos, const vec3 & campos, const vec3 & up, float screenwidth, float screeneheight) :entity(campos), m_screenwidth(screenwidth), m_screenheight(screeneheight)
	{
		vec3 diff_btw = campos - lookpos;
		m_camdir = diff_btw.normalize() * -1.f;

		m_camright = up.cross(m_camdir).normalize();
		m_camdown = m_camright.cross(m_camdir);
	}

	camera::~camera()
	{
	}

	void camera::update(float deltat)
	{
		// TODO: render ui sprite showing that the camera can move

		// speed
		float speed = CAMMOVESPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			speed = CAMMOVEBOOSTSPEED;
		}

		// position
		// TODO: fly in direction that camera is facing, this is necessary when the camera can rotate
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			position += vec3(1.f, 0.f, 0.f) * deltat * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			position += vec3(-1.f, 0.f, 0.f) * deltat * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			position += vec3(0.f, 0.f, 1.f) * deltat * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			position += vec3(0.f, 0.f, -1.f) * deltat * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			position += vec3(0.f, 1.f, 0.f) * deltat * speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			position += vec3(0.f, -1.f, 0.f) * deltat * speed;
		}

		// direction
		// TODO: change camera to look towards a rotation, instead of towards a point, then rotate camera with mouse/keys to able to fly around
	}

	const float camera::get_aspect_ratio() const
	{
		return m_screenwidth / m_screenheight;
	}
	const float camera::get_screen_width() const
	{
		return m_screenwidth;
	}

	const float camera::get_screen_height() const
	{
		return m_screenheight;
	}

	const vec3 camera::get_cam_dir() const
	{
		return m_camdir;
	}

	const vec3 camera::get_cam_right() const
	{
		return m_camright;
	}

	const vec3 camera::get_cam_down() const
	{
		return m_camdown;
	}

}
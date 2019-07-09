#pragma once
#include <memory>

namespace sf
{
	class Color;
	class Clock;
}

namespace brt
{
	class scene;
	class scenemanager;
	class renderer;
	class commandlineinputhandler;

	class raytracer
	{
	public:
		raytracer();
		~raytracer();

		scene* get_scene() const;
		renderer* get_renderer() const;
		scenemanager* get_scene_manager();

	private:
		void start();
		void run();
		void destroy();

		void update(float deltat);

		const float get_elapsed_time() const;

	private:
		scenemanager* m_scenemanager;

		renderer* m_renderer;

		sf::Clock* m_clock;
	};
}
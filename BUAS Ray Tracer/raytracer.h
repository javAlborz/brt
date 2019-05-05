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
	class renderer;
	class commandlineinputhandler;

	class raytracer
	{
	public:
		raytracer();
		~raytracer();

		scene* get_scene() const;
		renderer* get_renderer() const;

		void load_scene(scene* s);

	private:
		void start();
		void run();
		void destroy();

		void update(float deltat);

		const float get_elapsed_time() const;

	private:
		std::unique_ptr<commandlineinputhandler> m_inputhandler;

		scene* m_scene;

		renderer* m_renderer;

		sf::Clock* m_clock;
	};
}
#include "raytracer.h"

#include <SFML/Graphics.hpp>
#include <assert.h>

#include "rendering/renderer.h"

#include "world/scenes/scene.h"
#include "world/scenes/scenewhitted.h"
#include "world/scenes/scenecornell.h"
#include "world/scenes/sceneboxes.h"
#include "world/scenes/scenetest.h"

#include "world/scenes/sceneacceleration.h"

#include "userinput/commandlineinputhandler.h"

// to show console
#include <windows.h>

namespace brt
{
	raytracer::raytracer()
	{
		start();
	}


	raytracer::~raytracer()
	{
	}

	void raytracer::start()
	{
		m_clock = new sf::Clock();

		m_renderer = new renderer(this);

		// bring console window forward
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE); // for some reason window thinks it's already shown, have to hide it first
		ShowWindow(hWnd, SW_SHOW);

		m_inputhandler = std::make_unique<commandlineinputhandler>(this);

		run();
	}

	void raytracer::run()
	{
		float lastelapsedtime = 0.f;

		while (m_renderer->get_window()->isOpen())
		{
			// input events, it would be even better to have the input event separate from the window, but this isn't how sfml works. Input handling will be dependant on window, will build an input handler in the future.
			sf::Event event;
			while (m_renderer->get_window()->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_renderer->get_window()->close();
			}

			// clear renderer
			m_renderer->window_clear();

			// update
			float deltat = get_elapsed_time() - lastelapsedtime;
			lastelapsedtime = get_elapsed_time();
			update(deltat);

			// render
			m_renderer->window_display();
		}

		destroy();
	}

	void raytracer::destroy()
	{
		delete m_renderer;

		if (m_scene)
		{
			delete m_scene;
		}
	}

	void raytracer::update(float deltat)
	{
		assert(deltat != 0.f);
		printf("deltatime: %.4f, fps: %.2f\n", deltat, 1.f / deltat);

		m_scene->update(deltat);
		m_renderer->update(deltat);
	}

	void raytracer::load_scene(scene* s)
	{
		if (m_scene)
		{
			delete m_scene;
		}
		m_scene = s;
	}

	const float raytracer::get_elapsed_time() const
	{
		sf::Time t = m_clock->getElapsedTime();
		return t.asSeconds();
	}

	scene * raytracer::get_scene() const
	{
		return m_scene;
	}

	renderer * raytracer::get_renderer() const
	{
		return m_renderer;
	}
}
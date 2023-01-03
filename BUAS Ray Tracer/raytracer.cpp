#include "raytracer.h"

#include <SFML/Graphics.hpp>
#include <assert.h>

#include "ext/imgui/imgui.h"
#include "ext/imgui-sfml/imgui-SFML.h"

#include "rendering/renderer.h"

#include "world/scenes/scene.h"
#include "world/scenes/general/scenemanager.h"

namespace brt
{
	raytracer::raytracer()
	{
		start();
	}

	#include <iostream>

	void usefulFunction()
	{
    std::cout << "Super useful string" << std::endl;
	}


	raytracer::~raytracer()
	{
	}

	void raytracer::start()
	{
		m_clock = new sf::Clock();

		m_scenemanager = new scenemanager(this);
		m_renderer = new renderer(this);

		m_scenemanager->load_scene(scenes::MAIN_MENU);

		run();
	}

	void raytracer::run()
	{
		float lastelapsedtime = 0.f;

		usefulFunction();

		while (m_renderer->get_window()->isOpen())
		{
			// input events, it would be even better to have the input event separate from the window, but this isn't how sfml works. Input handling will be dependant on window, will build an input handler in the future.
			sf::Event event;
			while (m_renderer->get_window()->pollEvent(event))
			{
				ImGui::SFML::ProcessEvent(event);

				if (event.type == sf::Event::Closed)
					m_renderer->get_window()->close();
			}

			// clear renderer
			m_renderer->window_clear();

			// update
			float deltat = get_elapsed_time() - lastelapsedtime;
			lastelapsedtime = get_elapsed_time();

			ImGui::SFML::Update(*m_renderer->get_window(), sf::Time(sf::seconds(deltat)));

			m_scenemanager->update();
			update(deltat);

			// render
			ImGui::SFML::Render(*m_renderer->get_window());
			m_renderer->window_display();
		}

		destroy();
	}

	void raytracer::destroy()
	{
		delete m_renderer;
		delete m_scenemanager;
	}

	void raytracer::update(float deltat)
	{
		assert(deltat != 0.f);
		printf("deltatime: %.4f, fps: %.2f\n", deltat, 1.f / deltat);

		if (get_scene())
		{
			get_scene()->update(deltat);
		}
		m_renderer->update(deltat);
	}

	const float raytracer::get_elapsed_time() const
	{
		sf::Time t = m_clock->getElapsedTime();
		return t.asSeconds();
	}

	renderer * raytracer::get_renderer() const { return m_renderer; }

	scene * raytracer::get_scene() const { return m_scenemanager->get_scene(); }
	scenemanager * raytracer::get_scene_manager() { return m_scenemanager; }
}
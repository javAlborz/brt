#include "commandlineinputhandler.h"

#include <stdio.h>
#include <iostream>

#include "../raytracer.h"

#include "../world/scenes/scenewhitted.h"
#include "../world/scenes/sceneboxes.h"
#include "../world/scenes/scenetest.h"
#include "../world/scenes/sceneacceleration.h"

namespace brt
{
	commandlineinputhandler::commandlineinputhandler(raytracer* application) : m_application(application)
	{
		load_scene_menu();
	}

	commandlineinputhandler::~commandlineinputhandler()
	{

	}

	void commandlineinputhandler::update(float)
	{

	}

	void commandlineinputhandler::load_scene_menu()
	{
		m_state = LOAD_SCENE;

		printf("Which scene do you want to load? Options are: \n");
		printf("1. whitted, 2. boxes, 3. test, 4. acceleration\n");
		printf("Type full name or number and press enter to continue.\n");

		std::string cmnd;
		std::cin >> cmnd;
		load_scene_command(cmnd);
		printf("---\n");
	}

	void commandlineinputhandler::load_scene_command(std::string command)
	{
		m_state = LOADING_SCENE;

		if (command == "1" || command == "whitted")
		{
			m_application->load_scene(new scenewhitted(m_application));
		}
		else if (command == "2" || command == "boxes")
		{
			m_application->load_scene(new sceneboxes(m_application));
		}
		else if (command == "3" || command == "test")
		{
			m_application->load_scene(new scenetest(m_application));
		}
		else if (command == "4" || command == "acceleration")
		{
			m_application->load_scene(new sceneacceleration(m_application));
		}
		else
		{
			printf("scene not recognized.\n");
			load_scene_menu();
		}

		m_state = RENDERING_SCENE;
	}

}
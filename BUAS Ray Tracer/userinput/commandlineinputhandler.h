#pragma once
#include <string>

enum commandinputstate
{
	LOAD_SCENE = 0,
	LOADING_SCENE,
	RENDERING_SCENE,
	WAITING_FOR_INPUT
};

namespace brt
{
	class raytracer;

	class commandlineinputhandler
	{
	public:
		commandlineinputhandler(raytracer* application);
		~commandlineinputhandler();

		void update(float deltat);

	private:
		void load_scene_menu();

		void load_scene_command(std::string command);

	private:
		raytracer* m_application;

		commandinputstate m_state;

		// bool m_continuousrendering = true; // TODO: implement
	};
}
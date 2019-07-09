#include "scenemainmenu.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../raytracer.h"

#include "general/scenemanager.h"

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui-sfml/imgui-SFML.h"


#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	scenemainmenu::scenemainmenu(raytracer * application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	scenemainmenu::~scenemainmenu()
	{
		destroy_scene();
	}

	void scenemainmenu::update(float)
	{
		ImGui::Begin("Main menu");

		if (ImGui::Button("Whitted"))
		{
			m_raytracer->get_scene_manager()->load_scene(scenes::WHITTED);
		}
		else if (ImGui::Button("Boxes"))
		{
			m_raytracer->get_scene_manager()->load_scene(scenes::BOXES);
		}
		else if (ImGui::Button("Test"))
		{
			m_raytracer->get_scene_manager()->load_scene(scenes::TEST);
		}
		else if (ImGui::Button("Acceleration"))
		{
			m_raytracer->get_scene_manager()->load_scene(scenes::ACCELERATION);
		}

		ImGui::End();
	}

	void scenemainmenu::build_scene()
	{
		// camera
		vec3 lookatpos(0.f, 2.f, -5.f);
		vec3 campos(4.f, 3.f, 3.f);

		m_camera = new camera(lookatpos, campos, vec3::up());
	}
}
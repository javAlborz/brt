#include "scenemainmenu.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../raytracer.h"
#include "../../rendering/renderer.h"

#include "general/scenemanager.h"

#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui-sfml/imgui-SFML.h"

#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	scenemainmenu::scenemainmenu(raytracer * application) : scene(application), m_imageScaling(DEFAULT_IMAGE_SCALING)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	scenemainmenu::~scenemainmenu()
	{
		destroy_scene();
	}

	void scenemainmenu::update(float)
	{
		ImGui::SetNextWindowSize(ImVec2(400.f, 300.f));
		ImGui::Begin("Main menu");

		const float dragspeed = 0.05f;
		const float minscaling = 0.1f;
		const float maxscaling = 10.f;
		ImGui::DragFloat("Image scaling", &m_imageScaling, dragspeed, minscaling, maxscaling);

		m_raytracer->get_renderer()->set_image_scaling(m_imageScaling);

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
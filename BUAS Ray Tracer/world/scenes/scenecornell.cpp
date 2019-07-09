#include "scenecornell.h"

#include "../objects/sceneobject.h"
#include "../objects/plane.h"
#include "../objects/quadrilateral.h"

#include "../lights/light.h"
#include "../lights/pointlight.h"
#include "../lights/directionallight.h"

#include "../../rendering/materials/material.h"
#include "../../rendering/materials/materialdefault.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../RayTracer.h"

namespace brt
{
	scenecornell::scenecornell(raytracer* application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	scenecornell::~scenecornell()
	{
		destroy_scene();
	}

	void scenecornell::build_scene()
	{
		vec3 lookatpos(278.f, 273.f, -0.f);
		vec3 campos(278.f, 273.f, -800.f);
		m_camera = new camera(lookatpos, campos, vec3::up());

		// objects
		// floor
		std::shared_ptr<material> floorplanemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(255, 255, 255)));
		m_objects.push_back(new plane(vec3(0.f, 0.f, 0.f), vec3(0.0f, 1.f, 0.f), floorplanemat));

		// ceiling
		m_objects.push_back(new plane(vec3(0.f, 548.8f, 0.f), vec3(0.0f, -1.f, 0.f), floorplanemat));
		// TODO: ceiling casts shadows on floor, even though the light is in between, why is this? Is the shadow function broken?

		// back wall
// 		m_objects.push_back(new plane(vec3(0.f, 0.f, 559.2f), vec3(0.0f, 0.f, -1.f), floorplanemat));
// 
// 		// right wall (green)
// 		std::shared_ptr<material> rightplanemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(sf::Color(0, 255, 0)));
// 		m_objects.push_back(new plane(vec3(525.8f, 0.f, 0.0f), vec3(-1.f, 0.f, 0.f), rightplanemat));
// 
// 		// left wall (red)
// 		std::shared_ptr<material> leftplanemat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(sf::Color(255, 0, 0)));
// 		m_objects.push_back(new plane(vec3(0.f, 0.f, 0.0f), vec3(1.f, 0.f, 0.f), leftplanemat));

		// quadrilateral test
		//std::shared_ptr<material> quadmat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(sf::Color(255, 255, 255)));
		//vec3 localverts[4] = { vec3(2.4f, 0.f, 3.f), vec3(-2.5f, 1.f, 3.f), vec3(2.5f, 0.f, -3.f), vec3(-2.5f, 0.f, -3.f) };
		//m_objects.push_back(new quadrilateral(vec3(-2.5f, 0.f, -11.f), vec3(0.0f, 1.f, 0.f), quadmat, localverts));

		// triangle test
		//vec3 verts[3] = { vec3(2.f, 0.f, -0.f), vec3(0.f, 2.f, -1.f), vec3(0.f, 0.f, 0.f) };
		//m_objects.push_back(new triangle(vec3(0.f, 0.f, 0.f), sf::Color(228, 182, 2), verts));

		// -----------------------
		// lights
		std::shared_ptr<light> l = std::static_pointer_cast<light>(std::make_shared<pointlight>(vec3(343.f, 548.f, 227.f), color::white(), 1.f));
		m_lights.push_back(l);
	}
}
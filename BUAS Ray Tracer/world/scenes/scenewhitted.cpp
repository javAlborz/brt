#include "scenewhitted.h"

#include "../objects/sceneobject.h"
#include "../objects/sphere.h"
#include "../objects/plane.h"
#include "../objects/triangle.h"
#include "../objects/quadrilateral.h"

#include "../lights/light.h"
#include "../lights/pointlight.h"

#include "../../rendering/materials/material.h"
#include "../../rendering/materials/materialdefault.h"
#include "../../rendering/materials/materialproccheckerboard.h"

#include "../../rendering/camera.h"
#include "../../rendering/renderer.h"

#include "../../raytracer.h"

#define SCREEN_WIDTH 340.f
#define SCREEN_HEIGHT 180.f

namespace brt
{
	scenewhitted::scenewhitted(raytracer* application) : scene(application)
	{
		build_scene(); // calling build_scene here because virtual function shouldn't be called in constructor
	}

	scenewhitted::~scenewhitted()
	{
		destroy_scene();
	}

	void scenewhitted::build_scene()
	{
		// camera
		vec3 lookatpos(0.f, 2.2f, -5.f);
		vec3 campos(0.f, 2.5f, 0.f);
		m_camera = new camera(lookatpos, campos, vec3::up(), SCREEN_WIDTH, SCREEN_HEIGHT);
		m_raytracer->get_renderer()->set_resolution(static_cast<unsigned int>(SCREEN_WIDTH), static_cast<unsigned int>(SCREEN_HEIGHT));

		// glass sphere
		std::shared_ptr<material> glassspheremat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(230, 230, 230, 80), 200.f, color(150, 150, 150), 0.f, true, /*0.97f*/ REFRACTIVEGLASS));
		m_objects.push_back(new sphere(vec3(0.3f, 2.12f, -5.f), 0.95f, glassspheremat)); // original pos (0.3f, 2.12f, -5.f)

		// inner glass sphere
		std::shared_ptr<material> innerglassspheremat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(230, 230, 230, 80), SPECNONE, color::white(), 0.f, true, 0.65f));
		m_objects.push_back(new sphere(vec3(0.3f, 2.12f, -5.f), 0.9495f, innerglassspheremat)); // original pos (0.3f, 2.12f, -5.f)

		// metal sphere
		std::shared_ptr<material> metalspheremat = std::static_pointer_cast<material>(std::make_shared<materialdefault>(color(190, 201, 160), SPECMIDLYSHINY, color::white(), 0.5f));
		m_objects.push_back(new sphere(vec3(-1.f, 1.1f, -7.5f), 0.9f, metalspheremat));

		// checkerboard quadrilateral
		std::shared_ptr<material> quadmat = std::static_pointer_cast<material>(std::make_shared<materialproccheckerboard>(1.5f, color(255, 0, 0), color(255, 255, 0)));
		vec3 localverts[4] = { vec3(3.5f, -1.f, 10.f), vec3(-5.5f, -1.f, 10.f), vec3(3.5f, -1.f, -8.f), vec3(-5.5f, -1.f, -8.f) };
		m_objects.push_back(new quadrilateral(vec3(-6.f, -1.f, -23.f), vec3(0.0f, 1.f, 0.f), quadmat, localverts));

		// light
		std::shared_ptr<light> scenelight = std::static_pointer_cast<light>(std::make_shared<pointlight>(vec3(0.f, 5.f, -3.5f), color::white(), 1.f));
		m_lights.push_back(scenelight);
	}
}